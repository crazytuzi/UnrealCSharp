using System;
using Fody;
using Mono.Cecil;
using Mono.Cecil.Cil;
using Mono.Cecil.Rocks;
using System.Collections.Generic;
#if WITH_LEANCLR
using System.Globalization;
#endif
using System.IO;
using System.Linq;

namespace Weavers
{
    public class UnrealTypeWeaver : BaseModuleWeaver
    {
        private readonly List<TypeDefinition> _classTypes = new List<TypeDefinition>();

        private readonly List<TypeDefinition> _structTypes = new List<TypeDefinition>();

        private readonly List<TypeDefinition> _enumTypes = new List<TypeDefinition>();

        private readonly List<TypeDefinition> _interfaceTypes = new List<TypeDefinition>();

        private MethodDefinition _getObjectPropertyImplementation;

        private MethodDefinition _setObjectPropertyImplementation;

        private MethodDefinition _getStructPropertyImplementation;

        private MethodDefinition _setStructPropertyImplementation;

        private MethodDefinition _structRegisterImplementation;

        private MethodDefinition _structUnRegisterImplementation;

        private MethodDefinition _genericCall24Implementation;

        private MethodDefinition _genericCall26Implementation;

        private MethodDefinition _getHandle;

        private MethodDefinition _getObject;

        private TypeDefinition _pathNameAttributeType;

        private TypeDefinition _ufunctionAttributeType;

        private TypeDefinition _serverAttributeType;

        private TypeDefinition _clientAttributeType;

        private TypeDefinition _netMulticastAttributeType;

        private TypeDefinition _notPlaceableAttributeType;

        private TypeDefinition _overrideAttributeType;

        private bool bHasMetaError;

        public override void Execute()
        {
            if (!GetAllMeta())
            {
                return;
            }

            GetAllDynamic();

            // 处理PathName
            _classTypes.ForEach(AddPathNameAttributeToUnrealType);

            _structTypes.ForEach(AddPathNameAttributeToUnrealType);

            _enumTypes.ForEach(AddPathNameAttributeToUnrealType);

            _interfaceTypes.ForEach(AddPathNameAttributeToUnrealType);

            // 处理结构体注册和注销
            _structTypes.ForEach(ProcessStructRegister);

            // 处理UProperty
            _classTypes.ForEach(ProcessUClassType);

            _structTypes.ForEach(ProcessUStructType);

            _classTypes.ForEach(ProcessRpcMethods);
        }

        public override IEnumerable<string> GetAssembliesForScanning()
        {
            yield return "UENamePlaceholder";

            yield return "GameNamePlaceholder";
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
                    ModuleDefinition.ImportReference(_getHandle)));

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
                        ModuleDefinition.ImportReference(_getHandle)));

                ilProcessor.InsertBefore(finalize.Body.Instructions[2],
                    Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(_structUnRegisterImplementation)));

                finalize.Body.ExceptionHandlers[0].TryStart = finalize.Body.Instructions[0];
            }
        }

        private void AddPathNameAttributeToUnrealType(TypeDefinition Type)
        {
            if (Type.CustomAttributes.Any(Attribute =>
                    Attribute.AttributeType.FullName == _pathNameAttributeType.FullName) == false)
            {
                var constructor = _pathNameAttributeType.GetConstructors().FirstOrDefault();

                var constructorRef = ModuleDefinition.ImportReference(constructor);

                var attribute = new CustomAttribute(constructorRef);

                var fullPath = GetPathName(Type);

                attribute.ConstructorArguments.Add(new CustomAttributeArgument(ModuleDefinition.TypeSystem.String,
                    fullPath));

                Type.CustomAttributes.Add(attribute);
            }

            if (Type.Name.EndsWith("_C"))
            {
                if (Type.CustomAttributes.Any(Attribute =>
                        Attribute.AttributeType.FullName == _notPlaceableAttributeType.FullName) == false)
                {
                    var constructor = _notPlaceableAttributeType.GetConstructors().FirstOrDefault();

                    var constructorRef = ModuleDefinition.ImportReference(constructor);

                    var attribute = new CustomAttribute(constructorRef);

                    Type.CustomAttributes.Add(attribute);
                }
            }
        }

        private static string GetPathName(TypeDefinition Type)
        {
            var name = Type.Name;

            return "/Script/CoreUObject." + (name.EndsWith("_C") || Type.IsEnum ? name : name.Substring(1));
        }

#if WITH_LEANCLR
        private static string GetRootNamespace(TypeReference Type)
        {
            var root = Type;

            while (root.DeclaringType != null)
            {
                root = root.DeclaringType;
            }

            return root.Namespace;
        }

        private void EmitPropertyAttributesField(TypeDefinition Type, PropertyDefinition Property)
        {
            var lines = new List<string>();

            foreach (var attr in Property.CustomAttributes)
            {
                var attrType = attr.AttributeType;

                if (GetRootNamespace(attrType) != "Script.Dynamic" ||
                    attrType.Name == "UPropertyAttribute")
                {
                    continue;
                }

                var parts = new List<string>();

                if (attr.HasConstructorArguments)
                {
                    foreach (var arg in attr.ConstructorArguments)
                    {
                        var value = arg.Value;

                        string text;

                        if (value == null)
                        {
                            text = string.Empty;
                        }
                        else if (value is IFormattable formattable)
                        {
                            text = formattable.ToString(null, CultureInfo.InvariantCulture);
                        }
                        else
                        {
                            text = value.ToString();
                        }

                        parts.Add(text);
                    }
                }

                parts.Insert(0, parts.Count.ToString(CultureInfo.InvariantCulture));

                parts.Insert(0, attrType.FullName.Replace('/', '+'));

                lines.Add(string.Join("|", parts));
            }

            if (lines.Count == 0)
            {
                return;
            }

            var encoded = string.Join("\n", lines);

            var attrsField = new FieldDefinition("__" + Property.Name + "_Attrs",
                FieldAttributes.Private | FieldAttributes.Static | FieldAttributes.InitOnly,
                ModuleDefinition.TypeSystem.String);

            Type.Fields.Add(attrsField);

            var cctor = Type.Methods.FirstOrDefault(Method =>
                Method.Name == ".cctor" && Method.IsStatic && !Method.HasParameters);

            if (cctor == null)
            {
                cctor = new MethodDefinition(".cctor",
                    MethodAttributes.Static | MethodAttributes.SpecialName |
                    MethodAttributes.RTSpecialName | MethodAttributes.Private,
                    ModuleDefinition.TypeSystem.Void);

                cctor.Body.Instructions.Add(Instruction.Create(OpCodes.Ret));

                Type.Methods.Add(cctor);
            }

            var il = cctor.Body.GetILProcessor();

            var firstInstr = il.Body.Instructions[0];

            il.InsertBefore(firstInstr, Instruction.Create(OpCodes.Ldstr, encoded));

            il.InsertBefore(firstInstr, Instruction.Create(OpCodes.Stsfld,
                ModuleDefinition.ImportReference(attrsField)));
        }
#endif

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

        private static bool IsBackingFieldReference(Instruction Instruction, FieldDefinition BackingField)
        {
            return Instruction.Operand is FieldReference Field && Field.Resolve() == BackingField;
        }

        private static bool RewriteBackingFieldReferences(TypeDefinition Type, PropertyDefinition Property,
            FieldDefinition BackingField)
        {
            var Methods = Type.Methods
                .Where(Method => Method.HasBody)
                .Where(Method => Method != Property.GetMethod && Method != Property.SetMethod)
                .ToList();

            var Instructions = Methods
                .SelectMany(Method => Method.Body.Instructions)
                .Where(Instruction => IsBackingFieldReference(Instruction, BackingField))
                .ToList();

            if (Instructions.Count == 0)
            {
                return true;
            }

            if (BackingField.IsStatic || Instructions.Any(Instruction => Instruction.OpCode != OpCodes.Stfld))
            {
                return false;
            }

            foreach (var Method in Methods)
            {
                var ILProcessor = Method.Body.GetILProcessor();

                foreach (var Instruction in Method.Body.Instructions.ToList())
                {
                    if (IsBackingFieldReference(Instruction, BackingField) &&
                        Instruction.OpCode == OpCodes.Stfld)
                    {
                        ILProcessor.InsertAfter(Instruction, Instruction.Create(OpCodes.Pop));

                        ILProcessor.InsertAfter(Instruction, Instruction.Create(OpCodes.Pop));

                        ILProcessor.Remove(Instruction);
                    }
                }
            }

            return true;
        }

        private void ProcessUClassProperty(TypeDefinition Type, PropertyDefinition Property)
        {
            // 删除默认生成
            var fieldName = $"<{Property.Name}>k__BackingField";

            var backingField = Type.Fields.FirstOrDefault(Field =>
                Field.Name == fieldName && Field.FieldType.FullName == Property.PropertyType.FullName);

            if (backingField != null && RewriteBackingFieldReferences(Type, Property, backingField))
            {
                Type.Fields.Remove(backingField);
            }

#if WITH_LEANCLR
            EmitPropertyAttributesField(Type, Property);
#endif

            // 修改setter
            if (Property.SetMethod != null)
            {
                var bIsCompound = IsCompound(Property.PropertyType);

                var field = Type.Fields.FirstOrDefault(Field =>
                    Field.Name == "__" + Property.Name &&
                    Field.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);

                if (field == null)
                {
                    field = new FieldDefinition("__" + Property.Name,
                        FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);

                    Type.Fields.Add(field);
                }

                var BufferSize = GetTypeSize(Property.PropertyType);

                Property.SetMethod.Body.Variables.Clear();

                Property.SetMethod.Body.ExceptionHandlers.Clear();

                Property.SetMethod.Body.Variables.Add(
                    new VariableDefinition(new PointerType(ModuleDefinition.TypeSystem.Byte)));

                Property.SetMethod.Body.InitLocals = true;

                var ilProcessor = Property.SetMethod.Body.GetILProcessor();

                ilProcessor.Clear();

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(GetLdcI4(BufferSize));

                ilProcessor.Append(Instruction.Create(OpCodes.Conv_U));

                ilProcessor.Append(Instruction.Create(OpCodes.Localloc));

                ilProcessor.Append(Instruction.Create(OpCodes.Stloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_1));

                if (bIsCompound)
                {
                    var zeroField = ModuleDefinition.TypeSystem.IntPtr.Resolve().Fields
                        .First(Field => Field.Name == "Zero");

                    var ib = Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(zeroField));

                    var i12 = Instruction.Create(OpCodes.Ldarg_1);

                    var i13 = Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(_getHandle));

                    var i18 = GetTypeStind(Property.PropertyType);

                    var i9 = Instruction.Create(OpCodes.Brtrue_S, i12);

                    var i10 = Instruction.Create(OpCodes.Br_S, i18);

                    ilProcessor.Append(i9);

                    ilProcessor.Append(ib);

                    ilProcessor.Append(i10);

                    ilProcessor.Append(i12);

                    ilProcessor.Append(i13);

                    ilProcessor.Append(i18);
                }
                else
                {
                    ilProcessor.Append(GetTypeStind(Property.PropertyType));
                }

                ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_getHandle)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(field)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_setObjectPropertyImplementation)));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Ret));
            }

            if (Property.GetMethod != null)
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

                var BufferSize = GetTypeSize(Property.PropertyType);

                var bIsCompound = IsCompound(Property.PropertyType);

                Property.GetMethod.Body.Variables.Clear();

                Property.GetMethod.Body.ExceptionHandlers.Clear();

                Property.GetMethod.Body.Variables.Add(
                    new VariableDefinition(new PointerType(ModuleDefinition.TypeSystem.Byte)));

                if (!bIsCompound)
                {
                    Property.GetMethod.Body.Variables.Add(
                        new VariableDefinition(ModuleDefinition.ImportReference(Property.PropertyType)));
                }

                Property.GetMethod.Body.InitLocals = true;

                var ilProcessor = Property.GetMethod.Body.GetILProcessor();

                ilProcessor.Clear();

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(GetLdcI4(BufferSize));

                ilProcessor.Append(Instruction.Create(OpCodes.Conv_U));

                ilProcessor.Append(Instruction.Create(OpCodes.Localloc));

                ilProcessor.Append(Instruction.Create(OpCodes.Stloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_getHandle)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(field)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_getObjectPropertyImplementation)));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                if (bIsCompound)
                {
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldind_I));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(_getObject)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Castclass,
                        ModuleDefinition.ImportReference(Property.PropertyType)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    ilProcessor.Append(GetTypeLdind(Property.PropertyType));

                    ilProcessor.Append(Instruction.Create(OpCodes.Stloc_1));

                    var i1 = Instruction.Create(OpCodes.Ldloc_1);

                    var i0 = Instruction.Create(OpCodes.Br_S, i1);

                    ilProcessor.Append(i0);

                    ilProcessor.Append(i1);

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
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

            if (backingField != null && RewriteBackingFieldReferences(Type, Property, backingField))
            {
                Type.Fields.Remove(backingField);
            }

#if WITH_LEANCLR
            EmitPropertyAttributesField(Type, Property);
#endif

            // 修改setter
            if (Property.SetMethod != null)
            {
                var bIsCompound = IsCompound(Property.PropertyType);

                var field = Type.Fields.FirstOrDefault(Field =>
                    Field.Name == "__" + Property.Name &&
                    Field.FieldType.FullName == ModuleDefinition.TypeSystem.UInt32.FullName);

                if (field == null)
                {
                    field = new FieldDefinition("__" + Property.Name,
                        FieldAttributes.Private | FieldAttributes.Static, ModuleDefinition.TypeSystem.UInt32);

                    Type.Fields.Add(field);
                }

                var BufferSize = GetTypeSize(Property.PropertyType);

                Property.SetMethod.Body.Variables.Clear();

                Property.SetMethod.Body.ExceptionHandlers.Clear();

                Property.SetMethod.Body.Variables.Add(
                    new VariableDefinition(new PointerType(ModuleDefinition.TypeSystem.Byte)));

                Property.SetMethod.Body.InitLocals = true;

                var ilProcessor = Property.SetMethod.Body.GetILProcessor();

                ilProcessor.Clear();

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(GetLdcI4(BufferSize));

                ilProcessor.Append(Instruction.Create(OpCodes.Conv_U));

                ilProcessor.Append(Instruction.Create(OpCodes.Localloc));

                ilProcessor.Append(Instruction.Create(OpCodes.Stloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_1));

                if (bIsCompound)
                {
                    var zeroField = ModuleDefinition.TypeSystem.IntPtr.Resolve().Fields
                        .First(Field => Field.Name == "Zero");

                    var ib = Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(zeroField));

                    var i12 = Instruction.Create(OpCodes.Ldarg_1);

                    var i13 = Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(_getHandle));

                    var i18 = GetTypeStind(Property.PropertyType);

                    var i9 = Instruction.Create(OpCodes.Brtrue_S, i12);

                    var i10 = Instruction.Create(OpCodes.Br_S, i18);

                    ilProcessor.Append(i9);

                    ilProcessor.Append(ib);

                    ilProcessor.Append(i10);

                    ilProcessor.Append(i12);

                    ilProcessor.Append(i13);

                    ilProcessor.Append(i18);
                }
                else
                {
                    ilProcessor.Append(GetTypeStind(Property.PropertyType));
                }

                ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_getHandle)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(field)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_setStructPropertyImplementation)));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Ret));
            }

            if (Property.GetMethod != null)
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

                var BufferSize = GetTypeSize(Property.PropertyType);

                var bIsCompound = IsCompound(Property.PropertyType);

                Property.GetMethod.Body.Variables.Clear();

                Property.GetMethod.Body.ExceptionHandlers.Clear();

                Property.GetMethod.Body.Variables.Add(
                    new VariableDefinition(new PointerType(ModuleDefinition.TypeSystem.Byte)));

                if (!bIsCompound)
                {
                    Property.GetMethod.Body.Variables.Add(
                        new VariableDefinition(ModuleDefinition.ImportReference(Property.PropertyType)));
                }

                Property.GetMethod.Body.InitLocals = true;

                var ilProcessor = Property.GetMethod.Body.GetILProcessor();

                ilProcessor.Clear();

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(GetLdcI4(BufferSize));

                ilProcessor.Append(Instruction.Create(OpCodes.Conv_U));

                ilProcessor.Append(Instruction.Create(OpCodes.Localloc));

                ilProcessor.Append(Instruction.Create(OpCodes.Stloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldarg_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_getHandle)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(field)));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                ilProcessor.Append(Instruction.Create(OpCodes.Call,
                    ModuleDefinition.ImportReference(_getStructPropertyImplementation)));

                ilProcessor.Append(Instruction.Create(OpCodes.Nop));

                ilProcessor.Append(Instruction.Create(OpCodes.Ldloc_0));

                if (bIsCompound)
                {
                    ilProcessor.Append(Instruction.Create(OpCodes.Ldind_I));

                    ilProcessor.Append(Instruction.Create(OpCodes.Call,
                        ModuleDefinition.ImportReference(_getObject)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Castclass,
                        ModuleDefinition.ImportReference(Property.PropertyType)));

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
                }
                else
                {
                    ilProcessor.Append(GetTypeLdind(Property.PropertyType));

                    ilProcessor.Append(Instruction.Create(OpCodes.Stloc_1));

                    var i1 = Instruction.Create(OpCodes.Ldloc_1);

                    var i0 = Instruction.Create(OpCodes.Br_S, i1);

                    ilProcessor.Append(i0);

                    ilProcessor.Append(i1);

                    ilProcessor.Append(Instruction.Create(OpCodes.Ret));
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
                    Attribute.AttributeType.FullName == _netMulticastAttributeType.FullName))
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

        private static Instruction GetTypeLdind(TypeReference Type)
        {
            switch (Type.MetadataType)
            {
                case MetadataType.Boolean:
                    return Instruction.Create(OpCodes.Ldind_U1);
                case MetadataType.Byte:
                    return Instruction.Create(OpCodes.Ldind_I1);
                case MetadataType.Int16:
                    return Instruction.Create(OpCodes.Ldind_I2);
                case MetadataType.Int32:
                    return Instruction.Create(OpCodes.Ldind_I4);
                case MetadataType.Int64:
                    return Instruction.Create(OpCodes.Ldind_I8);
                case MetadataType.SByte:
                    return Instruction.Create(OpCodes.Ldind_U1);
                case MetadataType.UInt16:
                    return Instruction.Create(OpCodes.Ldind_U2);
                case MetadataType.UInt32:
                    return Instruction.Create(OpCodes.Ldind_U4);
                case MetadataType.UInt64:
                    return Instruction.Create(OpCodes.Ldind_I8);
                case MetadataType.Single:
                    return Instruction.Create(OpCodes.Ldind_R4);
                case MetadataType.Double:
                    return Instruction.Create(OpCodes.Ldind_R8);
                default:
                {
                    if (Type.Resolve().IsEnum)
                    {
                        return GetTypeLdind(Type.Resolve().GetEnumUnderlyingType());
                    }

                    break;
                }
            }

            return Instruction.Create(OpCodes.Ldind_Ref);
        }

        private static int GetTypeSize(TypeReference Type)
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

            return IntPtr.Size;
        }

        private static Instruction GetLdcI4(int InValue)
        {
            return InValue >= sbyte.MinValue && InValue <= sbyte.MaxValue
                ? Instruction.Create(OpCodes.Ldc_I4_S, (sbyte)InValue)
                : Instruction.Create(OpCodes.Ldc_I4, InValue);
        }

        private void ModifyRpcMethod(TypeDefinition Type, MethodDefinition Method)
        {
            var hashField = new FieldDefinition("__" + Method.Name, FieldAttributes.Private | FieldAttributes.Static,
                ModuleDefinition.TypeSystem.IntPtr);

            Type.Fields.Add(hashField);

            Method.Body.GetILProcessor().Clear();

            Method.Body.Variables.Clear();

            if (Method.Parameters.Count > 0)
            {
                int BufferSize = 0;

                foreach (var param in Method.Parameters)
                {
                    BufferSize += GetTypeSize(param.ParameterType);
                }

                Method.Body.Variables.Add(new VariableDefinition(new PointerType(ModuleDefinition.TypeSystem.Byte)));

                Method.Body.InitLocals = true;

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Nop));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Nop));

                Method.Body.GetILProcessor().Append(GetLdcI4(BufferSize));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Conv_U));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Localloc));

                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Stloc_0));

                BufferSize = 0;

                foreach (var param in Method.Parameters)
                {
                    Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldloc_0));

                    if (BufferSize != 0)
                    {
                        Method.Body.GetILProcessor().Append(GetLdcI4(BufferSize));

                        Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Add));
                    }

                    BufferSize += GetTypeSize(param.ParameterType);

                    Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldarg_S, param));

                    var bIsCompound = IsCompound(param.ParameterType);

                    if (bIsCompound)
                    {
                        var zeroField = ModuleDefinition.TypeSystem.IntPtr.Resolve().Fields
                            .First(Field => Field.Name == "Zero");

                        var i3 = Instruction.Create(OpCodes.Ldarg_S, param);

                        var i0 = Instruction.Create(OpCodes.Brtrue_S, i3);

                        var i1 = Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(zeroField));

                        var i5 = GetTypeStind(param.ParameterType);

                        var i2 = Instruction.Create(OpCodes.Br_S, i5);

                        var i4 = Instruction.Create(OpCodes.Call,
                            ModuleDefinition.ImportReference(_getHandle));

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
                ModuleDefinition.ImportReference(_getHandle)));

            Method.Body.GetILProcessor()
                .Append(Instruction.Create(OpCodes.Ldsfld, ModuleDefinition.ImportReference(hashField)));

            if (Method.Parameters.Count > 0)
            {
                Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Ldloc_0));
            }

            Method.Body.GetILProcessor().Append(Instruction.Create(OpCodes.Call,
                ModuleDefinition.ImportReference(Method.Parameters.Count > 0
                    ? _genericCall26Implementation
                    : _genericCall24Implementation)));

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

            if (Method.HasBody)
            {
                newMethod.Body.InitLocals = true;

                foreach (var variableDefinition in Method.Body.Variables)
                {
                    newMethod.Body.Variables.Add(new VariableDefinition(variableDefinition.VariableType));
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

        private static bool IsCompound(TypeReference Type) => !Type.Resolve().IsValueType;

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

        private bool GetAllMeta()
        {
            bHasMetaError = false;

            var definition = ModuleDefinition;

            if (definition.Name != "DefinitionPlaceholder")
            {
                var path = GetUEAssemblyPath(AssemblyFilePath);

                if (!File.Exists(path))
                {
                    WriteError($"[UnrealCSharp] required assembly not found: {path}");

                    return false;
                }

                definition = ModuleDefinition.ReadModule(path);
            }

            var structImplementation = GetMetaType(definition, "Script.Library.UStructImplementation");

            var propertyImplementation = GetMetaType(definition, "Script.Library.FPropertyImplementation");

            var functionImplementation = GetMetaType(definition, "Script.Library.FFunctionImplementation");

            var handleData = GetInteropType("Interop.HandleData");

            _pathNameAttributeType = GetMetaType(definition, "Script.CoreUObject.PathNameAttribute");

            _ufunctionAttributeType = GetMetaType(definition, "Script.Dynamic.UFunctionAttribute");

            _clientAttributeType = GetMetaType(definition, "Script.Dynamic.ClientAttribute");

            _serverAttributeType = GetMetaType(definition, "Script.Dynamic.ServerAttribute");

            _netMulticastAttributeType = GetMetaType(definition, "Script.Dynamic.NetMulticastAttribute");

            _notPlaceableAttributeType = GetMetaType(definition, "Script.Dynamic.NotPlaceableAttribute");

            _overrideAttributeType = GetMetaType(definition, "Script.CoreUObject.OverrideAttribute");

            _structRegisterImplementation =
                GetMetaMethod(structImplementation, "UStruct_RegisterImplementation");

            _structUnRegisterImplementation =
                GetMetaMethod(structImplementation, "UStruct_UnRegisterImplementation");

            _getObjectPropertyImplementation =
                GetMetaMethod(propertyImplementation, "FProperty_GetObjectPropertyImplementation");

            _setObjectPropertyImplementation =
                GetMetaMethod(propertyImplementation, "FProperty_SetObjectPropertyImplementation");

            _getStructPropertyImplementation =
                GetMetaMethod(propertyImplementation, "FProperty_GetStructPropertyImplementation");

            _setStructPropertyImplementation =
                GetMetaMethod(propertyImplementation, "FProperty_SetStructPropertyImplementation");

            _genericCall24Implementation =
                GetMetaMethod(functionImplementation, "FFunction_GenericCall24Implementation");

            _genericCall26Implementation =
                GetMetaMethod(functionImplementation, "FFunction_GenericCall26Implementation");

            _getObject = GetMetaMethod(handleData, "GetObject");

            _getHandle = GetMetaMethod(handleData, "GetHandle");

            return !bHasMetaError;
        }

        private TypeDefinition GetMetaType(ModuleDefinition Definition, string TypeName)
        {
            var Type = Definition.GetType(TypeName);

            if (Type == null)
            {
                bHasMetaError = true;

                WriteError($"[UnrealCSharp] required type not found: {TypeName}");
            }

            return Type;
        }

        private MethodDefinition GetMetaMethod(TypeDefinition Type, string MethodName)
        {
            var Method = Type?.Methods.FirstOrDefault(Candidate => Candidate.Name == MethodName);

            if (Method == null && Type != null)
            {
                bHasMetaError = true;

                WriteError($"[UnrealCSharp] required method not found: {MethodName}");
            }

            return Method;
        }

        private TypeDefinition GetInteropType(string TypeName)
        {
            var Reference = ModuleDefinition.AssemblyReferences
                .FirstOrDefault(Candidate => Candidate.Name == "Interop");

            var Module = Reference != null
                ? ModuleDefinition.AssemblyResolver.Resolve(Reference).MainModule
                : null;

            var Type = Module?.GetType(TypeName);

            if (Type == null)
            {
                bHasMetaError = true;

                WriteError($"[UnrealCSharp] required Interop type not found: {TypeName}");
            }

            return Type;
        }
        private string GetUEAssemblyPath(string assemblyFilePath)
        {
            var scriptPathName = "ScriptPathPlaceholder";

            var ueAssemblyName = "AssemblyPlaceholder";

            var scriptIndex = assemblyFilePath.LastIndexOf(scriptPathName, StringComparison.Ordinal);

            var scriptPathNameLength = scriptPathName.Length;

            var relativePath = assemblyFilePath.Substring(scriptIndex + scriptPathNameLength + 1,
                assemblyFilePath.Length - scriptIndex - scriptPathNameLength - 1);

            var basePath = assemblyFilePath.Substring(0, scriptIndex + scriptPathNameLength);

            var segments = relativePath.Split(new[] { '\\', '/' });

            segments[0] = ueAssemblyName;

            segments[segments.Length - 1] = ueAssemblyName + ".dll";

            return Path.Combine(basePath, Path.Combine(segments));
        }
    }
}