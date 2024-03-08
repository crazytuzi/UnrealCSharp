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

        private CodeAnalysis(string inInputPathName, string inOutputPathName)
        {
            _inputPathName = inInputPathName;

            _outputPathName = inOutputPathName;

            _dynamic = new Dictionary<string, List<string>>
            {
                ["DynamicClass"] = new List<string>(),
                ["DynamicStruct"] = new List<string>(),
                ["DynamicEnum"] = new List<string>(),
                ["DynamicInterface"] = new List<string>()
            };

            _override = new Dictionary<string, List<string>>();
        }

        private static List<string> GetFiles(string inPathName)
        {
            var Files = new List<string>();

            var DirectoryInfo = new DirectoryInfo(inPathName);

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
            if (!Directory.Exists(_outputPathName))
            {
                Directory.CreateDirectory(_outputPathName);
            }

            foreach (var Item in Directory.GetFiles(_outputPathName))
            {
                File.Delete(Item);
            }

            var Files = GetFiles(_inputPathName);

            foreach (var Item in Files)
            {
                var Tree = CSharpSyntaxTree.ParseText(File.ReadAllText(Item, Encoding.UTF8));

                var Root = (CompilationUnitSyntax)Tree.GetRoot();

                AnalysisIsOverride(Root);

                AnalysisDynamic(Root);
            }

            WriteAll();
        }

        private void AnalysisIsOverride(CompilationUnitSyntax inRoot)
        {
            foreach (var RootMember in inRoot.Members)
            {
                if (RootMember is BaseNamespaceDeclarationSyntax NamespaceDeclaration)
                {
                    foreach (var NameSpaceMember in NamespaceDeclaration.Members)
                    {
                        if (NameSpaceMember is ClassDeclarationSyntax ClassDeclaration)
                        {
                            var Functions = new List<string>();

                            var IsOverride = false;

                            foreach (var AttributeList in ClassDeclaration.AttributeLists)
                            {
                                foreach (var Attribute in AttributeList.Attributes)
                                {
                                    if (Attribute.ToString().Equals("Override"))
                                    {
                                        IsOverride = true;

                                        break;
                                    }
                                }
                            }

                            if (IsOverride)
                            {
                                foreach (var MemberDeclaration in ClassDeclaration.Members)
                                {
                                    if (MemberDeclaration is MethodDeclarationSyntax MethodDeclaration)
                                    {
                                        IsOverride = false;

                                        foreach (var AttributeList in MethodDeclaration.AttributeLists)
                                        {
                                            foreach (var Attribute in AttributeList.Attributes)
                                            {
                                                if (Attribute.ToString().Equals("Override"))
                                                {
                                                    IsOverride = true;

                                                    break;
                                                }
                                            }
                                        }

                                        if (IsOverride)
                                        {
                                            Functions.Add(MethodDeclaration.Identifier.ToString());
                                        }
                                    }
                                }
                            }

                            if (Functions.Count > 0)
                            {
                                _override.Add($"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}", Functions);
                            }
                        }
                    }
                }
            }
        }

        private void AnalysisDynamic(CompilationUnitSyntax inRoot)
        {
            foreach (var RootMember in inRoot.Members)
            {
                if (RootMember is BaseNamespaceDeclarationSyntax NamespaceDeclaration)
                {
                    foreach (var NameSpaceMember in NamespaceDeclaration.Members)
                    {
                        if (NameSpaceMember is ClassDeclarationSyntax ClassDeclaration)
                        {
                            foreach (var AttributeList in ClassDeclaration.AttributeLists)
                            {
                                foreach (var Attribute in AttributeList.Attributes)
                                {
                                    if (Attribute.ToString().Equals("UClass"))
                                    {
                                        _dynamic["DynamicClass"].Add(ClassDeclaration.Identifier.ToString());

                                        return;
                                    }

                                    if (Attribute.ToString().Equals("UStruct"))
                                    {
                                        _dynamic["DynamicStruct"].Add(ClassDeclaration.Identifier.ToString());

                                        return;
                                    }

                                    if (Attribute.ToString().Equals("UInterface"))
                                    {
                                        _dynamic["DynamicInterface"].Add(ClassDeclaration.Identifier.ToString());

                                        return;
                                    }
                                }
                            }
                        }
                        else if (NameSpaceMember is EnumDeclarationSyntax EnumDeclaration)
                        {
                            foreach (var AttributeList in EnumDeclaration.AttributeLists)
                            {
                                foreach (var Attribute in AttributeList.Attributes)
                                {
                                    if (Attribute.ToString().Equals("UEnum"))
                                    {
                                        _dynamic["DynamicEnum"].Add(EnumDeclaration.Identifier.ToString());

                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void WriteAll()
        {
            File.WriteAllText(Path.Combine(_outputPathName, "Override.json"),
                JsonSerializer.Serialize(_override,
                    new JsonSerializerOptions
                    {
                        WriteIndented = true,
                    }));

            File.WriteAllText(Path.Combine(_outputPathName, "Dynamic.json"),
                JsonSerializer.Serialize(_dynamic,
                    new JsonSerializerOptions
                    {
                        WriteIndented = true,
                    }));
        }

        private readonly string _inputPathName;

        private readonly string _outputPathName;

        private readonly Dictionary<string, List<string>> _override;

        private readonly Dictionary<string, List<string>> _dynamic;
    }
}