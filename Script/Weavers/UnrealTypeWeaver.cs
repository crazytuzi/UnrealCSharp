using System;
using Fody;
using Mono.Cecil;
using Mono.Cecil.Cil;
using Mono.Cecil.Rocks;
using System.Collections.Generic;
using System.Linq;

namespace Weavers
{
    public class UnrealTypeWeaver : BaseModuleWeaver
    {
        private readonly Dictionary<string, MethodDefinition> _objectSetMethodMap =
            new Dictionary<string, MethodDefinition>();

        private readonly Dictionary<string, MethodDefinition> _objectGetMethodMap =
            new Dictionary<string, MethodDefinition>();

        private readonly Dictionary<string, MethodDefinition> _structSetMethodMap =
            new Dictionary<string, MethodDefinition>();

        private readonly Dictionary<string, MethodDefinition> _structGetMethodMap =
            new Dictionary<string, MethodDefinition>();

        private readonly List<TypeDefinition> _classTypes = new List<TypeDefinition>();

        private readonly List<TypeDefinition> _structTypes = new List<TypeDefinition>();

        private readonly List<TypeDefinition> _enumTypes = new List<TypeDefinition>();

        private readonly List<TypeDefinition> _interfaceTypes = new List<TypeDefinition>();

        private MethodDefinition _structRegisterImplementation;

        private MethodDefinition _structUnRegisterImplementation;

        private MethodDefinition _functionReflection0Implementation;

        private MethodDefinition _functionReflection2Implementation;

        private MethodDefinition _getGarbageCollectionHandle;

        private TypeDefinition _pathAttributeType;

        private TypeDefinition _ufunctionAttributeType;

        private TypeDefinition _serverAttributeType;
        private TypeDefinition _clientAttributeType;
        private TypeDefinition _netMulticastAttributeAttributeType;
        private TypeDefinition _overrideAttributeType;
        public override void Execute()
        {
            GetAllMeta();

            GetAllDynamic();

            // 处理PathName
            _classTypes.ForEach(AddPathNameAttributeToUnrealType);

            _structTypes.ForEach(AddPathNameAttributeToUnrealType);

            _enumTypes.ForEach(AddPathNameAttributeToUnrealType);

            _interfaceTypes.ForEach(AddPathNameAttributeToUnrealType);

            // 处理GCHandle
            _structTypes.ForEach(ProcessStructGarbageCollectionHandle);

            // 处理结构体注册和注销
            _structTypes.ForEach(ProcessStructRegister);

            // 处理UProperty
            _classTypes.ForEach(ProcessUClassType);

            _structTypes.ForEach(ProcessUStructType);

            _classTypes.ForEach(ProcessRpcMethods);
        }

        public override IEnumerable<string> GetAssembliesForScanning()
        {
            yield return "UE";

            yield return "Game";
        }

        private void ProcessStructRegister(TypeDefinition Type)
        {
            if (Type.BaseType.FullName != ModuleDefinition.TypeSystem.Object.FullName)
            {
                return;
            }

            // 构造函数处理
            var constructors = Type.GetConstructors();

            var constructor = constructors.FirstOrDefault(Method => !Method.Parameters.Any());

            if (constructor == null)
            {
                throw new WeavingException("UStruct must have a constructor with 0 parameters: " + Type.FullName);
            }

            var ilProcessor = constructor.Body.GetILProcessor();

            ilProcessor.InsertAfter(constructor.Body.Instructions[1], Instruction.Create(OpCodes.Ldarg_0));

            ilProcessor.InsertAfter(constructor.Body.Instructions[2],
                Instruction.Create(OpCodes.Ldstr, GetPathName(Type)));

            ilProcessor.InsertAfter(constructor.Body.Instructions[3],
                Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(_structRegisterImplementation)));

            if (Type.Methods.Any(Method => Method.Name == "Finalize") == false)
            {
                var superFinalize = Type.BaseType.Resolve().Methods.FirstOrDefault(Method => Method.Name == "Finalize");

                var destructor = new MethodDefinition("Finalize",
                    MethodAttributes.HideBySig | MethodAttributes.Family | MethodAttributes.Virtual,
                    ModuleDefinition.TypeSystem.Void);

                destructor.Overrides.Add(ModuleDefinition.ImportReference(superFinalize));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Ldarg_0));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Call,
                    Type.Methods.FirstOrDefault(Method => Method.Name == "get_GarbageCollectionHandle")));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_structUnRegisterImplementation)));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Ret));

                Type.Methods.Add(destructor);
            }
            else
            {
                var finalize = Type.Methods.FirstOrDefault(Method => Method.Name == "Finalize");

                if (finalize != null)
                {
                    ilProcessor = finalize.Body.GetILProcessor();

                    ilProcessor.InsertBefore(finalize.Body.Instructions[0], Instruction.Create(OpCodes.Ldarg_0));

                    ilProcessor.InsertBefore(finalize.Body.Instructions[1],
                        Instruction.Create(OpCodes.Call,
                            Type.Methods.FirstOrDefault(Method => Method.Name == "get_GarbageCollectionHandle")));

                    ilProcessor.InsertBefore(finalize.Body.Instructions[2],
                        Instruction.Create(OpCodes.Call,
                            ModuleDefinition.ImportReference(_structUnRegisterImplementation)));
                }
            }
        }

        private void ProcessStructGarbageCollectionHandle(TypeDefinition Type)
        {
            if (Type.Properties.Any(Property => Property.Name == "GarbageCollectionHandle"))
            {
                return;
            }

            var garbageCollectionHandle = new PropertyDefinition("GarbageCollectionHandle", PropertyAttributes.None,
                ModuleDefinition.TypeSystem.IntPtr);

            var garbageCollectionHandleBackingField = new FieldDefinition("<GarbageCollectionHandle>k__BackingField",
                FieldAttributes.Private, ModuleDefinition.TypeSystem.IntPtr);

            Type.Fields.Add(garbageCollectionHandleBackingField);

            var getter = new MethodDefinition("get_GarbageCollectionHandle",
                MethodAttributes.Public | MethodAttributes.HideBySig | MethodAttributes.SpecialName |
                MethodAttributes.NewSlot | MethodAttributes.Virtual | MethodAttributes.Final,
                ModuleDefinition.TypeSystem.IntPtr);

            var instructions = getter.Body.Instructions;

            instructions.Add(Instruction.Create(OpCodes.Ldarg_0));

            instructions.Add(Instruction.Create(OpCodes.Ldfld, garbageCollectionHandleBackingField));

            instructions.Add(Instruction.Create(OpCodes.Ret));

            Type.Methods.Add(getter);

            garbageCollectionHandle.GetMethod = getter;

            var setter = new MethodDefinition("set_GarbageCollectionHandle",
                MethodAttributes.Public | MethodAttributes.HideBySig | MethodAttributes.SpecialName |
                MethodAttributes.NewSlot | MethodAttributes.Virtual | MethodAttributes.Final,
                ModuleDefinition.TypeSystem.Void);

            setter.Parameters.Add(new ParameterDefinition(ModuleDefinition.TypeSystem.IntPtr));

            instructions = setter.Body.Instructions;

            instructions.Add(Instruction.Create(OpCodes.Ldarg_0));

            instructions.Add(Instruction.Create(OpCodes.Ldarg_1));

            instructions.Add(Instruction.Create(OpCodes.Stfld, garbageCollectionHandleBackingField));

            instructions.Add(Instruction.Create(OpCodes.Ret));

            Type.Methods.Add(setter);

            garbageCollectionHandle.SetMethod = setter;

            Type.Properties.Add(garbageCollectionHandle);
        }

        private void AddPathNameAttributeToUnrealType(TypeDefinition Type)
        {
            if (Type.CustomAttributes.Any(Attribute => Attribute.AttributeType == _pathAttributeType) == false)
            {
                var constructor = _pathAttributeType.GetConstructors().FirstOrDefault();

                var constructorRef = ModuleDefinition.ImportReference(constructor);

                var attribute = new CustomAttribute(constructorRef);

                var fullPath = GetPathName(Type);

                attribute.ConstructorArguments.Add(new CustomAttributeArgument(ModuleDefinition.TypeSystem.String,
                    fullPath));

                Type.CustomAttributes.Add(attribute);
            }
        }

        private static string GetPathName(TypeDefinition Type)
        {
            var name = Type.Name;

            return "/Script/CoreUObject." + (name.EndsWith("_C") || Type.IsEnum ? name : name.Substring(1));
        }

        private void ProcessUClassType(TypeDefinition Type)
        {
            foreach (var property in Type.Properties)
            {
                if (property.CustomAttributes.Any(Attribute =>
                        Attribute.AttributeType.FullName == "Script.Dynamic.UPropertyAttribute"))
                {
                    ProcessUClassProperty(Type, property);
                }
            }
        }

        private void ProcessUClassProperty(TypeDefinition Type, PropertyDefinition Property)
        {
            // 删除默认生成
            var fieldName = $"<{Property.Name}>k__BackingField";

            var backingField = Type.Fields.FirstOrDefault(Field =>
                Field.Name == fieldName && Field.FieldType.FullName == Property.PropertyType.FullName);

            if (backingField != null)
            {
                Type.Fields.Remove(backingField);
            }

            // 获取GarbageCollectionHandle访问器
            var getGarbageCollectionHandleMethod = GetGarbageCollectionHandle(Type);

            if (getGarbageCollectionHandleMethod == null)
            {
                throw new WeavingException("Not Found GetGarbageCollectionHandle property's getter of class " +
                                           Type.FullName);
            }

            // 修改setter
            if (Property.SetMethod != null)
            {
                var propertyType = Property.PropertyType;

                var propertySetMethod = GetPropertyAccessor(Property, _objectSetMethodMap);

                if (propertySetMethod != null)
                {
                    var field = Type.Fields.FirstOrDefault(Field =>
                        Field.Name == "__" + Property.Name &&
                        Field.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);

                    if (field == null)
                    {
                        field = new FieldDefinition("__" + Property.Name,
                            FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);

                        Type.Fields.Add(field);
                    }

                    var ilProcessor = Property.SetMethod.Body.GetILProcessor();

                    ilProcessor.Clear();

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(getGarbageCollectionHandleMethod)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_1));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(propertySetMethod)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found set function of type " + propertyType.FullName);
                }
            }

            if (Property.GetMethod != null)
            {
                var propertyType = Property.PropertyType;

                // 先找一下int, uint这些 函数的类型跟 property能直接对上的
                var propertyGetMethod = GetPropertyAccessor(Property, _objectGetMethodMap);

                if (propertyGetMethod != null)
                {
                    var field = Type.Fields.FirstOrDefault(Field =>
                        Field.Name == "__" + Property.Name &&
                        Field.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);

                    if (field == null)
                    {
                        field = new FieldDefinition("__" + Property.Name,
                            FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);

                        Type.Fields.Add(field);
                    }

                    var ilProcessor = Property.GetMethod.Body.GetILProcessor();

                    ilProcessor.Clear();

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(getGarbageCollectionHandleMethod)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(propertyGetMethod)));

                    if (propertyType.IsValueType == false)
                    {
                        ilProcessor.Append(Instruction.Create(OpCodes.Isinst,
                            ModuleDefinition.ImportReference(propertyType)));
                    }

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found get function of type " + propertyType.FullName);
                }
            }
        }

        private void ProcessUStructType(TypeDefinition Type)
        {
            foreach (var property in Type.Properties)
            {
                if (property.CustomAttributes.Any(Attribute =>
                        Attribute.AttributeType.FullName == "Script.Dynamic.UPropertyAttribute"))
                {
                    ProcessUStructProperty(Type, property);
                }
            }
        }

        private void ProcessUStructProperty(TypeDefinition Type, PropertyDefinition Property)
        {
            // 删除默认生成
            var fieldName = $"<{Property.Name}>k__BackingField";

            var backingField = Type.Fields.FirstOrDefault(Field =>
                Field.Name == fieldName && Field.FieldType.FullName == Property.PropertyType.FullName);

            if (backingField != null)
            {
                Type.Fields.Remove(backingField);
            }

            // 获取GarbageCollectionHandle访问器
            var getGarbageCollectionHandleMethod = GetGarbageCollectionHandle(Type);

            if (getGarbageCollectionHandleMethod == null)
            {
                throw new WeavingException("Not Found GetGarbageCollectionHandle property's getter of class " +
                                           Type.FullName);
            }

            // 修改setter
            if (Property.SetMethod != null)
            {
                var propertyType = Property.PropertyType;

                var propertySetMethod = GetPropertyAccessor(Property, _structSetMethodMap);

                if (propertySetMethod != null)
                {
                    var field = Type.Fields.FirstOrDefault(Field =>
                        Field.Name == "__" + Property.Name &&
                        Field.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);

                    if (field == null)
                    {
                        field = new FieldDefinition("__" + Property.Name,
                            FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);

                        Type.Fields.Add(field);
                    }

                    var ilProcessor = Property.SetMethod.Body.GetILProcessor();

                    ilProcessor.Clear();

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(getGarbageCollectionHandleMethod)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_1));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(propertySetMethod)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found set function of type " + propertyType.FullName);
                }
            }

            if (Property.GetMethod != null)
            {
                var propertyType = Property.PropertyType;

                // 先找一下int, uint这些 函数的类型跟 property能直接对上的
                var propertyGetMethod = GetPropertyAccessor(Property, _structGetMethodMap);

                if (propertyGetMethod != null)
                {
                    var field = Type.Fields.FirstOrDefault(Field =>
                        Field.Name == "__" + Property.Name &&
                        Field.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);

                    if (field == null)
                    {
                        field = new FieldDefinition("__" + Property.Name,
                            FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);

                        Type.Fields.Add(field);
                    }

                    var ilProcessor = Property.GetMethod.Body.GetILProcessor();

                    ilProcessor.Clear();

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(getGarbageCollectionHandleMethod)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, field));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(propertyGetMethod)));

                    if (propertyType.IsValueType == false)
                    {
                        ilProcessor.Append(Instruction.Create(OpCodes.Isinst,
                            ModuleDefinition.ImportReference(propertyType)));
                    }

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    throw new WeavingException("Not found get function of type " + propertyType.FullName);
                }
            }
        }

        private void ProcessRpcMethods(TypeDefinition Type)
        {
            List<MethodDefinition> rpcMethods = new List<MethodDefinition>();
            foreach(var method in Type.GetMethods())
            {
                if (method.CustomAttributes.Any(Attribute => Attribute.AttributeType.FullName == _ufunctionAttributeType.FullName) == false)
                    continue;
                if (method.CustomAttributes.Any(Attribute => Attribute.AttributeType.FullName == _serverAttributeType.FullName
                    || Attribute.AttributeType.FullName == _clientAttributeType.FullName 
                    || Attribute.AttributeType.FullName == _serverAttributeType.FullName
                    || Attribute.AttributeType.FullName == _netMulticastAttributeAttributeType.FullName) == false)
                    continue;
                rpcMethods.Add(method);
            }
            foreach (var method in rpcMethods)
            {
                Type.Methods.Add(CreateRpcMethodImplementation(method));
                ModifyRpcMethod(Type, method);
            }
        }

        private void ModifyRpcMethod(TypeDefinition Type, MethodDefinition method)
        {
            var hashField = new FieldDefinition("__" + method.Name, FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.IntPtr);
            Type.Fields.Add(hashField);

            method.Body.GetILProcessor().Clear();
            method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Nop));
            method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldarg_0));
            method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(_getGarbageCollectionHandle)));
            method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(hashField)));

            if (method.Parameters.Count > 0)
            {
                method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldc_I4, method.Parameters.Count));
                method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Newarr, ModuleDefinition.ImportReference(ModuleDefinition.TypeSystem.Object)));

                var i = 0;
                foreach (var param in method.Parameters)
                {
                    method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Dup));
                    method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldc_I4, i));
                    method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldarg_S, param));
                    if (param.ParameterType.IsValueType)
                    {
                        method.Body.GetILProcessor().Append(param.ParameterType.Resolve().IsEnum
                            ? Instruction.Create(OpCodes.Box,
                                ModuleDefinition.ImportReference(param.ParameterType.Resolve()
                                    .GetEnumUnderlyingType()))
                            : Instruction.Create(OpCodes.Box,
                                ModuleDefinition.ImportReference(param.ParameterType)));
                    }
                    method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Stelem_Ref));
                    i++;
                }
                method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(_functionReflection2Implementation)));
            }
            else
            {
                method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Call, ModuleDefinition.ImportReference(_functionReflection0Implementation)));
            }
            method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ret));
            method.Body.Variables.Clear();
            method.Body.InitLocals = false;
        }
        private MethodDefinition CreateRpcMethodImplementation(MethodDefinition method)
        {
            var constructor = _overrideAttributeType.GetConstructors().FirstOrDefault();
            var constructorRef = ModuleDefinition.ImportReference(constructor);
            var attribute = new CustomAttribute(constructorRef);
            var newMethod = new MethodDefinition(method.Name + "_Implementation", MethodAttributes.Public, method.ReturnType);
            newMethod.CustomAttributes.Add(attribute);
            foreach (var param in method.Parameters)
            {
                newMethod.Parameters.Add(new ParameterDefinition(param.ParameterType));
            }
            foreach (var variable in method.Body.Variables)
            {
                newMethod.Body.Variables.Add(new VariableDefinition(variable.VariableType));
            }
            newMethod.Body.InitLocals = method.Body.InitLocals;
            newMethod.Body.GetILProcessor().Clear();
            foreach (var instruction in method.Body.Instructions)
            {
                if (instruction == null)
                    continue;
                var opCode = instruction.OpCode;
                var operand = instruction.Operand;

                if (operand != null)
                {
                    if (operand is ParameterDefinition parameter)
                    {
                        var index = method.Parameters.IndexOf(parameter);
                        if (index < 0)
                            throw new WeavingException("not found param:" + parameter.ToString());
                        var newParameter = newMethod.Parameters[index];
                        newMethod.Body.GetILProcessor().Append(Instruction.Create(opCode, newParameter));
                        continue;
                    }
                    else if (operand is VariableDefinition variable)
                    {
                        var index = method.Body.Variables.IndexOf(variable);
                        if (index < 0)
                            throw new WeavingException("not found param:" + variable.ToString());
                        var newvariable = newMethod.Body.Variables[index];
                        newMethod.Body.GetILProcessor().Append(Instruction.Create(opCode, newvariable));
                        continue;
                    }
                }
                newMethod.Body.GetILProcessor().Append(instruction);
            }
            return newMethod;
        }
        private MethodDefinition GetPropertyAccessor(PropertyDefinition Property,
            Dictionary<string, MethodDefinition> MethodMap)
        {
            var type = Property.PropertyType.Resolve();

            if (MethodMap.TryGetValue(Property.PropertyType.FullName, out var propertyGetMethod) == false)
            {
                // 然后找一下enum
                if (type.IsEnum)
                {
                    if (MethodMap.TryGetValue(type.GetEnumUnderlyingType().FullName, out propertyGetMethod) == false)
                    {
                        throw new WeavingException("Not found accessor Property Method: named " + Property.Name +
                                                   " property type is " +
                                                   type.Resolve().GetEnumUnderlyingType().Resolve().FullName +
                                                   " of type " + "type " + type.FullName);
                    }
                }

                if (GetGarbageCollectionHandle(type.Resolve()) != null)
                {
                    propertyGetMethod = MethodMap[ModuleDefinition.TypeSystem.Object.FullName];
                }
            }

            return propertyGetMethod;
        }

        private MethodDefinition GetGarbageCollectionHandle(TypeDefinition Type)
        {
            var property = Type.Properties.FirstOrDefault(Property => Property.Name == "GarbageCollectionHandle" &&
                                                                      Property.PropertyType.FullName ==
                                                                      ModuleDefinition.TypeSystem.IntPtr.FullName &&
                                                                      Property.GetMethod != null);

            if (property != null)
            {
                return property.GetMethod;
            }

            return Type.BaseType != null ? GetGarbageCollectionHandle(Type.BaseType.Resolve()) : null;
        }

        private void GetAllDynamic()
        {
            foreach (var type in ModuleDefinition.Types)
            {
                if (type.CustomAttributes.Any(Attribute =>
                        Attribute.AttributeType.FullName == "Script.Dynamic.UClassAttribute"))
                {
                    _classTypes.Add(type);
                }

                else if (type.CustomAttributes.Any(Attribute =>
                             Attribute.AttributeType.FullName == "Script.Dynamic.UStructAttribute"))
                {
                    _structTypes.Add(type);
                }

                else if (type.CustomAttributes.Any(Attribute =>
                             Attribute.AttributeType.FullName == "Script.Dynamic.UEnumAttribute"))
                {
                    _enumTypes.Add(type);
                }

                else if (type.CustomAttributes.Any(Attribute =>
                             Attribute.AttributeType.FullName == "Script.Dynamic.UInterfaceAttribute"))
                {
                    _interfaceTypes.Add(type);
                }

                else if (type.IsInterface && type.Interfaces.ToList().Any(Interface =>
                             Interface.InterfaceType.FullName == "Script.CoreUObject.IInterface"))
                {
                    _interfaceTypes.Add(type);
                }
            }
        }

        private void SearchAllPropertyAccessors(ModuleDefinition Definition)
        {
            var propertyImplementationClass = Definition.GetType("Script.Library.FPropertyImplementation");

            foreach (var method in propertyImplementationClass.Methods)
            {
                if (method.IsStatic == false)
                {
                    continue;
                }

                // Get函数
                if (method.ReturnType.FullName != ModuleDefinition.TypeSystem.Void.FullName &&
                    method.Name.IndexOf("FProperty_Get", StringComparison.Ordinal) >= 0 &&
                    method.Name.IndexOf("PropertyImplementation", StringComparison.Ordinal) > 0)
                {
                    var propertyType = method.ReturnType;

                    if (method.Name.IndexOf("FProperty_GetObject", StringComparison.Ordinal) >= 0)
                    {
                        // UObject
                        _objectGetMethodMap.Add(propertyType.FullName, method);
                    }
                    else if (method.Name.IndexOf("FProperty_GetStruct", StringComparison.Ordinal) >= 0)
                    {
                        // UStruct
                        _structGetMethodMap.Add(propertyType.FullName, method);
                    }
                }
                // Set函数
                else if (method.ReturnType.FullName == ModuleDefinition.TypeSystem.Void.FullName &&
                         method.Name.IndexOf("FProperty_Set", StringComparison.Ordinal) >= 0 &&
                         method.Name.IndexOf("PropertyImplementation", StringComparison.Ordinal) > 0 &&
                         method.Parameters.Count == 3)
                {
                    var propertyType = method.Parameters[2].ParameterType;

                    if (method.Name.IndexOf("FProperty_SetObject", StringComparison.Ordinal) >= 0)
                    {
                        // UObject
                        _objectSetMethodMap.Add(propertyType.FullName, method);
                    }
                    else if (method.Name.IndexOf("FProperty_SetStruct", StringComparison.Ordinal) >= 0)
                    {
                        // UStruct
                        _structSetMethodMap.Add(propertyType.FullName, method);
                    }
                }
            }
        }

        private void GetAllMeta()
        {
            var definition = ModuleDefinition;

            if (definition.Name != "UE.dll")
            {
                definition = ModuleDefinition.ReadModule("../../Content/Script/UE.dll");
            }

            _pathAttributeType = definition.GetType("Script.CoreUObject.PathNameAttribute");

            _structRegisterImplementation = definition.GetType("Script.Library.UStructImplementation").Methods
                .FirstOrDefault(Method => Method.Name == "UStruct_RegisterImplementation");

            _structUnRegisterImplementation = definition.GetType("Script.Library.UStructImplementation").Methods
                .FirstOrDefault(Method => Method.Name == "UStruct_UnRegisterImplementation");

            _ufunctionAttributeType = definition.GetType("Script.Dynamic.UFunctionAttribute");

            _clientAttributeType = definition.GetType("Script.Dynamic.ClientAttribute");

            _serverAttributeType = definition.GetType("Script.Dynamic.ServerAttribute");

            _netMulticastAttributeAttributeType = definition.GetType("Script.Dynamic.NetMulticastAttribute");

            _overrideAttributeType = definition.GetType("Script.CoreUObject.OverrideAttribute");

            _functionReflection0Implementation = definition.GetType("Script.Library.FFunctionImplementation").Methods
                .FirstOrDefault(Method => Method.Name == "FFunction_Reflection0Implementation");

            _functionReflection2Implementation = definition.GetType("Script.Library.FFunctionImplementation").Methods
                .FirstOrDefault(Method => Method.Name == "FFunction_Reflection2Implementation");

            _getGarbageCollectionHandle = definition.GetType("Script.CoreUObject.UObject").Methods
                .FirstOrDefault(Method => Method.Name == "get_GarbageCollectionHandle");
            SearchAllPropertyAccessors(definition);
        }
    }
}