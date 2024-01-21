using System.Text;
using System.Text.Json;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace CodeAnalysis
{
    internal class CodeAnalysis
    {
        static void Main(string[] args)
        {
            var InputPathName = args[0];

            var OutputPathName = args[1];

            var Analysis = new CodeAnalysis(InputPathName, OutputPathName);

            Analysis.Analysis();
        }

        private CodeAnalysis(string InInputPathName, string InOutputPathName)
        {
            InputPathName = InInputPathName;

            OutputPathName = InOutputPathName;

            Dynamic = new Dictionary<string, List<string>>
            {
                ["CSharpGeneratedClass"] = new List<string>(),
                ["CSharpBlueprintGeneratedClass"] = new List<string>(),
                ["CSharpScriptStruct"] = new List<string>(),
                ["CSharpEnum"] = new List<string>()
            };
        }

        private static List<string> GetFiles(string InPathName)
        {
            var Files = new List<string>();

            var DirectoryInfo = new DirectoryInfo(InPathName);

            foreach (var Item in DirectoryInfo.GetFiles("*.cs"))
            {
                Files.Add(Item.FullName);
            }

            foreach (var Directories in DirectoryInfo.GetDirectories())
            {
                if (!Directories.Name.Equals("Proxy") && !Directories.Name.Equals("obj"))
                {
                    foreach (var Item in Directories.GetFiles("*.cs", SearchOption.AllDirectories))
                    {
                        Files.Add(Item.FullName);
                    }
                }
            }

            return Files;
        }

        private void Analysis()
        {
            if (!Directory.Exists(OutputPathName))
            {
                Directory.CreateDirectory(OutputPathName);
            }

            foreach (var Item in Directory.GetFiles(OutputPathName))
            {
                File.Delete(Item);
            }

            var Files = GetFiles(InputPathName);

            foreach (var Item in Files)
            {
                var Tree = CSharpSyntaxTree.ParseText(File.ReadAllText(Item, Encoding.UTF8));

                var Root = (CompilationUnitSyntax)Tree.GetRoot();

                AnalysisIsOverride(Root);

                AnalysisDynamic(Root);
            }

            WriteAll();
        }

        private void AnalysisIsOverride(CompilationUnitSyntax InRoot)
        {
            foreach (var RootMember in InRoot.Members)
            {
                if (RootMember is BaseNamespaceDeclarationSyntax NamespaceDeclaration)
                {
                    foreach (var NameSpaceMember in NamespaceDeclaration.Members)
                    {
                        if (NameSpaceMember is ClassDeclarationSyntax ClassDeclaration)
                        {
                            var Functions = new List<string>();

                            var bIsOverride = false;

                            foreach (var Attribute in ClassDeclaration.AttributeLists)
                            {
                                if (Attribute.ToString().Equals("[Override]"))
                                {
                                    bIsOverride = true;

                                    break;
                                }
                            }

                            if (bIsOverride)
                            {
                                foreach (var MemberDeclaration in ClassDeclaration.Members)
                                {
                                    if (MemberDeclaration is MethodDeclarationSyntax MethodDeclaration)
                                    {
                                        bIsOverride = false;

                                        foreach (var Attribute in MethodDeclaration.AttributeLists)
                                        {
                                            if (Attribute.ToString().Equals("[Override]"))
                                            {
                                                bIsOverride = true;

                                                break;
                                            }
                                        }

                                        if (bIsOverride)
                                        {
                                            Functions.Add(MethodDeclaration.Identifier.ToString());
                                        }
                                    }
                                }
                            }

                            if (Functions.Count > 0)
                            {
                                var FileName = Path.Combine(OutputPathName,
                                    String.Format("{0}.{1}.json", NamespaceDeclaration.Name,
                                        ClassDeclaration.Identifier));

                                var Value = String.Format("{{\"Override\":{0}}}", JsonSerializer.Serialize(Functions));

                                File.WriteAllText(FileName, Value);
                            }
                        }
                    }
                }
            }
        }

        private void AnalysisDynamic(CompilationUnitSyntax InRoot)
        {
            foreach (var RootMember in InRoot.Members)
            {
                if (RootMember is BaseNamespaceDeclarationSyntax NamespaceDeclaration)
                {
                    foreach (var NameSpaceMember in NamespaceDeclaration.Members)
                    {
                        if (NameSpaceMember is ClassDeclarationSyntax ClassDeclaration)
                        {
                            foreach (var Attribute in ClassDeclaration.AttributeLists)
                            {
                                if (Attribute.ToString().Equals("[UClass]"))
                                {
                                    Dynamic["CSharpGeneratedClass"].Add(ClassDeclaration.Identifier.ToString());

                                    return;
                                }

                                if (Attribute.ToString().Equals("[UBlueprint]"))
                                {
                                    Dynamic["CSharpBlueprintGeneratedClass"].Add(ClassDeclaration.Identifier.ToString());

                                    return;
                                }

                                if (Attribute.ToString().Equals("[UStruct]"))
                                {
                                    Dynamic["CSharpScriptStruct"].Add(ClassDeclaration.Identifier.ToString());

                                    return;
                                }
                            }
                        }
                        else if (NameSpaceMember is EnumDeclarationSyntax EnumDeclaration)
                        {
                            foreach (var Attribute in EnumDeclaration.AttributeLists)
                            {
                                if (Attribute.ToString().Equals("[UEnum]"))
                                {
                                    Dynamic["CSharpEnum"].Add(EnumDeclaration.Identifier.ToString());

                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        private void WriteAll()
        {
            foreach (var Pair in Dynamic)
            {
                var FileName = Path.Combine(OutputPathName, Pair.Key + ".json");

                var Value = String.Format("{{\"{0}\":{1}}}", Pair.Key, JsonSerializer.Serialize(Pair.Value));

                File.WriteAllText(FileName, Value);
            }
        }

        private string InputPathName;

        private string OutputPathName;

        private Dictionary<string, List<string>> Dynamic;
    }
}