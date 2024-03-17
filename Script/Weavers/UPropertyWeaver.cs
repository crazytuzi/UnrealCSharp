using Fody;
using Mono.Cecil;
using Mono.Cecil.Cil;
using Mono.Cecil.Rocks;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;

namespace Weavers
{
    public class UPropertyWeaver : BaseModuleWeaver
    {
        Dictionary<string, MethodDefinition> ObjectSetMethodMap = new Dictionary<string, MethodDefinition>();
        Dictionary<string, MethodDefinition> ObjectGetMethodMap = new Dictionary<string, MethodDefinition>();
        Dictionary<string, MethodDefinition> StructSetMethodMap = new Dictionary<string, MethodDefinition>();
        Dictionary<string, MethodDefinition> StructGetMethodMap = new Dictionary<string, MethodDefinition>();

        List<TypeDefinition> UClassTypes = new List<TypeDefinition>();
        List<TypeDefinition> UStructTypes = new List<TypeDefinition>();


        List<TypeDefinition> UEnumTypes = new List<TypeDefinition>();
        List<TypeDefinition> UInterfaceTypes = new List<TypeDefinition>();

        TypeDefinition IStaticClassType;
        TypeDefinition IStaticStructType;


        TypeDefinition UScriptStructType;
        TypeDefinition UClassType;

        MethodDefinition UObject_StaticClassImplementation;
        MethodDefinition UStruct_StaticStructImplementation;


        MethodDefinition UStruct_RegisterImplementation;
        MethodDefinition UStruct_UnRegisterImplementation;

        TypeDefinition PathAttributeType = null;

        public override void Execute()
        {
            GetAllMeta();
            GetAllUClass();
            // 处理PathName
            UClassTypes.ForEach(AddPathNameAttributeToUEType);
            UStructTypes.ForEach(AddPathNameAttributeToUEType);
            UEnumTypes.ForEach(AddPathNameAttributeToUEType);
            UInterfaceTypes.ForEach(AddPathNameAttributeToUEType);

            
            // 处理IStaticClass
            UClassTypes.ForEach(ProcessStaticClass);
            UInterfaceTypes.ForEach(ProcessStaticClass);
            UStructTypes.ForEach(ProcessStaticStruct);
            UStructTypes.ForEach(ProcessStructGCHandle);
            UStructTypes.ForEach(ProcessStructRegister);
            

            // 处理UProperty
            UClassTypes.ForEach(ProcessUClassType);
            UStructTypes.ForEach(ProcessUStructType);
        }

        public override IEnumerable<string> GetAssembliesForScanning()
        {
            yield return "UE";
            yield return "Game";
        }

        
        public void ProcessStaticClass(TypeDefinition type)
        {
            if (type.IsClass == false)
                return;
            if (type.Interfaces.Any(interf => interf.InterfaceType.FullName == "Script.CoreUObject.IStaticClass") == false)
            {
                var IStaticClassInterface = new InterfaceImplementation(ModuleDefinition.ImportReference(IStaticClassType));
                type.Interfaces.Add(IStaticClassInterface);
            }

            if (type.Methods.Any(method => method.IsStatic && method.Name == "StaticClass" && method.Parameters.Count == 0) == false)
            {
                var StaticClassMethod = IStaticClassType.Methods.FirstOrDefault(method => method.Name == "StaticClass");
                var StaticClassFunction = new MethodDefinition("StaticClass", MethodAttributes.Public | MethodAttributes.Static | MethodAttributes.HideBySig, ModuleDefinition.ImportReference(UClassType));
                StaticClassFunction.Overrides.Add(ModuleDefinition.ImportReference(StaticClassMethod));
                var Instructions = StaticClassFunction.Body.Instructions;
                Instructions.Add(Instruction.Create(OpCodes.Nop));
                Instructions.Add(Instruction.Create(OpCodes.Ldstr, GetPath(type)));
                Instructions.Add(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(UObject_StaticClassImplementation)));
                Instructions.Add(Instruction.Create(OpCodes.Ret));
                
                type.Methods.Add(StaticClassFunction);
            }
        }

        private void ProcessStructRegister(TypeDefinition type)
        {
            if (type.BaseType.FullName != typeof(object).FullName)
                return;

            // 构造函数处理
            var ctors = type.GetConstructors();
            var ctor = ctors.FirstOrDefault(method => method.Parameters.Count() == 0);
            if (ctor == null)
            {
                throw new WeavingException("UStruct must have a constructor with 0 parameters: " + type.FullName);
            }
            var ilProcessor = ctor.Body.GetILProcessor();
            ilProcessor.InsertAfter(ctor.Body.Instructions[1], Instruction.Create(OpCodes.Ldarg_0));
            ilProcessor.InsertAfter(ctor.Body.Instructions[2], Instruction.Create(OpCodes.Ldarg_0));
            ilProcessor.InsertAfter(ctor.Body.Instructions[3], Instruction.Create(OpCodes.Ldstr, GetPath(type)));
            ilProcessor.InsertAfter(ctor.Body.Instructions[4], Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(UStruct_RegisterImplementation)));

            if (type.Methods.Any(m => m.Name == "Finalize") == false)
            {
                var superFinalize = type.BaseType.Resolve().Methods.FirstOrDefault(m => m.Name == "Finalize");
                var destructor = new MethodDefinition("Finalize", MethodAttributes.HideBySig | MethodAttributes.Family | MethodAttributes.Virtual, ModuleDefinition.TypeSystem.Void);
                destructor.Overrides.Add(ModuleDefinition.ImportReference(superFinalize));
                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Ldarg_0));
                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Call, type.Methods.FirstOrDefault(m => m.Name == "get_GarbageCollectionHandle")));
                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(UStruct_UnRegisterImplementation)));
                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Ret));
                
                type.Methods.Add(destructor);
            } else
            {
                var Finalize = type.Methods.FirstOrDefault(m => m.Name == "Finalize");
                ilProcessor = Finalize.Body.GetILProcessor(); 
                ilProcessor.InsertBefore(Finalize.Body.Instructions[0], Instruction.Create(OpCodes.Ldarg_0));
                ilProcessor.InsertBefore(Finalize.Body.Instructions[1], Instruction.Create(OpCodes.Call, type.Methods.FirstOrDefault(m => m.Name == "get_GarbageCollectionHandle")));
                ilProcessor.InsertBefore(Finalize.Body.Instructions[2], Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(UStruct_UnRegisterImplementation)));
           
            }

            



        }
        private void ProcessStructGCHandle(TypeDefinition type)
        {
            if (type.Properties.Any(property => property.Name == "GarbageCollectionHandle") == true)
                return;
            var GarbageCollectionHandle = new PropertyDefinition("GarbageCollectionHandle", PropertyAttributes.None, ModuleDefinition.TypeSystem.IntPtr);
            
            var GarbageCollectionHandleBackingField = new FieldDefinition("<GarbageCollectionHandle>k__BackingField", FieldAttributes.Private, ModuleDefinition.TypeSystem.IntPtr);
            type.Fields.Add(GarbageCollectionHandleBackingField);

            var cga = ModuleDefinition.ImportReference(typeof(CompilerGeneratedAttribute));
            var constructor = cga.Resolve().GetConstructors().FirstOrDefault();
            var constructorRef = ModuleDefinition.ImportReference(constructor);
            var attribute = new CustomAttribute(constructorRef);
            GarbageCollectionHandleBackingField.CustomAttributes.Add(attribute);

            var getter = new MethodDefinition("get_GarbageCollectionHandle", MethodAttributes.Public | MethodAttributes.HideBySig | MethodAttributes.SpecialName | MethodAttributes.NewSlot | MethodAttributes.Virtual | MethodAttributes.Final, ModuleDefinition.TypeSystem.IntPtr);
            var Instructions = getter.Body.Instructions;
            Instructions.Add(Instruction.Create(OpCodes.Ldarg_0));
            Instructions.Add(Instruction.Create(OpCodes.Ldfld, GarbageCollectionHandleBackingField));
            Instructions.Add(Instruction.Create(OpCodes.Ret));
            type.Methods.Add(getter);
            GarbageCollectionHandle.GetMethod = getter;

            var setter = new MethodDefinition("set_GarbageCollectionHandle", MethodAttributes.Public | MethodAttributes.HideBySig | MethodAttributes.SpecialName | MethodAttributes.NewSlot | MethodAttributes.Virtual | MethodAttributes.Final, ModuleDefinition.TypeSystem.Void);
            setter.Parameters.Add(new ParameterDefinition(ModuleDefinition.TypeSystem.IntPtr));
            Instructions = setter.Body.Instructions;
            Instructions.Add(Instruction.Create(OpCodes.Ldarg_0));
            Instructions.Add(Instruction.Create(OpCodes.Ldarg_1));
            Instructions.Add(Instruction.Create(OpCodes.Stfld, GarbageCollectionHandleBackingField));
            Instructions.Add(Instruction.Create(OpCodes.Ret));
            type.Methods.Add(setter);
            GarbageCollectionHandle.SetMethod = setter;
            type.Properties.Add(GarbageCollectionHandle);
        }
        public void ProcessStaticStruct(TypeDefinition type)
        {
            if (type.IsClass == false)
                return;
            if (type.Interfaces.Any(interf => interf.InterfaceType.FullName == "Script.CoreUObject.IStaticStruct") == false)
            {
                var IStaticStructInterface = new InterfaceImplementation(ModuleDefinition.ImportReference(IStaticStructType));
                type.Interfaces.Add(IStaticStructInterface);
            }
            if (type.Methods.Any(method => method.IsStatic && method.Name == "StaticStruct" && method.Parameters.Count == 0) == false)
            {
                var StaticStructMethod = IStaticStructType.Methods.FirstOrDefault(method => method.Name == "StaticStruct");
                var StaticStructFunction = new MethodDefinition("StaticStruct", MethodAttributes.Public | MethodAttributes.Static | MethodAttributes.HideBySig, ModuleDefinition.ImportReference(UScriptStructType));
                StaticStructFunction.Overrides.Add(ModuleDefinition.ImportReference(StaticStructMethod));
                var Instructions = StaticStructFunction.Body.Instructions;
                Instructions.Add(Instruction.Create(OpCodes.Nop));
                Instructions.Add(Instruction.Create(OpCodes.Ldstr, GetPath(type)));
                Instructions.Add(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(UStruct_StaticStructImplementation)));
                Instructions.Add(Instruction.Create(OpCodes.Ret));

                type.Methods.Add(StaticStructFunction);
            }  
        }

        public void AddPathNameAttributeToUEType(TypeDefinition type)
        {
            if (type.CustomAttributes.Any(attribute => attribute.AttributeType == PathAttributeType) == false)
            {

                var constructor = PathAttributeType.GetConstructors().FirstOrDefault();

                var constructorRef = ModuleDefinition.ImportReference(constructor);
                var attribute = new CustomAttribute(constructorRef);
                var FullPath = GetPath(type);
                attribute.ConstructorArguments.Add(new CustomAttributeArgument(ModuleDefinition.TypeSystem.String, FullPath));
                type.CustomAttributes.Add(attribute);
            }

        }

        private string GetPath(TypeDefinition type)
        {
            var FullPath = "/Script/CoreUObject.";
            if (type.Name[0] == 'A' || type.Name[0] == 'U' || type.Name[0] == 'F')
            {
                FullPath += type.Name.Substring(1);
            }
            else if (type.IsInterface && type.Name[0] == 'I')
            {
                FullPath += type.Name.Substring(1);
            }
            else
            {
                FullPath += type.Name;
            }
            if (FullPath.EndsWith("_C"))
                FullPath = FullPath.Substring(0, FullPath.Length - 2);
            return FullPath;
        }
        private void ProcessUClassType(TypeDefinition type)
        {
            foreach(var property in type.Properties)
            {
                if (property.CustomAttributes.Any(attribute => attribute.AttributeType.FullName == "Script.Dynamic.UPropertyAttribute"))
                {
                    ProcessUClassProperty(type, property);
                }
            }

        }

        private void ProcessUClassProperty(TypeDefinition type, PropertyDefinition property)
        {
            // 删除默认生成

            var FieldName = $"<{property.Name}>k__BackingField";
            var BackingField = type.Fields.FirstOrDefault(field => field.Name == FieldName && field.FieldType.FullName == property.PropertyType.FullName);
            if (BackingField != null)
            {
                type.Fields.Remove(BackingField);
                // type.Fields.Clear();
            }

            // 获取GarbageCollectionHandle访问器
            var GetGarbageCollectionHandleMethod = GetGarbageCollectionHandle(type);
            if (GetGarbageCollectionHandleMethod == null)
            {
                throw new WeavingException("Not Found GetGarbageCollectionHandle property's getter of class " + type.FullName);
            }
            // 修改setter
            if (property.SetMethod != null)
            {
                var propertyType = property.PropertyType;
                var PropertySetMethod = GetPropertyAccessor(property, ObjectSetMethodMap);
                if (PropertySetMethod != null)
                {
                    var field = type.Fields.FirstOrDefault(f => f.Name == "__" + property.Name && f.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);
                    if (field == null)
                    {
                        field = new FieldDefinition("__" + property.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);
                        type.Fields.Add(field);
                    }

                    var ilProcessor = property.SetMethod.Body.GetILProcessor();
                    ilProcessor.Clear();
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(GetGarbageCollectionHandleMethod)));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_1));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(PropertySetMethod)));
                    ilProcessor.Append(Instruction.Create(OpCodes.Nop));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found set function of type " + propertyType.FullName);
                }


            }

            if (property.GetMethod != null)
            {
                var propertyType = property.PropertyType;
                // 先找一下int, uint这些 函数的类型跟 property能直接对上的
                var PropertyGetMethod = GetPropertyAccessor(property, ObjectGetMethodMap);
                if (PropertyGetMethod != null)
                {
                    var field = type.Fields.FirstOrDefault(f => f.Name == "__" + property.Name && f.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);
                    if (field == null)
                    {
                        field = new FieldDefinition("__" + property.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);
                        type.Fields.Add(field);
                    }
                    var ilProcessor = property.GetMethod.Body.GetILProcessor();
                    ilProcessor.Clear();
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(GetGarbageCollectionHandleMethod)));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(PropertyGetMethod)));
                    if (propertyType.IsValueType == false)
                    {
                        ilProcessor.Append(Instruction.Create(OpCodes.Isinst, ModuleDefinition.ImportReference(propertyType)));
                    }
                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found get function of type " + propertyType.FullName);
                }
            }


        }


        private void ProcessUStructType(TypeDefinition type)
        {
            foreach (var property in type.Properties)
            {
                if (property.CustomAttributes.Any(attribute => attribute.AttributeType.FullName == "Script.Dynamic.UPropertyAttribute"))
                {
                    ProcessUStructProperty(type, property);
                }
            }

        }
        private void ProcessUStructProperty(TypeDefinition type, PropertyDefinition property)
        {
            // 删除默认生成

            var FieldName = $"<{property.Name}>k__BackingField";
            var BackingField = type.Fields.FirstOrDefault(field => field.Name == FieldName && field.FieldType.FullName == property.PropertyType.FullName);
            if (BackingField != null)
            {
                type.Fields.Remove(BackingField);
                // type.Fields.Clear();
            }

            // 获取GarbageCollectionHandle访问器
            var GetGarbageCollectionHandleMethod = GetGarbageCollectionHandle(type);
            if (GetGarbageCollectionHandleMethod == null)
            {
                throw new WeavingException("Not Found GetGarbageCollectionHandle property's getter of class " + type.FullName);
            }
            // 修改setter
            if (property.SetMethod != null)
            {
                var propertyType = property.PropertyType;
                var PropertySetMethod = GetPropertyAccessor(property, StructSetMethodMap);
                if (PropertySetMethod != null)
                {
                    var field = type.Fields.FirstOrDefault(f => f.Name == "__" + property.Name && f.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);
                    if (field == null)
                    {
                        field = new FieldDefinition("__" + property.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);
                        type.Fields.Add(field);
                    }
                    var ilProcessor = property.SetMethod.Body.GetILProcessor();
                    ilProcessor.Clear();
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(GetGarbageCollectionHandleMethod)));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_1));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(PropertySetMethod)));
                    ilProcessor.Append(Instruction.Create(OpCodes.Nop));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found set function of type " + propertyType.FullName);
                }


            }

            if (property.GetMethod != null)
            {
                var propertyType = property.PropertyType;
                // 先找一下int, uint这些 函数的类型跟 property能直接对上的
                var PropertyGetMethod = GetPropertyAccessor(property, StructGetMethodMap);
                if (PropertyGetMethod != null)
                {
                    var field = type.Fields.FirstOrDefault(f => f.Name == "__" + property.Name && f.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);
                    if (field == null)
                    {
                        field = new FieldDefinition("__" + property.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);
                        type.Fields.Add(field);
                    }
                    var ilProcessor = property.GetMethod.Body.GetILProcessor();
                    ilProcessor.Clear();
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(GetGarbageCollectionHandleMethod)));
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));
                    ilProcessor.Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(PropertyGetMethod)));
                    if (propertyType.IsValueType == false)
                    {
                        ilProcessor.Append(Instruction.Create(OpCodes.Isinst, ModuleDefinition.ImportReference(propertyType)));
                    }
                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found get function of type " + propertyType.FullName);
                }
            }


        }

        private MethodDefinition GetPropertyAccessor(PropertyDefinition property, Dictionary<string, MethodDefinition> MethodMap)
        {
            var type = property.PropertyType.Resolve();
            if (MethodMap.TryGetValue(property.PropertyType.FullName, out var PropertyGetMethod) == false)
            {
                // 然后找一下enum
                if (type.IsEnum)
                {
                    if (MethodMap.TryGetValue(type.GetEnumUnderlyingType().FullName, out PropertyGetMethod) == false)
                    {
                        throw new WeavingException("Not found accessor Property Method: named " + property.Name + " property type is " + type.Resolve().GetEnumUnderlyingType().Resolve().FullName + " of type " + "type " + type.FullName);
                    }
                }
                if (GetGarbageCollectionHandle(type.Resolve()) != null)
                {
                    PropertyGetMethod = MethodMap[ModuleDefinition.TypeSystem.Object.FullName];
                }
            }

            return PropertyGetMethod;
        }
        private MethodDefinition GetGarbageCollectionHandle(TypeDefinition type)
        {
            var property = type.Properties.FirstOrDefault(porperty => porperty.Name == "GarbageCollectionHandle"
                && porperty.PropertyType.FullName == ModuleDefinition.TypeSystem.IntPtr.FullName
                && porperty.GetMethod != null);
            if (property != null)
                return property.GetMethod;
            if (type.BaseType != null)
                return GetGarbageCollectionHandle(type.BaseType.Resolve());
            return null;
        }
        private void GetAllUClass()
        {
            foreach (var type in ModuleDefinition.Types)
            {
                if (type.CustomAttributes.Any(attribute => attribute.AttributeType.FullName == "Script.Dynamic.UClassAttribute"))
                {
                    UClassTypes.Add(type);
                }
                else if (type.CustomAttributes.Any(attribute => attribute.AttributeType.FullName == "Script.Dynamic.UStructAttribute"))
                {
                    UStructTypes.Add(type);
                }
                else if (type.CustomAttributes.Any(attribute => attribute.AttributeType.FullName == "Script.Dynamic.UEnumAttribute"))
                {
                    UEnumTypes.Add(type);
                }
                else if (type.CustomAttributes.Any(attribute => attribute.AttributeType.FullName == "Script.Dynamic.UInterfaceAttribute"))
                {
                    UInterfaceTypes.Add(type);
                }
                else if (type.IsInterface && type.BaseType != null && type.FullName == "Script.CoreUObject.IInterface")
                {
                    UInterfaceTypes.Add(type);
                }
            }
        }

        private void SearchAllPropertyAccessors(ModuleDefinition UEDefinition)
        {
            TypeDefinition PropertyImplementationClass = UEDefinition.GetType("Script.Library.FPropertyImplementation");
            foreach (var method in PropertyImplementationClass.Methods)
            {
                if (method.IsStatic == false)
                    continue;
                // Get函数
                if (method.ReturnType.FullName != ModuleDefinition.TypeSystem.Void.FullName
                    && method.Name.IndexOf("FProperty_Get") >= 0 && method.Name.IndexOf("PropertyImplementation") > 0)
                {
                    var PropertyType = method.ReturnType;
                    if (method.Name.IndexOf("FProperty_GetObject") >= 0)
                    {
                        // UObject
                        ObjectGetMethodMap.Add(PropertyType.FullName, method);
                    }
                    else if (method.Name.IndexOf("FProperty_GetStruct") >= 0)
                    {
                        // UStruct
                        StructGetMethodMap.Add(PropertyType.FullName, method);
                    }
                }
                // Set函数
                else if (method.ReturnType.FullName == ModuleDefinition.TypeSystem.Void.FullName
                    && method.Name.IndexOf("FProperty_Set") >= 0 && method.Name.IndexOf("PropertyImplementation") > 0
                    && method.Parameters.Count == 3)
                {
                    var PropertyType = method.Parameters[2].ParameterType;
                    if (method.Name.IndexOf("FProperty_SetObject") >= 0)
                    {
                        // UObject
                        ObjectSetMethodMap.Add(PropertyType.FullName, method);
                    }
                    else if (method.Name.IndexOf("FProperty_SetStruct") >= 0)
                    {
                        // UStruct
                        StructSetMethodMap.Add(PropertyType.FullName, method);
                    }
                }
            }
        }
        private void GetAllMeta()
        {
            ModuleDefinition UEDefinition = ModuleDefinition;
            if (UEDefinition.Name != "UE.dll")
            {
                UEDefinition = ModuleDefinition.ReadModule("../../Content/Script/UE.dll");
            }
            
            PathAttributeType = UEDefinition.GetType("Script.CoreUObject.PathNameAttribute");
            IStaticClassType = UEDefinition.GetType("Script.CoreUObject.IStaticClass");
            IStaticStructType = UEDefinition.GetType("Script.CoreUObject.IStaticStruct");
            UClassType = UEDefinition.GetType("Script.CoreUObject.UClass");
            UScriptStructType = UEDefinition.GetType("Script.CoreUObject.UScriptStruct");
            UStruct_StaticStructImplementation = UEDefinition.GetType("Script.Library.UStructImplementation").Methods.FirstOrDefault(method => method.Name == "UStruct_StaticStructImplementation");
            UObject_StaticClassImplementation = UEDefinition.GetType("Script.Library.UObjectImplementation").Methods.FirstOrDefault(method => method.Name == "UObject_StaticClassImplementation");
            UStruct_RegisterImplementation = UEDefinition.GetType("Script.Library.UStructImplementation").Methods.FirstOrDefault(method => method.Name == "UStruct_RegisterImplementation");
            UStruct_UnRegisterImplementation = UEDefinition.GetType("Script.Library.UStructImplementation").Methods.FirstOrDefault(method => method.Name == "UStruct_UnRegisterImplementation");
            SearchAllPropertyAccessors(UEDefinition);

        }
    }
}

