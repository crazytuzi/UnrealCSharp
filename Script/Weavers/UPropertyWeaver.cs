using Fody;
using Mono.Cecil;
using Mono.Cecil.Cil;
using Mono.Cecil.Rocks;
using System;
using System.Collections.Generic;
using System.Linq;

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


        TypeDefinition PathAttributeType = null;

        public override void Execute()
        {
            GetAllMeta();
            GetAllUClass();
            // 处理UProperty
            UClassTypes.ForEach(ProcessUClassType);
            UStructTypes.ForEach(ProcessUStructType);
            // 处理PathName
            UClassTypes.ForEach(AddPathNameAttributeToUEType);
            UStructTypes.ForEach(AddPathNameAttributeToUEType);
            UEnumTypes.ForEach(AddPathNameAttributeToUEType);
            UInterfaceTypes.ForEach(AddPathNameAttributeToUEType);


        }

        public override IEnumerable<string> GetAssembliesForScanning()
        {
            yield return "UE";
            yield return "Game";
        }


        public void AddPathNameAttributeToUEType(TypeDefinition type)
        {
            if (type.CustomAttributes.Any(attribute => attribute.AttributeType == PathAttributeType) == false)
            {

                var constructor = PathAttributeType.GetConstructors().FirstOrDefault();

                var constructorRef = ModuleDefinition.ImportReference(constructor);
                var attribute = new CustomAttribute(constructorRef);

                var FullPath = "/Script/CoreUObject.";
                if (type.Name[0] == 'A' || type.Name[0] == 'U' || type.Name[0] == 'F')
                {
                    FullPath += type.Name.Substring(1);
                }
                else
                {
                    FullPath += type.Name;
                }
                attribute.ConstructorArguments.Add(new CustomAttributeArgument(ModuleDefinition.TypeSystem.String, FullPath));
                type.CustomAttributes.Add(attribute);
            }

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
                    var field = new FieldDefinition("__" + property.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);
                    type.Fields.Add(field);
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
                    var field = new FieldDefinition("__" + property.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);
                    type.Fields.Add(field);
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
        private void GetAllMeta()
        {


            TypeDefinition PropertyImplementationClass = ModuleDefinition.Types.FirstOrDefault(type => type.FullName == "Script.Library.FPropertyImplementation");
            PathAttributeType = ModuleDefinition.Types.FirstOrDefault(type => type.FullName == "Script.CoreUObject.PathNameAttribute");
            if (PropertyImplementationClass == null)
            {
                var Module = ModuleDefinition.ReadModule("../../Content/Script/UE.dll");
                PropertyImplementationClass = Module.Types.FirstOrDefault(type => type.FullName == "Script.Library.FPropertyImplementation");
                PathAttributeType = Module.Types.FirstOrDefault(type => type.FullName == "Script.CoreUObject.PathNameAttribute");
            }
            if (PropertyImplementationClass == null || PathAttributeType == null)
            {
                throw new WeavingException("Not Found build in class: 'Script.Library.FPropertyImplementation'");
            }

            foreach(var method in PropertyImplementationClass.Methods)
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
    }
}

