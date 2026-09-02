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
        private const string GameAssemblyName = "GameNamePlaceholder";

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

            if (Context.Compilation.AssemblyName != GameAssemblyName)
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

                @interface.Usings.Add("using Script.Library;\n");

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
                    HasHashCodeMethod = false,
                    HasOperatorEqualTo = false,
                    HasOperatorNotEqualTo = false,
                    HasStaticClass = false,
                    HasStaticStruct = false,
                });

                Context.AddSource("Script.CoreUObject." + @interface.Name + ".gen.cs", source);
            }

            foreach (var type in unrealTypeReceiver.TypeInfos)
            {
                if (type.Value.DynamicType == EDynamicType.Other)
                {
                    continue;
                }

                if (type.Value.DynamicType == EDynamicType.UStruct &&
                    type.Value.HasStaticStruct &&
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
                    var source = "";

                    type.Value.Usings.ForEach(Str => source += Str);

                    source +=
                        $"\nnamespace {type.Value.NameSpace}\n" +
                        $"{{\n\t{type.Value.Modifiers} class {type.Value.Name} : IStaticStruct\n" +
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

                    if (type.Value.HasEqualsMethod == false)
                    {
                        source +=
                            $"\t\tpublic override bool Equals(object Other) => this == Other as {type.Value.Name};\n";
                    }

                    if (type.Value.HasHashCodeMethod == false)
                    {
                        source += "\t\tpublic override int GetHashCode() => (int)HandleData.GetHandle(this);\n";
                    }

                    if (type.Value.HasOperatorEqualTo == false)
                    {
                        source +=
                            $"\t\tpublic static bool operator ==({type.Value.Name} A, {type.Value.Name} B)\n" +
                            "\t\t{\n" +
                            "\t\t\tif (A is null && B is null)\n" +
                            "\t\t\t{\n" +
                            "\t\t\t\treturn true;\n" +
                            "\t\t\t}\n" +
                            "\t\t\tif (A is null || B is null)\n" +
                            "\t\t\t{\n" +
                            "\t\t\t\treturn false;\n" +
                            "\t\t\t}\n" +
                            "\t\t\treturn ReferenceEquals(A, B) || UStructImplementation.UStruct_IdenticalImplementation(HandleData.GetHandle(StaticStruct()), HandleData.GetHandle(A), HandleData.GetHandle(B));\n" +
                            "\t\t}\n";
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
                              $"{{\n\t{type.Value.Modifiers} class {type.Value.Name} : IStaticClass\n" +
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
        private readonly string[] InterfaceAttributes =
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

                            if (InterfaceAttributes.Any(
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

            if (Syntax.Modifiers.Any(Modifier => Modifier.Text == "partial") == false)
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

            var modifiers = string.Join(" ", Syntax.Modifiers.Select(Modifier => Modifier.Text));

            var methods = Syntax.Members.OfType<MethodDeclarationSyntax>().ToArray();

            var bHasStaticClass = methods.Any(Method => Method.Identifier.ToString() == "StaticClass");

            var bHasStaticStruct = methods.Any(Method => Method.Identifier.ToString() == "StaticStruct");

            var bHasEqualsMethod = methods.Any(Method =>
                Method.Identifier.ToString() == "Equals" && Method.ParameterList.Parameters.Count == 1);

            var bHasHashCodeMethod = methods.Any(Method =>
                Method.Identifier.ToString() == "GetHashCode" && Method.ParameterList.Parameters.Count <= 0);

            var operators = Syntax.Members.OfType<OperatorDeclarationSyntax>().ToArray();

            var bHasOperatorEqualTo = operators.Any(Operator =>
            {
                if (Operator.OperatorToken.Text != "==")
                {
                    return false;
                }

                foreach (var parameter in Operator.ParameterList.Parameters)
                {
                    if (parameter.Type is IdentifierNameSyntax parameterType == false ||
                        parameterType.Identifier.Text != name)
                    {
                        return false;
                    }
                }

                return true;
            });

            var bHasOperatorNotEqualTo = operators.Any(Operator =>
            {
                if (Operator.OperatorToken.Text != "!=")
                {
                    return false;
                }

                foreach (var parameter in Operator.ParameterList.Parameters)
                {
                    if (parameter.Type is IdentifierNameSyntax parameterType == false ||
                        parameterType.Identifier.Text != name)
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
                    "using Script.CoreUObject;\n",
                    "using Interop;\n"
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
                    var currentFileName = bIsUClass && name.EndsWith("_C")
                        ? name + ".cs"
                        : name.Substring(1) + ".cs";

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
                    var attributeName = attribute.Name.ToString();

                    if (attributeName == Name || attributeName == Name + "Attribute")
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
                    result.Add(@using.ToFullString().Trim() + "\n");
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

    [Generator]
    public class LibraryBridgeGenerator : ISourceGenerator
    {
        private readonly string[] BridgeNamespaces = { "Script.Binding", "Script.Library" };

        private const string NativeModuleName = "UnrealCSharp";

        public void Initialize(GeneratorInitializationContext Context)
        {
            Context.RegisterForSyntaxNotifications(() => new LibraryBridgeReceiver());
        }

        public void Execute(GeneratorExecutionContext Context)
        {
            if (!(Context.SyntaxReceiver is LibraryBridgeReceiver receiver) || receiver.Candidates.Count == 0)
            {
                return;
            }

            var byType = new Dictionary<INamedTypeSymbol, List<IMethodSymbol>>(SymbolEqualityComparer.Default);

            var semanticModels = new Dictionary<SyntaxTree, SemanticModel>();

            foreach (var candidate in receiver.Candidates)
            {
                if (semanticModels.TryGetValue(candidate.SyntaxTree, out var semanticModel) == false)
                {
                    semanticModel = Context.Compilation.GetSemanticModel(candidate.SyntaxTree);

                    semanticModels[candidate.SyntaxTree] = semanticModel;
                }

                if (semanticModel.GetDeclaredSymbol(candidate) is IMethodSymbol method == false)
                {
                    continue;
                }

                var owner = method.ContainingType;

                if (owner == null ||
                    BridgeNamespaces.Contains(owner.ContainingNamespace?.ToDisplayString()) == false)
                {
                    continue;
                }

                if (byType.TryGetValue(owner, out var methods) == false)
                {
                    methods = new List<IMethodSymbol>();

                    byType[owner] = methods;
                }

                methods.Add(method);
            }

            foreach (var pair in byType)
            {
                Context.AddSource($"{pair.Key.ContainingNamespace?.ToDisplayString()}.{pair.Key.Name}.LibraryBridge.g.cs",
                    EmitBridges(pair.Key, pair.Value));
            }
        }

        private string EmitBridges(INamedTypeSymbol InOwner, List<IMethodSymbol> InMethods)
        {
            var source = "// <auto-generated/> LibraryBridgeGenerator -- do not edit.\n" +
                         "#if WITH_LEANCLR\n" +
                         "using System.Runtime.InteropServices;\n" +
                         "#endif\n";

            var containingNamespace = InOwner.ContainingNamespace?.ToDisplayString() ?? BridgeNamespaces[1];

            var qualifiedTypes = new Dictionary<ITypeSymbol, string>(SymbolEqualityComparer.Default);

            source +=
                $"\nnamespace {containingNamespace}\n" +
                $"{{\n\t{(InOwner.DeclaredAccessibility == Accessibility.Public ? "public" : "internal")} static unsafe partial class {InOwner.Name}\n" +
                "\t{\n";

            foreach (var method in InMethods
                         .OrderBy(Method => Method.Name, StringComparer.Ordinal)
                         .ThenBy(Method => Method.ToDisplayString(), StringComparer.Ordinal))
            {
                var returnType = method.ReturnsVoid ? "void" : Qualify(method.ReturnType, qualifiedTypes);

                var parameters = string.Join(", ", method.Parameters.Select(
                    Parameter => $"{Qualify(Parameter.Type, qualifiedTypes)} {Parameter.Name}"));

                var arguments = string.Join(", ", method.Parameters.Select(Parameter => Parameter.Name));

                var pointerType = string.Join(", ", method.Parameters
                    .Select(Parameter => Qualify(Parameter.Type, qualifiedTypes)).Concat(new[] { returnType }));

                var key = $"{containingNamespace}.{InOwner.Name}::{method.Name}";

                var slot = $"{method.Name}_Slot";

                var accessibility = method.DeclaredAccessibility == Accessibility.Public ? "public" : "private";

                source +=
                    "#if WITH_LEANCLR\n" +
                    $"\t\t[DllImport(\"{NativeModuleName}\", CallingConvention = CallingConvention.Cdecl)]\n" +
                    $"\t\t{accessibility} static extern unsafe partial {returnType} {method.Name}({parameters});\n" +
                    "#else\n" +
                    $"\t\tprivate static nint {slot};\n" +
                    "\n" +
                    $"\t\t{accessibility} static unsafe partial {returnType} {method.Name}({parameters}) =>\n" +
                    $"\t\t\t((delegate* unmanaged[Cdecl]<{pointerType}>)global::Interop.MethodBridge.GetMethod(\n" +
                    $"\t\t\t\tref {slot}, \"{key}\"))({arguments});\n" +
                    "#endif\n\n";
            }

            source += "\t}\n";

            source += "}";

            return source;
        }

        private static string Qualify(ITypeSymbol InType, Dictionary<ITypeSymbol, string> InCache)
        {
            if (InCache.TryGetValue(InType, out var display) == false)
            {
                display = InType.ToDisplayString(SymbolDisplayFormat.FullyQualifiedFormat);

                InCache[InType] = display;
            }

            return display;
        }
    }

    public class LibraryBridgeReceiver : ISyntaxReceiver
    {
        public readonly List<MethodDeclarationSyntax> Candidates = new List<MethodDeclarationSyntax>();

        public void OnVisitSyntaxNode(SyntaxNode Node)
        {
            if (Node is MethodDeclarationSyntax methodDeclarationSyntax == false)
            {
                return;
            }

            if (methodDeclarationSyntax.Body != null || methodDeclarationSyntax.ExpressionBody != null)
            {
                return;
            }

            if (methodDeclarationSyntax.Modifiers.Any(Modifier => Modifier.ValueText == "partial") == false ||
                methodDeclarationSyntax.Modifiers.Any(Modifier => Modifier.ValueText == "static") == false)
            {
                return;
            }

            Candidates.Add(methodDeclarationSyntax);
        }
    }
}
