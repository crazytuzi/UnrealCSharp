using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace SourceGenerator
{
    [Generator]
    public class UnrealTypeSourceGenerator : ISourceGenerator
    {
        private static readonly DiagnosticDescriptor ErrorDynamicClass = new DiagnosticDescriptor(
            "UC_ERROR_01",
            "Dynamic Class Must be partial", "{0} \"{1}\" must be a partial class",
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
                Context.ReportDiagnostic(Diagnostic.Create(ErrorDynamicClass, error.ErrorLocation,
                    error.UnrealDynamicType.ToString().Replace("EType.", ""), error.Name));
            }

            foreach (var type in unrealTypeReceiver.Types)
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

                    type.Value.Using.ForEach(Str => source += Str);

                    source +=
                        $"namespace {type.Value.NameSpace}\n" +
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

                    type.Value.Using.ForEach(Str => source += Str);

                    source += $"namespace {type.Value.NameSpace}\n" +
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
        public readonly Dictionary<string, TypeInfo> Types = new Dictionary<string, TypeInfo>();

        public readonly List<ErrorInfo> Errors = new List<ErrorInfo>();

        public void OnVisitSyntaxNode(SyntaxNode Node)
        {
            if (Node is ClassDeclarationSyntax classDeclarationSyntax)
            {
                ProcessClass(classDeclarationSyntax);
            }
        }

        private void ProcessClass(ClassDeclarationSyntax Syntax)
        {
            var name = Syntax.Identifier.ToString();

            var attributeUClass = GetAttributeFromClass(Syntax, "UClass");

            var attributeUStruct = GetAttributeFromClass(Syntax, "UStruct");

            var attributeUInterface = GetAttributeFromClass(Syntax, "UInterface");

            var bIsUClass = attributeUClass != null;

            var bIsUStruct = attributeUStruct != null;

            var bIsUInterface = attributeUInterface != null;

            var bHasBase = Syntax.BaseList != null;

            if (Syntax.Modifiers.ToArray().Any(Modifier => Modifier.Text == "partial") == false)
            {
                if (bIsUClass || bIsUStruct || bIsUInterface)
                {
                    AttributeSyntax errorAttribute;

                    EDynamicType dynamicType;

                    if (bIsUClass)
                    {
                        errorAttribute = attributeUClass;

                        dynamicType = EDynamicType.UClass;
                    }
                    else if (bIsUStruct)
                    {
                        errorAttribute = attributeUStruct;

                        dynamicType = EDynamicType.UStruct;
                    }
                    else
                    {
                        errorAttribute = attributeUInterface;

                        dynamicType = EDynamicType.UInterface;
                    }

                    Errors.Add(new ErrorInfo
                    {
                        Name = name,
                        UnrealDynamicType = dynamicType,
                        ErrorLocation = Location.Create(errorAttribute.SyntaxTree, errorAttribute.Span)
                    });
                }

                return;
            }

            if (Syntax.Parent is BaseNamespaceDeclarationSyntax syntax == false)
            {
                return;
            }

            var nameSpace = syntax.GetFullNamespace();

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

            if (Types.TryGetValue(nameSpace + "." + name, out var type) == false)
            {
                type = new TypeInfo();

                Types.Add(nameSpace + "." + name, type);

                type.NameSpace = nameSpace;

                type.Name = name;

                type.Modifiers = modifiers;

                type.DynamicType = EDynamicType.Other;

                type.Using = new List<string>
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
                else if (bIsUInterface)
                {
                    type.DynamicType = EDynamicType.UInterface;
                }
            }

            type.Using = MergeUsing(usingList, type.Using);

            type.HasBase = bHasBase;

            type.HasStaticStruct |= bHasStaticStruct;

            type.HasStaticClass |= bHasStaticClass;

            type.HasGarbageCollectionHandle |= bHasGarbageCollectionHandle;

            type.HasHashCodeMethod |= bHasHashCodeMethod;

            type.HasEqualsMethod |= bHasEqualsMethod;

            type.HasOperatorEqualTo |= bHasOperatorEqualTo;

            type.HasOperatorNotEqualTo |= bHasOperatorNotEqualTo;
        }

        private static AttributeSyntax GetAttributeFromClass(ClassDeclarationSyntax Syntax, string Name)
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

    public class ErrorInfo
    {
        public string Name = "";

        public EDynamicType UnrealDynamicType;

        public Location ErrorLocation;
    }

    public enum EDynamicType
    {
        UClass,
        UStruct,
        UInterface,
        Other
    }

    public class TypeInfo
    {
        public EDynamicType DynamicType { get; set; }

        public List<string> Using { get; set; }

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