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

            foreach (var Item in Directory.GetFiles(OutputPathName))
            {
                File.Delete(Item);
            }

            var Files = GetFiles(InputPathName);

            foreach (var Item in Files)
            {
                Analysis(File.ReadAllText(Item, Encoding.UTF8), OutputPathName);
            }
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

        private static void Analysis(string InContent, string InPathName)
        {
            var Tree = CSharpSyntaxTree.ParseText(InContent);

            var Root = (CompilationUnitSyntax) Tree.GetRoot();

            foreach (BaseNamespaceDeclarationSyntax NamespaceDeclaration in Root.Members)
            {
                foreach (ClassDeclarationSyntax ClassDeclaration in NamespaceDeclaration.Members)
                {
                    var Functions = new List<string>();

                    var bIsOverride = false;

                    foreach (var Attribute in ClassDeclaration.AttributeLists)
                    {
                        if (Attribute.ToString().Equals("[IsOverride]"))
                        {
                            bIsOverride = true;

                            break;
                        }
                    }

                    if (bIsOverride)
                    {
                        foreach (MethodDeclarationSyntax MethodDeclaration in ClassDeclaration.Members)
                        {
                            bIsOverride = false;

                            foreach (var Attribute in MethodDeclaration.AttributeLists)
                            {
                                if (Attribute.ToString().Equals("[IsOverride]"))
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

                    if (Functions.Count > 0)
                    {
                        var FileName = Path.Combine(InPathName,
                            String.Format("{0}.{1}.json", NamespaceDeclaration.Name, ClassDeclaration.Identifier));

                        var Value = String.Format("{{\"Override\":{0}}}", JsonSerializer.Serialize(Functions));

                        File.WriteAllText(FileName, Value);
                    }
                }
            }
        }
    }
}