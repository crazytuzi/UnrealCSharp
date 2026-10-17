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
                    var Pair = _overrideFile.FirstOrDefault(pair => pair.Value == _inputFileName);

                    if (Pair.Key != null)
                    {
                        _overrideFunction.Remove(Pair.Key);

                        _overrideFile.Remove(Pair.Key);
                    }
                }

                // 单文件分析前，先清掉"这个文件"之前登记过的动态类型。
                // 否则改文件名/改类名后会残留旧条目，且同一类会被反复累加。
                PurgeDynamicByFile(_inputFileName);
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

                _dynamicFile = new Dictionary<string, string>();

                _overrideFunction = new Dictionary<string, List<string>>();

                _overrideFile = new Dictionary<string, string>();
            }
        }

        /// <summary>
        /// 比较两个文件路径是否指向同一个文件（忽略分隔符与大小写差异）。
        /// 单文件模式传进来的是 DirectoryWatcher 给的路径，JSON 里存的可能是另一种写法。
        /// </summary>
        private static bool IsSamePath(string InA, string InB)
        {
            if (string.IsNullOrEmpty(InA) || string.IsNullOrEmpty(InB))
            {
                return false;
            }

            return string.Equals(
                InA.Replace('\\', '/').Trim(),
                InB.Replace('\\', '/').Trim(),
                StringComparison.OrdinalIgnoreCase);
        }

        /// <summary>
        /// 移除某个源文件登记过的全部动态类型，保持清单与实际源码一致。
        /// </summary>
        private void PurgeDynamicByFile(string InFile)
        {
            if (_dynamicFile == null || _dynamic == null || string.IsNullOrEmpty(InFile))
            {
                return;
            }

            var StaleKeys = _dynamicFile
                .Where(Pair => IsSamePath(Pair.Value, InFile))
                .Select(Pair => Pair.Key)
                .ToList();

            foreach (var Key in StaleKeys)
            {
                _dynamicFile.Remove(Key);

                foreach (var Names in _dynamic.Values)
                {
                    Names.RemoveAll(Name => Name == Key);
                }
            }
        }

        /// <summary>
        /// 登记一个动态类型。
        /// 与原始实现（直接 Add）的区别：重复登记不会产生重复项。
        /// 原始实现会让 Dynamic.json 里的类名无限累加，进而让生成器重复处理同一个类。
        /// </summary>
        private void AddDynamic(string InCategory, string InName, string InFile)
        {
            if (_dynamic == null || string.IsNullOrEmpty(InName))
            {
                return;
            }

            if (!_dynamic.TryGetValue(InCategory, out var Names))
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

            AnalysisDynamic(inFile, Root);
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

        private void AnalysisDynamic(string inFile, CompilationUnitSyntax inRoot)
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
                                        AddDynamic("DynamicClass",
                                            $"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}", inFile);

                                        return;
                                    }

                                    if (Attribute.ToString().Equals("UStruct"))
                                    {
                                        AddDynamic("DynamicStruct",
                                            $"{NamespaceDeclaration.Name}.{ClassDeclaration.Identifier}", inFile);

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
                                        AddDynamic("DynamicInterface",
                                            $"{NamespaceDeclaration.Name}.{InterfaceDeclaration.Identifier}", inFile);

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
                                        AddDynamic("DynamicEnum",
                                            $"{NamespaceDeclaration.Name}.{EnumDeclaration.Identifier}", inFile);

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

        private readonly string _inputFileName;

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