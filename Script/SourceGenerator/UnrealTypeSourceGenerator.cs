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
        private static readonly DiagnosticDescriptor ErrorDymaticClass = new DiagnosticDescriptor(
            "UC_ERROR_01", 
            "Dynamic Class Must be partial", "{0} \"{1}\" must be a partial class", 
            "UnrealCSharp", 
            DiagnosticSeverity.Error, 
            isEnabledByDefault: true);
        public string GetPathName(string Name)
        {
            var FullPath = "/Script/CoreUObject.";
            if (Name[0] == 'A' || Name[0] == 'U' || Name[0] == 'F')
                FullPath += Name.Substring(1);
            else
                FullPath += Name;
            return FullPath;
        }
        public void Execute(GeneratorExecutionContext context)
        {
            var UnrealTypeReceiver = context.SyntaxReceiver as UnrealTypeReceiver;
            if (UnrealTypeReceiver == null)
                return;
            foreach(var error in UnrealTypeReceiver.Errors)
            {

                context.ReportDiagnostic(Diagnostic.Create(ErrorDymaticClass, error.ErrorLocation, error.UnrealType == EType.UClass ?"UClass" : "UStruct", error.Name));
            }
            foreach(var kv in UnrealTypeReceiver.Types)
            {
                if (kv.Value.Type == EType.Other)
                    continue;
                if (kv.Value.Type == EType.UStruct && kv.Value.HasStaticStruct && kv.Value.HasGarbageCollectionHandle)
                    continue;
                if (kv.Value.Type == EType.UClass && kv.Value.HasStaticClass)
                    continue;
                if (kv.Value.Type == EType.UInterface && kv.Value.HasStaticClass)
                    continue;
                if (kv.Value.Type == EType.UStruct)
                {
                    string souce = "";
                    kv.Value.Using.ForEach(str => souce += str);
                    souce += "namespace " + kv.Value.NameSpace + "\n" +
                        "{\n" +
                        "\t" + kv.Value.Modifiers + " class " + kv.Value.Name + ": IStaticStruct, IGarbageCollectionHandle\n" +
                    "\t{\n";
                    if (kv.Value.HasStaticStruct == false)
                    {
                        var FullPath = GetPathName(kv.Value.Name);
                        souce +=
                            "\t\tpublic static UScriptStruct StaticStruct()\n" +
                            "\t\t{\n" +
                            $"\t\t\treturn UStructImplementation.UStruct_StaticStructImplementation(\"{FullPath}\");\n"+
                            "\t\t}\n";
                    }

                    if (kv.Value.HasGarbageCollectionHandle == false)
                    {
                        souce += "\t\tpublic nint GarbageCollectionHandle { get; set; }\n";
                    }
                    if (kv.Value.HasEqualsMethod == false)
                    {
                        souce += $"\t\tpublic override bool Equals(object Other) => this == Other as {kv.Value.Name};\n";
                    }
                    if (kv.Value.HasHashCodeMethod == false)
                    {
                        souce += $"\t\tpublic override int GetHashCode() => (int)GarbageCollectionHandle;\n";
                    }
                    if (kv.Value.HasOperatorEqualTo == false)
                    {
                        souce += $"\t\tpublic static bool operator ==({kv.Value.Name} A, {kv.Value.Name} B) => UStructImplementation.UStruct_IdenticalImplementation(StaticStruct().GarbageCollectionHandle, A?.GarbageCollectionHandle??nint.Zero, B?.GarbageCollectionHandle??nint.Zero);\n";
                    }
                    if (kv.Value.HasOperatorNotEqualTo == false)
                    {
                        souce += $"\t\tpublic static bool operator !=({kv.Value.Name} A, {kv.Value.Name} B) => !UStructImplementation.UStruct_IdenticalImplementation(StaticStruct().GarbageCollectionHandle, A?.GarbageCollectionHandle??nint.Zero, B?.GarbageCollectionHandle??nint.Zero);\n";
                    }
                    souce += "\t}\n";
                    souce += "}";
                    context.AddSource(kv.Value.NameSpace + "." + kv.Value.Name + ".gen.cs", souce);
                }
                else if (kv.Value.Type == EType.UClass || kv.Value.Type == EType.UInterface)
                {
                    string souce = "";
                    kv.Value.Using.ForEach(str => souce += str);
                    souce +="namespace " + kv.Value.NameSpace + "\n" +
                        "{\n" +
                       "\t" + kv.Value.Modifiers + " class " + kv.Value.Name + ": IStaticClass\n" +
                   "\t{\n";
                    if (kv.Value.HasStaticStruct == false)
                    {
                        var FullPath = GetPathName(kv.Value.Name);
                        souce +=
                            "\t\tpublic new static UClass StaticClass()\n" +
                            "\t\t{\n" +
                            $"\t\t\treturn UObjectImplementation.UObject_StaticClassImplementation(\"{FullPath}\");\n" +
                            "\t\t}\n";
                    }

                    souce += "\t}\n";
                    souce += "}";
                    context.AddSource(kv.Value.NameSpace + "." + kv.Value.Name + ".gen.cs", souce);
                }
            }

        }

        public void Initialize(GeneratorInitializationContext context)
        {
            context.RegisterForSyntaxNotifications(() => new UnrealTypeReceiver());
        }
    }

    public class UnrealTypeReceiver : ISyntaxReceiver
    {
        public Dictionary<string, TypeInfo> Types = new Dictionary<string, TypeInfo>();
        public List<ErrorInfo> Errors = new List<ErrorInfo>();
        public void OnVisitSyntaxNode(SyntaxNode syntaxNode)
        {
            if (syntaxNode is ClassDeclarationSyntax cds == true)
            {
                ProcessClass(cds);
            }
        }
        private void ProcessClass(ClassDeclarationSyntax cds)
        {
            string Name = cds.Identifier.ToString();
            var UClassAttribute = GetAttributeFromClass(cds, "UClass");
            var UStructAttribute =  GetAttributeFromClass(cds, "UStruct");
            bool IsUClass = UClassAttribute != null;
            bool IsUStruct = UStructAttribute != null;
            if (cds.Modifiers.ToArray().Any(modifier => modifier.Text == "partial") == false)
            {
                AttributeSyntax ErrorAttribue = null;
                if (IsUClass)
                    ErrorAttribue = UClassAttribute;
                else
                    ErrorAttribue = UStructAttribute;
                if (IsUClass || IsUStruct)
                {
                    Errors.Add(new ErrorInfo
                    {
                        Name = Name,
                        UnrealType = IsUClass ? EType.UClass : EType.UStruct,
                        ErrorLocation = Location.Create(ErrorAttribue.SyntaxTree, ErrorAttribue.Span)
                    }); ;
                }

                return;
            }
            if (cds.Parent is BaseNamespaceDeclarationSyntax ns == false)
            {
                return;
            }
            string NameSpace = ns.GetFullNamespace();
            List<string> Using = cds.GetUsings();
            bool IsUInterface = cds.AttributeLists.Any(list => list.Attributes.Any(att => att.GetText().ToString().IndexOf("UInterface") >= 0));
            string Modifiers = string.Join(" ", cds.Modifiers.ToArray().Select(modifier => modifier.Text));


            var methods = cds.Members.Where(mem => mem is MethodDeclarationSyntax);

            bool HasStaticClass = methods.Any(m => ((MethodDeclarationSyntax)m).Identifier.ToString() == "StaticClass");
            bool HasStaticStruct = methods.Any(m => ((MethodDeclarationSyntax)m).Identifier.ToString() == "StaticStruct");
            bool HasGarbageCollectionHandle = cds.Members.Any(mem => mem is PropertyDeclarationSyntax && ((PropertyDeclarationSyntax)mem).Identifier.ToString() == "GarbageCollectionHandle");

            bool HasEqualsMethod = methods.Any(m =>
            {
                var method = ((MethodDeclarationSyntax)m);
                if (method.Identifier.ToString() != "Equals")
                    return false;
                if (method.ParameterList.Parameters.Count != 1)
                    return false;
                return true;
            });
            bool HasHashCodeMethod = methods.Any(m =>
            {
                var method = ((MethodDeclarationSyntax)m);
                if (method.Identifier.ToString() != "GetHashCode")
                    return false;
                if (method.ParameterList.Parameters.Count > 0)
                    return false;
                return true;
            });

            var operators = cds.Members.Where(mem => mem is OperatorDeclarationSyntax);
            var HasOperatorEqualTo = operators.Any(o =>
            {
                var op = ((OperatorDeclarationSyntax)o);
                if (op.OperatorToken.Text != "==")
                    return false;
                foreach (var param in op.ParameterList.Parameters)
                {
                    var t = (IdentifierNameSyntax)param.Type;
                    if (t.Identifier.Text != Name)
                        return false;
                }
                return true;
            });

            var HasOperatorNotEqualTo = operators.Any(o =>
            {
                var op = ((OperatorDeclarationSyntax)o);
                if (op.OperatorToken.Text != "!=")
                    return false;
                foreach (var param in op.ParameterList.Parameters)
                {
                    var t = (IdentifierNameSyntax)param.Type;
                    if (t.Identifier.Text != Name)
                        return false;
                }
                return true;
            });

            if (Types.TryGetValue(NameSpace + "." + Name, out var type) == false)
            {
                type = new TypeInfo();
                Types.Add(NameSpace + "." + Name, type);
                type.NameSpace = NameSpace;
                type.Name = Name;
                type.Modifiers = Modifiers;
                type.Type = EType.Other;
                type.Using = new List<string>() { 
                    "using Script.Library;\n", 
                    "using Script.UnrealCSharpCore;\n", 
                    "using Script.CoreUObject;\n" 
                };
            }

            if (type.Type == EType.Other)
            {
                if (IsUClass)
                    type.Type = EType.UClass;
                else if (IsUStruct)
                    type.Type = EType.UStruct;
                else if (IsUInterface)
                    type.Type = EType.UInterface;
            }
            type.Using = MerageUsing(Using, type.Using);
            type.HasStaticStruct |= HasStaticStruct;
            type.HasStaticClass |= HasStaticClass;
            type.HasGarbageCollectionHandle |= HasGarbageCollectionHandle;
            type.HasHashCodeMethod |= HasHashCodeMethod;
            type.HasEqualsMethod |= HasEqualsMethod;
            type.HasOperatorEqualTo |= HasOperatorEqualTo;
            type.HasOperatorNotEqualTo |= HasOperatorNotEqualTo;
            return;
        }

        private AttributeSyntax GetAttributeFromClass(ClassDeclarationSyntax cds, string name)
        {
            foreach (var atts in cds.AttributeLists)
            {
                foreach (var att in atts.Attributes)
                {
                    if (att.GetText().ToString().IndexOf(name) >= 0)
                    {
                        return att;
                    }
                }
            }
            return null;
        }
        private List<string> MerageUsing(List<string> using1, List<string> using2)
        {
            if (using1 == null && using2 != null)
                return using2;
            if (using2 == null && using1 != null)
                return using1;
            List<string> rtl = new List<string>();
            if (using1 == null && using2 == null)
                return rtl;
            foreach (string s in using1)
            {
                if (rtl.Contains(s))
                    continue;
                rtl.Add(s);
            }
            foreach (string s in using2)
            {
                if (rtl.Contains(s))
                    continue;
                rtl.Add(s);
            }
            return rtl;
        }
    }
    public class ErrorInfo
    {
        public string Name = "";
        public EType UnrealType;
        public Location ErrorLocation;
    }
    public enum EType
    {
        UClass,
        UStruct,
        UInterface,
        Other
    }
    public class TypeInfo
    {
        public EType Type { get; set; }

        public List<string> Using { get; set; }   
        public string Name { get; set; }
        public string NameSpace { get; set; }

        public string Modifiers { get; set; }

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
        public static List<string> GetUsings(this SyntaxNode cds)
        {
            List<string> rtl = new List<string>();
            if (cds is CompilationUnitSyntax cus)
            {
                foreach (var @using in cus.Usings)
                {
                    var str = @using.GetText().ToString().Replace(" ", "").Replace("\t", "").Replace("\n", "").Replace("\r", "").Trim() + "\n";
                    str = str.Replace("using", "using ");
                    rtl.Add(str);

                }
                return rtl;
            }
            if (cds.Parent == null)
                return rtl;
            return cds.Parent.GetUsings();
        }

        
        public static string GetFullNamespace(this BaseNamespaceDeclarationSyntax ns)
        {
            if (ns.Parent is BaseNamespaceDeclarationSyntax bns == false) 
            {
                return ns.Name.ToString();
            }
            else
            {
                return bns.GetFullNamespace() + "." + ns.Name.ToString();
            }
        }
    }
}
