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
            var Analysis = new CodeAnalysis(args);

            Analysis.Analysis();
        }

        private CodeAnalysis(string[] args)
        {
            _bIsSingle = bool.Parse(args[0]);

            if (_bIsSingle)
            {
                _outputPathName = args[1];

                _inputFileName = args[2];

                _inputPathNames = new List<string>();

                if (File.Exists(Path.Combine(_outputPathName, DynamicFileName)))
                {
                    _dynamic = JsonSerializer.Deserialize<Dictionary<string, List<string>>>(
                        File.ReadAllText(Path.Combine(_outputPathName, DynamicFileName)));
                }
                else
                {
                    _dynamic = new Dictionary<string, List<string>>
                    {
                        ["DynamicClass"] = new List<string>(),
                        ["DynamicStruct"] = new List<string>(),
                        ["DynamicEnum"] = new List<string>(),
                        ["DynamicInterface"] = new List<string>()
                    };
                }

                if (File.Exists(Path.Combine(_outputPathName, OverrideFunctionFileName)))
                {
                    _overrideFunction = JsonSerializer.Deserialize<Dictionary<string, List<string>>>(
                        File.ReadAllText(Path.Combine(_outputPathName, OverrideFunctionFileName)));
                }
                else
                {
                    _overrideFunction = new Dictionary<string, List<string>>();
                }

                if (File.Exists(Path.Combine(_outputPathName, OverrideFileFileName)))
                {
                    _overrideFile = JsonSerializer.Deserialize<Dictionary<string, string>>(
                        File.ReadAllText(Path.Combine(_outputPathName, OverrideFileFileName)));
                }
                else
                {
                    _overrideFile = new Dictionary<string, string>();
                }

                if (_overrideFunction != null && _overrideFile != null)
                {
                    var Pair = _overrideFile.FirstOrDefault(pair => pair.Value == _inputFileName);

                    if (Pair.Key != null)
                    {
                        _overrideFunction.Remove(Pair.Key);

                        _overrideFile.Remove(Pair.Key);
                    }
                }
            }
            else
            {
                _outputPathName = args[1];

                _inputFileName = "";

                _inputPathNames = new List<string>();

                for (var i = 2; i < args.Length; i++)
                {
                    _inputPathNames.Add(args[i]);
                }

                _dynamic = new Dictionary<string, List<string>>
                {
                    ["DynamicClass"] = new List<string>(),
                    ["DynamicStruct"] = new List<string>(),
                    ["DynamicEnum"] = new List<string>(),
                    ["DynamicInterface"] = new List<string>()
                };

                _overrideFunction = new Dictionary<string, List<string>>();

                _overrideFile = new Dictionary<string, string>();
            }
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

            if (_bIsSingle)
            {
                AnalysisSingle(_inputFileName);
            }
            else
            {
                foreach (var PathName in _inputPathNames)
                {
                    var Files = GetFiles(PathName);

                    foreach (var Item in Files)
                    {
                        AnalysisSingle(Item);
                    }
                }
            }

            WriteAll();
        }

        private void AnalysisSingle(string inFile)
        {
            var Tree = CSharpSyntaxTree.ParseText(File.ReadAllText(inFile, Encoding.UTF8));

            var Root = (CompilationUnitSyntax)Tree.GetRoot();

            AnalysisOverride(inFile, Root);

            AnalysisDynamic(Root);
        }

        private void AnalysisOverride(string inFile, CompilationUnitSyntax inRoot)
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
                                if (_overrideFile != null)
                                {
                                    _overrideFile[$"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}"] =
                                        inFile;
                                }

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
                                if (_overrideFunction != null)
                                {
                                    _overrideFunction[$"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}"] =
                                        Functions;
                                }
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
                                        _dynamic?["DynamicClass"].Add(ClassDeclaration.Identifier.ToString());

                                        return;
                                    }

                                    if (Attribute.ToString().Equals("UStruct"))
                                    {
                                        _dynamic?["DynamicStruct"].Add(ClassDeclaration.Identifier.ToString());

                                        return;
                                    }
                                }
                            }
                        }
                        else if (NameSpaceMember is InterfaceDeclarationSyntax InterfaceDeclaration)
                        {
                            foreach (var AttributeList in InterfaceDeclaration.AttributeLists)
                            {
                                foreach (var Attribute in AttributeList.Attributes)
                                {
                                    if (Attribute.ToString().Equals("UInterface"))
                                    {
                                        _dynamic?["DynamicInterface"].Add(InterfaceDeclaration.Identifier.ToString());

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
                                        _dynamic?["DynamicEnum"].Add(EnumDeclaration.Identifier.ToString());

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
            File.WriteAllText(Path.Combine(_outputPathName, DynamicFileName),
                JsonSerializer.Serialize(_dynamic,
                    new JsonSerializerOptions
                    {
                        WriteIndented = true,
                    }));

            File.WriteAllText(Path.Combine(_outputPathName, OverrideFunctionFileName),
                JsonSerializer.Serialize(_overrideFunction,
                    new JsonSerializerOptions
                    {
                        WriteIndented = true,
                    }));

            File.WriteAllText(Path.Combine(_outputPathName, OverrideFileFileName),
                JsonSerializer.Serialize(_overrideFile,
                    new JsonSerializerOptions
                    {
                        WriteIndented = true,
                    }));
        }

        private readonly bool _bIsSingle;

        private readonly string _outputPathName;

        private readonly string _inputFileName;

        private readonly List<string> _inputPathNames;

        private readonly Dictionary<string, List<string>>? _overrideFunction;

        private readonly Dictionary<string, string>? _overrideFile;

        private readonly Dictionary<string, List<string>>? _dynamic;

        private const string DynamicFileName = "Dynamic.json";

        private const string OverrideFunctionFileName = "OverrideFunction.json";

        private const string OverrideFileFileName = "OverrideFile.json";
    }
}