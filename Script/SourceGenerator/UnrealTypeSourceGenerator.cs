using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace SourceGenerator
{
    [Generator]
    public class UnrealTypeSourceGenerator : ISourceGenerator
    {
        public static readonly DiagnosticDescriptor ErrorDynamicClassNotAPartialClass = new DiagnosticDescriptor(
            "UC_ERROR_01",
            "UClass or UStruct must be a partial class", "{0} \"{1}\" must be a partial class",
            "UnrealCSharp",
            DiagnosticSeverity.Error,
            isEnabledByDefault: true);

        public static readonly DiagnosticDescriptor ErrorFileNameNotMatch = new DiagnosticDescriptor(
            "UC_ERROR_02",
            "The file name and class name do not match", "The file where {0} \"{1}\" is located must be \"{2}\"",
            "UnrealCSharp",
            DiagnosticSeverity.Error,
            isEnabledByDefault: true);

        public static readonly DiagnosticDescriptor ErrorTypeNameNotMatch = new DiagnosticDescriptor(
            "UC_ERROR_03",
            "The name of dynamic class is error", "{0}",
            "UnrealCSharp",
            DiagnosticSeverity.Error,
            isEnabledByDefault: true);

        public static readonly DiagnosticDescriptor ErrorUClassHasNoBaseClass = new DiagnosticDescriptor(
            "UC_ERROR_04",
            "UClass must have a base class", "{0}",
            "UnrealCSharp",
            DiagnosticSeverity.Error,
            isEnabledByDefault: true);

        public static readonly DiagnosticDescriptor ErrorTypeMustBeUnique = new DiagnosticDescriptor(
            "UC_ERROR_05",
            "Type must be unique", "{0}",
            "UnrealCSharp",
            DiagnosticSeverity.Error,
            isEnabledByDefault: true);

        private static string GetPathName(string Name)
        {
            return "/Script/CoreUObject." + (Name.EndsWith("_C") ? Name : Name.Substring(1));
        }

        public void Execute(GeneratorExecutionContext Context)
        {
            if (!(Context.SyntaxReceiver is UnrealTypeReceiver unrealTypeReceiver))
            {
                return;
            }

            foreach (var error in unrealTypeReceiver.Errors)
            {
                Context.ReportDiagnostic(error);
            }

            foreach (var @interface in unrealTypeReceiver.Interfaces)
            {
                var source = "";

                @interface.Usings.Add("using Script.Library;");

                @interface.Usings.ForEach(Str => source += Str);

                source += "\nnamespace Script.CoreUObject";

                source += "\n{";

                source += $"\n\t[{string.Join(", ", @interface.Attributes)}]";

                source += $"\n\tpublic partial class U{@interface.Name.Substring(1)} : UInterface ";

                source += "\n\t{";

                source += "\n\t}";

                source += "\n}";

                unrealTypeReceiver.TypeInfos.Add(@interface.Name, new TypeInfo
                {
                    Name = $"U{@interface.Name.Substring(1)}",
                    DynamicType = EDynamicType.UInterface,
                    NameSpace = "Script.CoreUObject",
                    Modifiers = "public partial",
                    Usings = @interface.Usings,
                    HasBase = true,
                    HasEqualsMethod = false,
                    HasGarbageCollectionHandle = false,
                    HasHashCodeMethod = false,
                    HasOperatorEqualTo = false,
                    HasOperatorNotEqualTo = false,
                    HasStaticClass = false,
                    HasStaticStruct = false,
                });

                Context.AddSource(@interface.Name + ".gen.cs", source);
            }

            foreach (var type in unrealTypeReceiver.TypeInfos)
            {
                if (type.Value.DynamicType == EDynamicType.Other)
                {
                    continue;
                }

                if (type.Value.DynamicType == EDynamicType.UStruct &&
                    type.Value.HasStaticStruct &&
                    type.Value.HasGarbageCollectionHandle &&
                    type.Value.HasEqualsMethod &&
                    type.Value.HasHashCodeMethod &&
                    type.Value.HasOperatorEqualTo &&
                    type.Value.HasOperatorNotEqualTo)
                {
                    continue;
                }

                if (type.Value.DynamicType == EDynamicType.UClass && type.Value.HasStaticClass)
                {
                    continue;
                }

                if (type.Value.DynamicType == EDynamicType.UInterface && type.Value.HasStaticClass)
                {
                    continue;
                }

                if (type.Value.DynamicType == EDynamicType.UStruct)
                {
                    var interfaceBody = type.Value.HasBase || type.Value.HasGarbageCollectionHandle
                        ? ": IStaticStruct"
                        : ": IStaticStruct, IGarbageCollectionHandle";

                    var source = "";

                    type.Value.Usings.ForEach(Str => source += Str);

                    source +=
                        $"\nnamespace {type.Value.NameSpace}\n" +
                        $"{{\n\t{type.Value.Modifiers} class {type.Value.Name}{interfaceBody}\n" +
                        "\t{\n";

                    if (type.Value.HasStaticStruct == false)
                    {
                        var newBody = type.Value.HasBase ? " new" : "";

                        var fullPath = GetPathName(type.Value.Name);

                        source +=
                            $"\t\tpublic{newBody} static UScriptStruct StaticStruct()\n" +
                            "\t\t{\n" +
                            $"\t\t\treturn StaticStructSingleton ??= UStructImplementation.UStruct_StaticStructImplementation(\"{fullPath}\");\n" +
                            "\t\t}\n" +
                            "\t\tprivate static UScriptStruct StaticStructSingleton { get; set; }\n";
                    }

                    if (type.Value.HasGarbageCollectionHandle == false && type.Value.HasBase == false)
                    {
                        source += "\t\tpublic nint GarbageCollectionHandle { get; set; }\n";
                    }

                    if (type.Value.HasEqualsMethod == false)
                    {
                        source +=
                            $"\t\tpublic override bool Equals(object Other) => this == Other as {type.Value.Name};\n";
                    }

                    if (type.Value.HasHashCodeMethod == false)
                    {
                        source += "\t\tpublic override int GetHashCode() => (int)GarbageCollectionHandle;\n";
                    }

                    if (type.Value.HasOperatorEqualTo == false)
                    {
                        source +=
                            $"\t\tpublic static bool operator ==({type.Value.Name} A, {type.Value.Name} B) => Utils.EqualsTo(A, B, UStructImplementation.UStruct_IdenticalImplementation);\n";
                    }

                    if (type.Value.HasOperatorNotEqualTo == false)
                    {
                        source +=
                            $"\t\tpublic static bool operator !=({type.Value.Name} A, {type.Value.Name} B) => !(A == B);\n";
                    }

                    source += "\t}\n";

                    source += "}";

                    Context.AddSource(type.Value.NameSpace + "." + type.Value.Name + ".gen.cs", source);
                }
                else if (type.Value.DynamicType == EDynamicType.UClass ||
                         type.Value.DynamicType == EDynamicType.UInterface)
                {
                    var source = "";

                    type.Value.Usings.ForEach(Str => source += Str);

                    source += $"\nnamespace {type.Value.NameSpace}\n" +
                              $"{{\n\t{type.Value.Modifiers} class {type.Value.Name}: IStaticClass\n" +
                              "\t{\n";

                    if (type.Value.HasStaticClass == false)
                    {
                        var fullPath = GetPathName(type.Value.Name);

                        source +=
                            "\t\tpublic new static UClass StaticClass()\n" +
                            "\t\t{\n" +
                            $"\t\t\treturn StaticClassSingleton ??= UObjectImplementation.UObject_StaticClassImplementation(\"{fullPath}\");\n" +
                            "\t\t}\n" +
                            "\t\tprivate static UClass StaticClassSingleton { get; set; }\n";
                    }

                    source += "\t}\n";

                    source += "}";

                    Context.AddSource(type.Value.NameSpace + "." + type.Value.Name + ".gen.cs", source);
                }
            }
        }

        public void Initialize(GeneratorInitializationContext Context)
        {
            Context.RegisterForSyntaxNotifications(() => new UnrealTypeReceiver());
        }
    }

    public class UnrealTypeReceiver : ISyntaxReceiver
    {
        private readonly string[] _interfaceAttributes =
        {
            "UInterface",
            "MinimalAPI",
            "BlueprintType",
            "Blueprintable",
            "ConversionRoot",
            "CannotImplementInterfaceInBlueprint"
        };

        public readonly Dictionary<string, TypeInfo> TypeInfos = new Dictionary<string, TypeInfo>();

        public readonly List<Diagnostic> Errors = new List<Diagnostic>();

        public readonly List<InterfaceInfo> Interfaces = new List<InterfaceInfo>();

        public HashSet<string> Types = new HashSet<string>();

        public void OnVisitSyntaxNode(SyntaxNode Node)
        {
            if (Node is ClassDeclarationSyntax classDeclarationSyntax)
            {
                ProcessClass(classDeclarationSyntax);
            }
            else if (Node is EnumDeclarationSyntax enumDeclarationSyntax)
            {
                var name = enumDeclarationSyntax.Identifier.ToString();

                var filePath = enumDeclarationSyntax.GetLocation().SourceTree?.FilePath;

                if (enumDeclarationSyntax.Parent is BaseNamespaceDeclarationSyntax == false)
                {
                    return;
                }

                if (GetAttributeFromClass(enumDeclarationSyntax, "UEnum") == null)
                {
                    return;
                }

                if (!IsUnique(enumDeclarationSyntax, name))
                {
                    return;
                }

                if (name.StartsWith("E") == false)
                {
                    Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeNameNotMatch,
                        Location.Create(
                            enumDeclarationSyntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                            enumDeclarationSyntax.Identifier.Span),
                        $"The name of UEnum {name} must start with \"E\""));
                }
                else
                {
                    var currentFileName = name + ".cs";

                    if (Path.GetFileName(filePath) != currentFileName)
                    {
                        Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorFileNameNotMatch,
                            Location.Create(
                                enumDeclarationSyntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                                enumDeclarationSyntax.Identifier.Span),
                            "enum", name, currentFileName));
                    }
                }
            }
            else if (Node is InterfaceDeclarationSyntax interfaceDeclarationSyntax)
            {
                var name = interfaceDeclarationSyntax.Identifier.ToString();

                var filePath = interfaceDeclarationSyntax.GetLocation().SourceTree?.FilePath;

                if (interfaceDeclarationSyntax.Parent is BaseNamespaceDeclarationSyntax == false)
                {
                    return;
                }

                if (GetAttributeFromClass(interfaceDeclarationSyntax, "UInterface") == null)
                {
                    return;
                }

                if (!IsUnique(interfaceDeclarationSyntax, name))
                {
                    return;
                }

                var hasError = false;

                if (name.StartsWith("I") == false)
                {
                    hasError = true;

                    Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeNameNotMatch,
                        Location.Create(
                            interfaceDeclarationSyntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                            interfaceDeclarationSyntax.Identifier.Span),
                        $"The name of UInterface {name} must start with \"I\""));
                }
                else
                {
                    var currentFileName = name + ".cs";

                    currentFileName = currentFileName.Substring(1, currentFileName.Length - 1);

                    if (Path.GetFileName(filePath) != currentFileName)
                    {
                        hasError = true;

                        Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorFileNameNotMatch,
                            Location.Create(
                                interfaceDeclarationSyntax.Identifier.SyntaxTree ??
                                throw new InvalidOperationException(),
                                interfaceDeclarationSyntax.Identifier.Span),
                            "interface", name, currentFileName));
                    }
                }

                if (hasError == false)
                {
                    var attributes = new List<string>();

                    foreach (var list in interfaceDeclarationSyntax.AttributeLists)
                    {
                        foreach (var attribute in list.Attributes)
                        {
                            var text = attribute.ToFullString().Trim();

                            if (_interfaceAttributes.Any(
                                    AttributeText => text.IndexOf(AttributeText, StringComparison.Ordinal) >= 0))
                            {
                                attributes.Add(text);
                            }
                        }
                    }

                    Interfaces.Add(new InterfaceInfo
                    {
                        Name = name,

                        Attributes = attributes,

                        Usings = interfaceDeclarationSyntax.GetUsingList()
                    });
                }
            }
        }

        private void ProcessClass(ClassDeclarationSyntax Syntax)
        {
            var name = Syntax.Identifier.ToString().Trim();

            var attributeUClass = GetAttributeFromClass(Syntax, "UClass");

            var attributeUStruct = GetAttributeFromClass(Syntax, "UStruct");

            var bIsUClass = attributeUClass != null;

            var bIsUStruct = attributeUStruct != null;

            var bHasBase = Syntax.BaseList != null;

            var filePath = Syntax.GetLocation().SourceTree?.FilePath;

            var hasError = false;

            if (bIsUClass || bIsUStruct)
            {
                if (!IsUnique(Syntax, name))
                {
                    return;
                }
            }

            if (bHasBase)
            {
                var baseType = Syntax.BaseList.Types.FirstOrDefault();

                if (baseType != null)
                {
                    var baseTypeName = baseType.Type.GetText().ToString().Trim();

                    if (bIsUClass)
                    {
                        if (baseTypeName.EndsWith("_C"))
                        {
                            if (name.EndsWith("_C") == false)
                            {
                                hasError = true;

                                Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeNameNotMatch,
                                    Location.Create(
                                        Syntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                                        Syntax.Identifier.Span),
                                    $"The name of UClass {name} must end with \"_C\""));
                            }
                        }
                        else if (baseTypeName.StartsWith("A"))
                        {
                            if (name.EndsWith("_C") == false && name.StartsWith("A") == false)
                            {
                                hasError = true;

                                Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeNameNotMatch,
                                    Location.Create(
                                        Syntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                                        Syntax.Identifier.Span),
                                    $"The name of UClass {name} must end with \"_C\" or start with \"A\""));
                            }
                        }
                        else if (baseTypeName.StartsWith("U"))
                        {
                            if (name.EndsWith("_C") == false && name.StartsWith("U") == false)
                            {
                                hasError = true;

                                Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeNameNotMatch,
                                    Location.Create(
                                        Syntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                                        Syntax.Identifier.Span),
                                    $"The name of UClass {name} must end with \"_C\" or start with \"U\""));
                            }
                        }
                    }
                }
            }
            else
            {
                if (bIsUClass)
                {
                    hasError = true;

                    Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorUClassHasNoBaseClass,
                        Location.Create(
                            Syntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                            Syntax.Identifier.Span),
                        $"{name} must have a base class"));
                }
            }

            if (bIsUStruct)
            {
                if (name.StartsWith("F") == false)
                {
                    hasError = true;

                    Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeNameNotMatch,
                        Location.Create(Syntax.Identifier.SyntaxTree ?? throw new InvalidOperationException(),
                            Syntax.Identifier.Span),
                        $"The name of UStruct {name} must start with \"F\""));
                }
            }

            if (Syntax.Modifiers.ToArray().Any(Modifier => Modifier.Text == "partial") == false)
            {
                if (bIsUClass || bIsUStruct)
                {
                    AttributeSyntax errorAttribute;

                    EDynamicType dynamicType;

                    if (bIsUClass)
                    {
                        errorAttribute = attributeUClass;

                        dynamicType = EDynamicType.UClass;
                    }
                    else
                    {
                        errorAttribute = attributeUStruct;

                        dynamicType = EDynamicType.UStruct;
                    }

                    Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorDynamicClassNotAPartialClass,
                        Location.Create(errorAttribute.SyntaxTree, errorAttribute.Span),
                        dynamicType.ToString().Replace("EType.", ""), name));
                }

                return;
            }

            if (Syntax.Parent is BaseNamespaceDeclarationSyntax namespaceDeclarationSyntax == false)
            {
                return;
            }

            var nameSpace = namespaceDeclarationSyntax.GetFullNamespace();

            var usingList = Syntax.GetUsingList();

            var modifiers = string.Join(" ", Syntax.Modifiers.ToArray().Select(Modifier => Modifier.Text));

            var methods = Syntax.Members.Where(Member => Member is MethodDeclarationSyntax);

            var methodArray = methods as MemberDeclarationSyntax[] ?? methods.ToArray();

            var bHasStaticClass = methodArray.Any(Method =>
                ((MethodDeclarationSyntax)Method).Identifier.ToString() == "StaticClass");

            var bHasStaticStruct = methodArray.Any(Method =>
                ((MethodDeclarationSyntax)Method).Identifier.ToString() == "StaticStruct");

            var bHasGarbageCollectionHandle = Syntax.Members.Any(Member =>
                Member is PropertyDeclarationSyntax declarationSyntax &&
                declarationSyntax.Identifier.ToString() == "GarbageCollectionHandle");

            var bHasEqualsMethod = methodArray.Any(Method =>
            {
                var method = (MethodDeclarationSyntax)Method;

                if (method.Identifier.ToString() != "Equals")
                {
                    return false;
                }

                return method.ParameterList.Parameters.Count == 1;
            });

            var bHasHashCodeMethod = methodArray.Any(Method =>
            {
                var method = (MethodDeclarationSyntax)Method;

                if (method.Identifier.ToString() != "GetHashCode")
                {
                    return false;
                }

                return method.ParameterList.Parameters.Count <= 0;
            });

            var operators = Syntax.Members.Where(Member => Member is OperatorDeclarationSyntax);

            var operatorArray = operators as MemberDeclarationSyntax[] ?? operators.ToArray();

            var bHasOperatorEqualTo = operatorArray.Any(Operator =>
            {
                var op = (OperatorDeclarationSyntax)Operator;

                if (op.OperatorToken.Text != "==")
                {
                    return false;
                }

                foreach (var parameter in op.ParameterList.Parameters)
                {
                    var parameterType = (IdentifierNameSyntax)parameter.Type;

                    if (parameterType != null && parameterType.Identifier.Text != name)
                    {
                        return false;
                    }
                }

                return true;
            });

            var bHasOperatorNotEqualTo = operatorArray.Any(Operator =>
            {
                var op = (OperatorDeclarationSyntax)Operator;

                if (op.OperatorToken.Text != "!=")
                {
                    return false;
                }

                foreach (var parameter in op.ParameterList.Parameters)
                {
                    var parameterType = (IdentifierNameSyntax)parameter.Type;

                    if (parameterType != null && parameterType.Identifier.Text != name)
                    {
                        return false;
                    }
                }

                return true;
            });

            if (TypeInfos.TryGetValue(nameSpace + "." + name, out var type) == false)
            {
                type = new TypeInfo();

                TypeInfos.Add(nameSpace + "." + name, type);

                type.NameSpace = nameSpace;

                type.Name = name;

                type.Modifiers = modifiers;

                type.DynamicType = EDynamicType.Other;

                type.Usings = new List<string>
                {
                    "using Script.Library;\n",
                    "using Script.UnrealCSharpCore;\n",
                    "using Script.CoreUObject;\n"
                };
            }

            if (type.DynamicType == EDynamicType.Other)
            {
                if (bIsUClass)
                {
                    type.DynamicType = EDynamicType.UClass;
                }
                else if (bIsUStruct)
                {
                    type.DynamicType = EDynamicType.UStruct;
                }
            }

            if (hasError == false)
            {
                if (bIsUClass || bIsUStruct)
                {
                    var currentFileName = name + ".cs";

                    if (bIsUClass && name.EndsWith("_C") == false)
                    {
                        currentFileName = currentFileName.Substring(1, currentFileName.Length - 1);
                    }

                    if (bIsUStruct)
                    {
                        currentFileName = currentFileName.Substring(1, currentFileName.Length - 1);
                    }

                    if (Path.GetFileName(filePath) != currentFileName)
                    {
                        Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorFileNameNotMatch,
                            Location.Create(Syntax.Identifier.SyntaxTree, Syntax.Identifier.Span), "class", name,
                            currentFileName));
                    }
                }
            }

            type.Usings = MergeUsing(usingList, type.Usings);

            type.HasBase = bHasBase;

            type.HasStaticStruct |= bHasStaticStruct;

            type.HasStaticClass |= bHasStaticClass;

            type.HasGarbageCollectionHandle |= bHasGarbageCollectionHandle;

            type.HasHashCodeMethod |= bHasHashCodeMethod;

            type.HasEqualsMethod |= bHasEqualsMethod;

            type.HasOperatorEqualTo |= bHasOperatorEqualTo;

            type.HasOperatorNotEqualTo |= bHasOperatorNotEqualTo;
        }

        private bool IsUnique(BaseTypeDeclarationSyntax Syntax, string Name)
        {
            if (Types.Add(Name))
            {
                return true;
            }

            Errors.Add(Diagnostic.Create(UnrealTypeSourceGenerator.ErrorTypeMustBeUnique,
                Location.Create(
                    Syntax.SyntaxTree,
                    Syntax.Span),
                $"{Name} must be unique"));

            return false;
        }

        private static AttributeSyntax GetAttributeFromClass(BaseTypeDeclarationSyntax Syntax, string Name)
        {
            foreach (var attributeList in Syntax.AttributeLists)
            {
                foreach (var attribute in attributeList.Attributes)
                {
                    if (attribute.GetText().ToString().IndexOf(Name, StringComparison.Ordinal) >= 0)
                    {
                        return attribute;
                    }
                }
            }

            return null;
        }

        private static List<string> MergeUsing(List<string> UsingListA, List<string> UsingListB)
        {
            if (UsingListA == null && UsingListB != null)
            {
                return UsingListB;
            }

            if (UsingListB == null && UsingListA != null)
            {
                return UsingListA;
            }

            var result = new List<string>();

            if (UsingListA == null)
            {
                return result;
            }

            foreach (var elem in UsingListA)
            {
                if (result.Contains(elem))
                {
                    continue;
                }

                result.Add(elem);
            }

            foreach (var elem in UsingListB)
            {
                if (result.Contains(elem))
                {
                    continue;
                }

                result.Add(elem);
            }

            return result;
        }
    }

    public enum EDynamicType
    {
        UClass,
        UStruct,
        UInterface,
        Other
    }

    public class InterfaceInfo
    {
        public string Name { get; set; }

        public List<string> Attributes { get; set; }

        public List<string> Usings { get; set; }
    }

    public class TypeInfo
    {
        public EDynamicType DynamicType { get; set; }

        public List<string> Usings { get; set; }

        public string Name { get; set; }

        public string NameSpace { get; set; }

        public string Modifiers { get; set; }

        public bool HasBase { get; set; }

        public bool HasGarbageCollectionHandle { get; set; }

        public bool HasStaticClass { get; set; }

        public bool HasStaticStruct { get; set; }

        public bool HasOperatorEqualTo { get; set; }

        public bool HasOperatorNotEqualTo { get; set; }

        public bool HasEqualsMethod { get; set; }

        public bool HasHashCodeMethod { get; set; }
    }

    public static class CodeAnalysisHelper
    {
        public static List<string> GetUsingList(this SyntaxNode Node)
        {
            var result = new List<string>();

            if (Node is CompilationUnitSyntax compilationUnitSyntax)
            {
                foreach (var @using in compilationUnitSyntax.Usings)
                {
                    var str = @using.GetText().ToString().Replace(" ", "").Replace("\t", "").Replace("\n", "")
                        .Replace("\r", "").Trim() + "\n";

                    str = str.Replace("using", "using ");

                    result.Add(str);
                }

                return result;
            }

            return Node.Parent == null ? result : Node.Parent.GetUsingList();
        }

        public static string GetFullNamespace(this BaseNamespaceDeclarationSyntax Syntax)
        {
            if (Syntax.Parent is BaseNamespaceDeclarationSyntax baseNamespaceDeclarationSyntax == false)
            {
                return Syntax.Name.ToString();
            }

            return baseNamespaceDeclarationSyntax.GetFullNamespace() + "." + Syntax.Name;
        }
    }
}