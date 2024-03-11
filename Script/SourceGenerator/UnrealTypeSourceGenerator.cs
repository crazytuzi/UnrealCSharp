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
        public void Execute(GeneratorExecutionContext context)
        {
            var UnrealTypeReceiver = context.SyntaxReceiver as UnrealTypeReceiver;
            if (UnrealTypeReceiver == null)
                return;
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
                    string souce = "using Script.CoreUObject;\n"+
                        "using Script.Library;\n"+
                        "namespace " + kv.Value.NameSpace + ";\n" +
                        "" + kv.Value.Modifiers + " class " + kv.Value.Name + ": IStaticStruct, IGarbageCollectionHandle\n" +
                    "{\n";
                    if (kv.Value.HasStaticStruct == false)
                    {
                        var FullPath = "/Script/CoreUObject.";
                        if (kv.Value.Name[0] == 'A' || kv.Value.Name[0] == 'U' || kv.Value.Name[0] == 'F')
                        {
                            FullPath += kv.Value.Name.Substring(1);
                        }
                        else
                        {
                            FullPath += kv.Value.Name;
                        }

                        souce +=
                            "\tpublic static UScriptStruct StaticStruct()\n" +
                            "\t{\n" +
                            $"\t\treturn UStructImplementation.UStruct_StaticStructImplementation(\"{FullPath}\");\n"+
                            "\t}\n";
                    }

                    if (kv.Value.HasGarbageCollectionHandle == false)
                    {
                        souce += "\tpublic nint GarbageCollectionHandle { get; set; }\n";
                    }
                    souce += "}";
                    context.AddSource(kv.Value.NameSpace + "." + kv.Value.Name + "gen.cs", souce);
                }
                else if (kv.Value.Type == EType.UClass || kv.Value.Type == EType.UInterface)
                {
                    string souce = "using Script.CoreUObject;\n" +
                        "using Script.Library;\n" +
                        "namespace " + kv.Value.NameSpace + ";\n" +
                       "" + kv.Value.Modifiers + " class " + kv.Value.Name + ": IStaticClass\n" +
                   "{\n";
                    if (kv.Value.HasStaticStruct == false)
                    {
                        var FullPath = "/Script/CoreUObject.";
                        if (kv.Value.Name[0] == 'A' || kv.Value.Name[0] == 'U' || kv.Value.Name[0] == 'F')
                        {
                            FullPath += kv.Value.Name.Substring(1);
                        }
                        else
                        {
                            FullPath += kv.Value.Name;
                        }

                        souce +=
                            "\tpublic new static UClass StaticClass()\n" +
                            "\t{\n" +
                            $"\t\treturn UObjectImplementation.UObject_StaticClassImplementation(\"{FullPath}\");\n" +
                            "\t}\n";
                    }

                    souce += "}";
                    context.AddSource(kv.Value.NameSpace + "." + kv.Value.Name + "gen.cs", souce);
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

        public void OnVisitSyntaxNode(SyntaxNode syntaxNode)
        {
            if (syntaxNode is ClassDeclarationSyntax cds ==true  )
            {
                ProcessClass(cds);
            }
        }
        private void ProcessClass(ClassDeclarationSyntax cds)
        {
            if (cds.Modifiers.ToArray().Any(modifier => modifier.Text == "partial") == false)
            {
                return;
            }
            if (cds.Parent is BaseNamespaceDeclarationSyntax ns == false)
            {
                return;
            }
            string NameSpace = ns.GetFullNamespace();
            string Name = cds.Identifier.ToString();
            bool IsUClass = cds.AttributeLists.ToList().Any(list => list.Attributes.All(att => att.GetText().ToString().IndexOf("UClass") >= 0));
            bool IsUStruct = cds.AttributeLists.ToList().Any(list => list.Attributes.All(att => att.GetText().ToString().IndexOf("UStruct") >= 0));
            bool IsUInterface = cds.AttributeLists.ToList().Any(list => list.Attributes.All(att => att.GetText().ToString().IndexOf("UInterface") >= 0));
            string Modifiers = string.Join(" ", cds.Modifiers.ToArray().Select(modifier => modifier.Text));


            var methods = cds.Members.Where(mem => mem is MethodDeclarationSyntax).ToList();

            bool HasStaticClass = methods.Any(m => ((MethodDeclarationSyntax)m).Identifier.ToString() == "StaticClass");
            bool HasStaticStruct = methods.Any(m => ((MethodDeclarationSyntax)m).Identifier.ToString() == "StaticStruct");
            bool HasGarbageCollectionHandle = cds.Members.Any(mem => mem is PropertyDeclarationSyntax && ((PropertyDeclarationSyntax)mem).Identifier.ToString() == "GarbageCollectionHandle");

            if (Types.TryGetValue(NameSpace + "." + Name, out var type) == false)
            {
                type = new TypeInfo();
                Types.Add(NameSpace + "." + Name, type);
                type.NameSpace = NameSpace;
                type.Name = Name;
                type.Modifiers = Modifiers;
                type.Type = EType.Other;
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

            type.HasStaticStruct |= HasStaticStruct;
            type.HasStaticClass |= HasStaticClass;
            type.HasGarbageCollectionHandle |= HasGarbageCollectionHandle;
            return;
        }
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

        public string Name { get; set; }
        public string NameSpace { get; set; }

        public string Modifiers { get; set; }

        public bool HasGarbageCollectionHandle { get; set; }
        public bool HasStaticClass { get; set; }
        public bool HasStaticStruct { get; set; }

    }


    public static class CodeAnalysisHelper
    {
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
