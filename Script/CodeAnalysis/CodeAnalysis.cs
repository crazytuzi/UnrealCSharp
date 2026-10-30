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

                _inputFileNames = new List<string>();

                for (var i = 2; i < args.Length; i++)
                {
                    _inputFileNames.Add(args[i]);
                }

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

                if (File.Exists(Path.Combine(_outputPathName, DynamicFileFileName)))
                {
                    _dynamicFile = JsonSerializer.Deserialize<Dictionary<string, string>>(
                        File.ReadAllText(Path.Combine(_outputPathName, DynamicFileFileName)));
                }
                else
                {
                    _dynamicFile = new Dictionary<string, string>();
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
                    foreach (var InputFileName in _inputFileNames)
                    {
                        var FileKeys = _overrideFile
                            .Where(Pair => IsSameFilePath(Pair.Value, InputFileName))
                            .Select(Pair => Pair.Key)
                            .ToList();

                        foreach (var Key in FileKeys)
                        {
                            _overrideFunction.Remove(Key);

                            _overrideFile.Remove(Key);
                        }
                    }
                }

                foreach (var InputFileName in _inputFileNames)
                {
                    RemoveDynamicTypes(InputFileName);
                }
            }
            else
            {
                _outputPathName = args[1];

                _inputFileNames = new List<string>();

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

                _dynamicFile = new Dictionary<string, string>();

                _overrideFunction = new Dictionary<string, List<string>>();

                _overrideFile = new Dictionary<string, string>();
            }
        }

        private static bool IsSameFilePath(string InPathA, string InPathB)
        {
            if (string.IsNullOrEmpty(InPathA) || string.IsNullOrEmpty(InPathB))
            {
                return false;
            }

            var PathComparison = OperatingSystem.IsWindows()
                ? StringComparison.OrdinalIgnoreCase
                : StringComparison.Ordinal;

            return string.Equals(
                InPathA.Replace('\\', '/').Trim(),
                InPathB.Replace('\\', '/').Trim(),
                PathComparison);
        }

        private void RemoveDynamicTypes(string InFile)
        {
            if (_dynamicFile == null || _dynamic == null || string.IsNullOrEmpty(InFile))
            {
                return;
            }

            var FileKeys = _dynamicFile
                .Where(Pair => IsSameFilePath(Pair.Value, InFile))
                .Select(Pair => Pair.Key)
                .ToList();

            foreach (var Key in FileKeys)
            {
                _dynamicFile.Remove(Key);

                foreach (var Names in _dynamic.Values)
                {
                    Names?.RemoveAll(Name => Name == Key);
                }
            }
        }

        private void AddDynamicType(string InCategory, string InName, string InFile)
        {
            if (_dynamic == null || string.IsNullOrEmpty(InName))
            {
                return;
            }

            if (!_dynamic.TryGetValue(InCategory, out var Names) || Names == null)
            {
                Names = new List<string>();

                _dynamic[InCategory] = Names;
            }

            if (!Names.Contains(InName))
            {
                Names.Add(InName);
            }

            if (_dynamicFile != null)
            {
                _dynamicFile[InName] = InFile;
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
                foreach (var InputFileName in _inputFileNames)
                {
                    AnalysisSingle(InputFileName);
                }
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

        private void AnalysisSingle(string InFile)
        {
            var Tree = CSharpSyntaxTree.ParseText(File.ReadAllText(InFile, Encoding.UTF8));

            var Root = (CompilationUnitSyntax)Tree.GetRoot();

            AnalysisOverride(InFile, Root);

            AnalysisDynamic(InFile, Root);
        }

        private void AnalysisOverride(string InFile, CompilationUnitSyntax InRoot)
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
                                        InFile;
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

        private void AnalysisDynamic(string InFile, CompilationUnitSyntax InRoot)
        {
            foreach (var RootMember in InRoot.Members)
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
                                        AddDynamicType("DynamicClass",
                                            $"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}", InFile);

                                        return;
                                    }

                                    if (Attribute.ToString().Equals("UStruct"))
                                    {
                                        AddDynamicType("DynamicStruct",
                                            $"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}", InFile);

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
                                        AddDynamicType("DynamicInterface",
                                            $"{NamespaceDeclaration.Name}.{InterfaceDeclaration.Identifier}", InFile);

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
                                        AddDynamicType("DynamicEnum",
                                            $"{NamespaceDeclaration.Name}.{EnumDeclaration.Identifier}", InFile);

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

            File.WriteAllText(Path.Combine(_outputPathName, DynamicFileFileName),
                JsonSerializer.Serialize(_dynamicFile,
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

        private readonly List<string> _inputFileNames;

        private readonly List<string> _inputPathNames;

        private readonly Dictionary<string, List<string>>? _overrideFunction;

        private readonly Dictionary<string, string>? _overrideFile;

        private readonly Dictionary<string, List<string>>? _dynamic;

        private readonly Dictionary<string, string>? _dynamicFile;

        private const string DynamicFileName = "Dynamic.json";

        private const string DynamicFileFileName = "DynamicFile.json";

        private const string OverrideFunctionFileName = "OverrideFunction.json";

        private const string OverrideFileFileName = "OverrideFile.json";
    }
}