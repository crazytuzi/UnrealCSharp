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
            yield return "";
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

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Ldarg_0));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(ModuleDefinition.TypeSystem.Object.Resolve().Methods
                        .FirstOrDefault(Method => Method.Name == "Finalize"))));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Endfinally));

                destructor.Body.Instructions.Add(Instruction.Create(OpCodes.Ret));

                destructor.Body.Instructions.Insert(3,
                    Instruction.Create(OpCodes.Leave_S, destructor.Body.Instructions[6]));

                var exceptionHandler = new ExceptionHandler(ExceptionHandlerType.Finally)
                {
                    TryStart = destructor.Body.Instructions[0],
                    TryEnd = destructor.Body.Instructions[4],
                    HandlerStart = destructor.Body.Instructions[4],
                    HandlerEnd = destructor.Body.Instructions[7]
                };

                destructor.Body.ExceptionHandlers.Add(exceptionHandler);

                Type.Methods.Add(destructor);
            }
            else
            {
                var finalize = Type.Methods.FirstOrDefault(Method => Method.Name == "Finalize");

                if (finalize == null)
                {
                    return;
                }

                ilProcessor = finalize.Body.GetILProcessor();

                ilProcessor.InsertBefore(finalize.Body.Instructions[0], Instruction.Create(OpCodes.Ldarg_0));

                ilProcessor.InsertBefore(finalize.Body.Instructions[1],
                    Instruction.Create(OpCodes.Call,
                        Type.Methods.FirstOrDefault(Method => Method.Name == "get_GarbageCollectionHandle")));

                ilProcessor.InsertBefore(finalize.Body.Instructions[2],
                    Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(_structUnRegisterImplementation)));

                finalize.Body.ExceptionHandlers[0].TryStart = finalize.Body.Instructions[0];
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

                MethodDefinition propertySetMethod;

                var getParamGarbageCollectionHandle = GetGarbageCollectionHandle(Property.PropertyType);

                if (getParamGarbageCollectionHandle != null)
                {
                    _objectSetMethodMap.TryGetValue(ModuleDefinition.TypeSystem.IntPtr.FullName, out propertySetMethod);
                }
                else
                {
                    propertySetMethod = GetPropertyAccessor(Property, _objectSetMethodMap);
                }

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

                    if (getParamGarbageCollectionHandle != null)
                    {
                        var zeroField = ModuleDefinition.TypeSystem.IntPtr.Resolve().Fields
                            .First(Field => Field.Name == "Zero");

                        var il2 = Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(zeroField));

                        var il4 = Instruction.Create(OpCodes.Ldarg_1);

                        var il5 = Instruction.Create(OpCodes.Call,
                            ModuleDefinition.ImportReference(getParamGarbageCollectionHandle));

                        var il6 = Instruction.Create(OpCodes.Nop);

                        var il1 = Instruction.Create(OpCodes.Brtrue_S, il4);

                        var il3 = Instruction.Create(OpCodes.Br_S, il6);

                        ilProcessor.Append(il1);

                        ilProcessor.Append(il2);

                        ilProcessor.Append(il3);

                        ilProcessor.Append(il4);

                        ilProcessor.Append(il5);

                        ilProcessor.Append(il6);
                    }

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

                MethodDefinition propertySetMethod;

                var getParamGarbageCollectionHandle = GetGarbageCollectionHandle(Property.PropertyType);

                if (getParamGarbageCollectionHandle != null)
                {
                    _structSetMethodMap.TryGetValue(ModuleDefinition.TypeSystem.IntPtr.FullName, out propertySetMethod);
                }
                else
                {
                    propertySetMethod = GetPropertyAccessor(Property, _structSetMethodMap);
                }

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

                    if (getParamGarbageCollectionHandle != null)
                    {
                        var zeroField = ModuleDefinition.TypeSystem.IntPtr.Resolve().Fields
                            .First(Field => Field.Name == "Zero");

                        var il2 = Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(zeroField));

                        var il4 = Instruction.Create(OpCodes.Ldarg_1);

                        var il5 = Instruction.Create(OpCodes.Call,
                            ModuleDefinition.ImportReference(getParamGarbageCollectionHandle));

                        var il6 = Instruction.Create(OpCodes.Nop);

                        var il1 = Instruction.Create(OpCodes.Brtrue_S, il4);

                        var il3 = Instruction.Create(OpCodes.Br_S, il6);

                        ilProcessor.Append(il1);

                        ilProcessor.Append(il2);

                        ilProcessor.Append(il3);

                        ilProcessor.Append(il4);

                        ilProcessor.Append(il5);

                        ilProcessor.Append(il6);
                    }

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
            var rpcMethods = Type.GetMethods()
                .Where(Method => Method.CustomAttributes.Any(Attribute =>
                    Attribute.AttributeType.FullName == _ufunctionAttributeType.FullName))
                .Where(Method => Method.CustomAttributes.Any(Attribute =>
                    Attribute.AttributeType.FullName == _serverAttributeType.FullName ||
                    Attribute.AttributeType.FullName == _clientAttributeType.FullName ||
                    Attribute.AttributeType.FullName == _netMulticastAttributeAttributeType.FullName))
                .ToList();

            foreach (var method in rpcMethods)
            {
                Type.Methods.Add(CreateRpcMethodImplementation(method));

                ModifyRpcMethod(Type, method);
            }
        }

        private static Instruction GetTypeStind(TypeReference Type)
        {
            switch (Type.MetadataType)
            {
                case MetadataType.Boolean:
                    return Instruction.Create(OpCodes.Stind_I1);
                case MetadataType.Byte:
                    return Instruction.Create(OpCodes.Stind_I1);
                case MetadataType.Int16:
                    return Instruction.Create(OpCodes.Stind_I2);
                case MetadataType.Int32:
                    return Instruction.Create(OpCodes.Stind_I4);
                case MetadataType.Int64:
                    return Instruction.Create(OpCodes.Stind_I8);
                case MetadataType.SByte:
                    return Instruction.Create(OpCodes.Stind_I1);
                case MetadataType.UInt16:
                    return Instruction.Create(OpCodes.Stind_I2);
                case MetadataType.UInt32:
                    return Instruction.Create(OpCodes.Stind_I4);
                case MetadataType.UInt64:
                    return Instruction.Create(OpCodes.Stind_I8);
                case MetadataType.Single:
                    return Instruction.Create(OpCodes.Stind_R4);
                case MetadataType.Double:
                    return Instruction.Create(OpCodes.Stind_R8);
                default:
                {
                    if (Type.Resolve().IsEnum)
                    {
                        return GetTypeStind(Type.Resolve().GetEnumUnderlyingType());
                    }

                    break;
                }
            }

            return Instruction.Create(OpCodes.Stind_I);
        }

        private static sbyte GetTypeSize(TypeReference Type)
        {
            switch (Type.MetadataType)
            {
                case MetadataType.Boolean:
                case MetadataType.Byte:
                    return sizeof(bool);
                case MetadataType.Int16:
                    return sizeof(short);
                case MetadataType.Int32:
                    return sizeof(int);
                case MetadataType.Int64:
                    return sizeof(long);
                case MetadataType.SByte:
                    return sizeof(sbyte);
                case MetadataType.UInt16:
                    return sizeof(ushort);
                case MetadataType.UInt32:
                    return sizeof(uint);
                case MetadataType.UInt64:
                    return sizeof(ulong);
                case MetadataType.Single:
                    return sizeof(float);
                case MetadataType.Double:
                    return sizeof(double);
                default:
                {
                    if (Type.Resolve().IsEnum)
                    {
                        return GetTypeSize(Type.Resolve().GetEnumUnderlyingType());
                    }

                    break;
                }
            }

            return (sbyte)IntPtr.Size;
        }

        private void ModifyRpcMethod(TypeDefinition Type, MethodDefinition Method)
        {
            var hashField = new FieldDefinition("__" + Method.Name, FieldAttributes.Private | FieldAttributes.Static,
                ModuleDefinition.TypeSystem.IntPtr);

            Type.Fields.Add(hashField);

            Method.Body.GetILProcessor().Clear();

            if (Method.Parameters.Count > 0)
            {
                sbyte BufferSize = 0;

                foreach (var param in Method.Parameters)
                {
                    BufferSize += GetTypeSize(param.ParameterType);
                }

                Method.Body.Variables.Add(new VariableDefinition(new PointerType(ModuleDefinition.TypeSystem.Byte)));

                Method.Body.InitLocals = true;

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Nop));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Nop));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldc_I4_S, BufferSize));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Conv_U));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Localloc));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Stloc_0));

                BufferSize = 0;

                foreach (var param in Method.Parameters)
                {
                    Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldloc_0));

                    if (BufferSize != 0)
                    {
                        Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldc_I4_S, BufferSize));

                        Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Add));
                    }

                    BufferSize += GetTypeSize(param.ParameterType);

                    Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldarg_S, param));

                    var paramGetGarbageCollectionHandleMethod = GetGarbageCollectionHandle(param.ParameterType);

                    if (paramGetGarbageCollectionHandleMethod != null)
                    {
                        var zeroField = ModuleDefinition.TypeSystem.IntPtr.Resolve().Fields
                            .First(Field => Field.Name == "Zero");

                        var i3 = Instruction.Create(OpCodes.Ldarg_S, param);

                        var i0 = Instruction.Create(OpCodes.Brtrue_S, i3);

                        var i1 = Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(zeroField));

                        var i5 = GetTypeStind(param.ParameterType);

                        var i2 = Instruction.Create(OpCodes.Br_S, i5);

                        var i4 = Instruction.Create(OpCodes.Call,
                            ModuleDefinition.ImportReference(paramGetGarbageCollectionHandleMethod));

                        Method.Body.GetILProcessor().Append(i0);

                        Method.Body.GetILProcessor().Append(i1);

                        Method.Body.GetILProcessor().Append(i2);

                        Method.Body.GetILProcessor().Append(i3);

                        Method.Body.GetILProcessor().Append(i4);

                        Method.Body.GetILProcessor().Append(i5);
                    }
                    else
                    {
                        Method.Body.GetILProcessor().Append(GetTypeStind(param.ParameterType));
                    }
                }
            }

            Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Nop));

            Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldarg_0));

            Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Call,
                ModuleDefinition.ImportReference(_getGarbageCollectionHandle)));

            Method.Body.GetILProcessor()
                .Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(hashField)));

            if (Method.Parameters.Count > 0)
            {
                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldloc_0));
            }

            Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Call,
                ModuleDefinition.ImportReference(Method.Parameters.Count > 0
                    ? _functionReflection2Implementation
                    : _functionReflection0Implementation)));

            Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ret));

            Method.Body.ExceptionHandlers.Clear();
        }

        private MethodDefinition CreateRpcMethodImplementation(MethodDefinition Method)
        {
            var constructor = _overrideAttributeType.GetConstructors().FirstOrDefault();

            var constructorRef = ModuleDefinition.ImportReference(constructor);

            var attribute = new CustomAttribute(constructorRef);

            var newMethod = new MethodDefinition(Method.Name + "_Implementation", MethodAttributes.Public,
                Method.ReturnType);

            newMethod.CustomAttributes.Add(attribute);

            foreach (var param in Method.Parameters)
            {
                newMethod.Parameters.Add(new ParameterDefinition(param.ParameterType));
            }

            foreach (var variable in Method.Body.Variables)
            {
                newMethod.Body.Variables.Add(new VariableDefinition(variable.VariableType));
            }

            newMethod.Body.InitLocals = Method.Body.InitLocals;

            if (Method.HasBody)
            {
                newMethod.Body.InitLocals = true;

                foreach (var variableDefinition in Method.Body.Variables)
                {
                    newMethod.Body.Variables.Add(variableDefinition);
                }

                foreach (var exceptionHandler in Method.Body.ExceptionHandlers)
                {
                    newMethod.Body.ExceptionHandlers.Add(exceptionHandler);
                }

                foreach (var instruction in Method.Body.Instructions)
                {
                    newMethod.Body.Instructions.Add(instruction);
                }

                newMethod.Body.OptimizeMacros();
            }

            return newMethod;
        }

        private MethodDefinition GetPropertyAccessor(PropertyReference Property,
            IReadOnlyDictionary<string, MethodDefinition> MethodMap)
        {
            var type = Property.PropertyType.Resolve();

            if (MethodMap.TryGetValue(Property.PropertyType.FullName, out var propertyGetMethod))
            {
                return propertyGetMethod;
            }

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

            return propertyGetMethod;
        }

        private MethodReference GetGarbageCollectionHandle(TypeDefinition Type)
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

        private MethodReference GetGarbageCollectionHandle(TypeReference Type)
        {
            var method = GetGarbageCollectionHandle(Type.Resolve());

            if (method == null)
            {
                return null;
            }

            if (Type.IsGenericInstance)
            {
                var arguments = new List<TypeReference>();

                foreach (var argument in ((GenericInstanceType)Type).GenericArguments)
                {
                    arguments.Add(argument.Resolve());
                }

                return method.MakeHostInstanceGeneric(arguments.ToArray());
            }
            else
            {
                return method;
            }
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

            if (definition.Name != "")
            {
                definition = ModuleDefinition.ReadModule("");
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
                .FirstOrDefault(Method => Method.Name == "FFunction_GenericCall24Implementation");

            _functionReflection2Implementation = definition.GetType("Script.Library.FFunctionImplementation").Methods
                .FirstOrDefault(Method => Method.Name == "FFunction_GenericCall26Implementation");

            _getGarbageCollectionHandle = definition.GetType("Script.CoreUObject.UObject").Methods
                .FirstOrDefault(Method => Method.Name == "get_GarbageCollectionHandle");

            SearchAllPropertyAccessors(definition);
        }
    }

    public static class CecilExtensions
    {
        public static MethodReference MakeHostInstanceGeneric(this MethodReference Self, params TypeReference[] Args)
        {
            var reference =
                new MethodReference(Self.Name, Self.ReturnType, Self.DeclaringType.MakeGenericInstanceType(Args))
                {
                    HasThis = Self.HasThis,
                    ExplicitThis = Self.ExplicitThis,
                    CallingConvention = Self.CallingConvention
                };

            foreach (var parameter in Self.Parameters)
            {
                reference.Parameters.Add(new ParameterDefinition(parameter.ParameterType));
            }

            foreach (var genericParam in Self.GenericParameters)
            {
                reference.GenericParameters.Add(new GenericParameter(genericParam.Name, reference));
            }

            return reference;
        }
    }
}