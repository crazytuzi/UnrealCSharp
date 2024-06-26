// Copyright Epic Games, Inc. All Rights Reserved.

using EpicGames.Core;
using EpicGames.UHT.Types;
using EpicGames.UHT.Utils;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EpicGames.UHT.Tables;
using UnrealBuildBase;
using UnrealBuildTool;

namespace SourceCodeGeneratorUbtPlugin
{
    [UnrealHeaderTool]
    internal class SourceCodeGenerator
    {
        [UhtExporter(Name = "UnrealCSharp", Description = "UnrealCSharp Source Code Generator",
            Options = UhtExporterOptions.Default, ModuleName = "UnrealCSharp")]
        private static void SourceCodeGeneratorExporter(IUhtExportFactory factory)
        {
            new SourceCodeGenerator(factory).Generate();
        }

        private readonly IUhtExportFactory Factory;

        private UhtSession Session => Factory.Session;

        private List<UhtClass> ExportClasses = new();

        private HashSet<string> Project = new();

        private Dictionary<string, string> HeaderPath = new();

        private const string BindingSuffix = ".binding.inl";

        private const string HeaderSuffix = ".header.inl";

        public SourceCodeGenerator(IUhtExportFactory factory)
        {
            Factory = factory;
        }

        /// <summary>
        /// Export all the classes in all the packages
        /// </summary>
        private void Generate()
        {
            if (Session is { EngineDirectory: not null, ProjectDirectory: not null })
            {
                GetModules(Path.GetFullPath(Path.Combine(Session.ProjectDirectory, "Source/")), Project);

                GetModules(Path.GetFullPath(Path.Combine(Session.ProjectDirectory, "Source/")), HeaderPath);

                GetModules(Path.GetFullPath(Path.Combine(Session.ProjectDirectory, "Plugins/")), HeaderPath);

                GetPlugins(Path.GetFullPath(Path.Combine(Session.ProjectDirectory, "Plugins/")), HeaderPath);

                GetModules(Path.GetFullPath(Path.Combine(Session.EngineDirectory, "Source/Developer/")), HeaderPath);

                GetModules(Path.GetFullPath(Path.Combine(Session.EngineDirectory, "Source/Editor/")), HeaderPath);

                GetModules(Path.GetFullPath(Path.Combine(Session.EngineDirectory, "Source/Programs/")), HeaderPath);

                GetModules(Path.GetFullPath(Path.Combine(Session.EngineDirectory, "Source/Runtime/")), HeaderPath);

                GetModules(Path.GetFullPath(Path.Combine(Session.EngineDirectory, "Plugins/")), HeaderPath);

                GetPlugins(Path.GetFullPath(Path.Combine(Session.EngineDirectory, "Plugins/")), HeaderPath);
            }

            DirectoryReference configDirectory =
                DirectoryReference.Combine(Unreal.EngineDirectory, "Programs/UnrealBuildTool");
            ConfigHierarchy ini = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, configDirectory,
                BuildHostPlatform.Current.Platform);
            ini.GetArray("Plugins", "ScriptSupportedModules", out var supportedScriptModules);

            List<UhtClass> classes = new();

            List<Task?> tasks = new();

            foreach (var package in Session.Packages)
            {
                if (package.Module.ModuleType != UHTModuleType.EngineRuntime &&
                    package.Module.ModuleType != UHTModuleType.GameRuntime)
                {
                    continue;
                }

                // if (supportedScriptModules != null && !supportedScriptModules.Any(x => String.Compare(x, package.Module.Name, StringComparison.OrdinalIgnoreCase) == 0))
                // {
                // 	continue;
                // }

                QueueClassExports(package, package, classes, tasks);
            }

            var waitTasks = tasks.Where(Task => Task != null).Cast<Task>().ToArray();

            if (waitTasks.Length > 0)
            {
                Task.WaitAll(waitTasks);
            }

            Finish();
        }

        /// <summary>
        /// Collect the classes to be exported for the given package and type
        /// </summary>
        /// <param name="package">Package being exported</param>
        /// <param name="type">Type to test for exporting</param>
        /// <param name="classes">Collection of exported classes</param>
        /// <param name="tasks">Collection of queued tasks</param>
        private void QueueClassExports(UhtPackage package, UhtType type, List<UhtClass> classes, List<Task?> tasks)
        {
            if (type is UhtClass classObj)
            {
                if (CanExportClass(classObj))
                {
                    classes.Add(classObj);

                    tasks.Add(Factory.CreateTask(_ => { ExportClass(classObj); }));
                }
            }

            foreach (var child in type.Children)
            {
                QueueClassExports(package, child, classes, tasks);
            }
        }

        /// <summary>
        /// Test to see if the given class should be exported
        /// </summary>
        /// <param name="classObj">Class to test</param>
        /// <returns>True if the class should be exported, false if not</returns>
        protected virtual bool CanExportClass(UhtClass classObj)
        {
            return !classObj.ClassFlags.HasAnyFlags(EClassFlags.Interface) &&
                   IsClassTypeSupported(classObj);
        }

        /// <summary>
        /// Test to see if the given function should be exported
        /// </summary>
        /// <param name="function">Function to test</param>
        /// <returns>True if the function should be exported</returns>
        protected virtual bool CanExportFunction(UhtFunction function)
        {
            if (function.FunctionType != UhtFunctionType.Function)
            {
                return false;
            }

            if (!function.FunctionFlags.HasAnyFlags(EFunctionFlags.Public))
            {
                return false;
            }

            if (function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.CustomThunk))
            {
                return false;
            }

            if (function is { HasReturnProperty: true, ReturnProperty: UhtMapProperty })
            {
                return false;
            }

            if (!function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.RequiredAPI))
            {
                if (function.Outer is UhtClass classObj)
                {
                    if (!Project.Contains(classObj.Package.ShortName))
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }

            foreach (var child in function.Children)
            {
                if (child is UhtProperty property && !IsPropertyTypeSupported(property))
                {
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Test to see if the given property should be exported
        /// </summary>
        /// <param name="property">Property to test</param>
        /// <returns>True if the property should be exported</returns>
        protected virtual bool CanExportProperty(UhtProperty property)
        {
            return property.PropertyFlags.HasAnyFlags(EPropertyFlags.NativeAccessSpecifierPublic) &&
                   IsPropertyTypeSupported(property);
        }

        private static bool IsClassTypeSupported(UhtClass classObj)
        {
            return classObj.ClassFlags.HasAnyFlags(EClassFlags.RequiredAPI | EClassFlags.MinimalAPI);
        }

        private static bool IsPropertyTypeSupported(UhtProperty property)
        {
            if (property is UhtArrayProperty arrayProperty)
            {
                return IsPropertyTypeSupported(arrayProperty.ValueProperty);
            }

            if (property is UhtObjectProperty objectProperty)
            {
                if (!IsClassTypeSupported(objectProperty.Class))
                {
                    return false;
                }
            }

            if (property is UhtObjectPtrProperty objectPtrProperty)
            {
                if (!IsClassTypeSupported(objectPtrProperty.Class))
                {
                    return false;
                }
            }

            if (property is UhtDelegateProperty or UhtMulticastDelegateProperty)
            {
                return false;
            }

            if (property is UhtStructProperty { ScriptStruct.HasNoOpConstructor: false })
            {
                return false;
            }

            return property is { IsBitfield: false, IsStaticArray: false };
        }

        /// <summary>
        /// Export the given class
        /// </summary>
        /// <param name="classObj">Class to export</param>
        private void ExportClass(UhtClass classObj)
        {
            using BorrowStringBuilder borrower = new(StringBuilderCache.Big);

            if (ExportClass(borrower.StringBuilder, classObj))
            {
                var fileName = Factory.MakePath(classObj.EngineName, BindingSuffix);

                Factory.CommitOutput(fileName, borrower.StringBuilder);

                ExportClasses.Add(classObj);
            }
        }

        private void Finish()
        {
            var packages = new Dictionary<UhtPackage, BorrowStringBuilder>();

            foreach (var Class in ExportClasses)
            {
                if (!packages.ContainsKey(Class.Package))
                {
                    packages.Add(Class.Package, new BorrowStringBuilder(StringBuilderCache.Big));

                    packages[Class.Package].StringBuilder.Append("#pragma once\r\n\r\n");
                }

                packages[Class.Package].StringBuilder.Append(GenerateInclude($"{Class.EngineName}{BindingSuffix}"));
            }

            foreach (var package in packages)
            {
                var fileName = Factory.MakePath(package.Key, HeaderSuffix);

                Factory.CommitOutput(fileName, package.Value.StringBuilder);
            }
        }

        private bool ExportClass(StringBuilder builder, UhtClass classObj)
        {
            builder.Append("#pragma once\r\n\r\n");

            var DependencyClasses = new HashSet<UhtClass> { classObj };

            using BorrowStringBuilder bodyBorrower = new(StringBuilderCache.Big);

            var bodyBuilder = bodyBorrower.StringBuilder;

            bodyBuilder.AppendFormat("struct FRegister{0}\r\n" +
                                     "{{\r\n" +
                                     "\tFRegister{1}()\r\n" +
                                     "\t{{\r\n" +
                                     "\t\tTBindingClassBuilder<{2}>(NAMESPACE_BINDING)\r\n",
                classObj.EngineName,
                classObj.EngineName,
                classObj.SourceName);

            var bExportProperty = false;

            foreach (var child in classObj.Children)
            {
                if (child is UhtProperty property && CanExportProperty(property))
                {
                    if (property is UhtClassProperty classProperty)
                    {
                        if (classProperty.MetaClass != null)
                        {
                            DependencyClasses.Add(classProperty.MetaClass);
                        }
                    }
                    else if (property is UhtObjectPtrProperty objectPtrProperty)
                    {
                        DependencyClasses.Add(objectPtrProperty.Class);
                    }
                    else if (property is UhtObjectProperty objectProperty)
                    {
                        DependencyClasses.Add(objectProperty.Class);
                    }
                    else if (property is UhtSoftClassProperty softClassProperty)
                    {
                        if (softClassProperty.MetaClass != null)
                        {
                            DependencyClasses.Add(softClassProperty.MetaClass);
                        }
                    }
                    else if (property is UhtSoftObjectProperty softObjectProperty)
                    {
                        DependencyClasses.Add(softObjectProperty.Class);
                    }
                    else if (property is UhtArrayProperty { ValueProperty: UhtObjectProperty valueProperty })
                    {
                        DependencyClasses.Add(valueProperty.Class);
                    }

                    ExportProperty(bodyBuilder, classObj, property);

                    bExportProperty = true;
                }
            }

            var bExportFunction = false;

            foreach (var function in classObj.Functions.Reverse())
            {
                if (CanExportFunction(function))
                {
                    foreach (var child in function.Children)
                    {
                        if (child is UhtProperty property)
                        {
                            if (property is UhtObjectProperty objectProperty)
                            {
                                DependencyClasses.Add(objectProperty.Class);
                            }
                            else if (property is UhtArrayProperty { ValueProperty: UhtObjectProperty ValueProperty })
                            {
                                DependencyClasses.Add(ValueProperty.Class);
                            }
                        }
                    }

                    ExportFunction(bodyBuilder, classObj, function);

                    bExportFunction = true;
                }
            }

            foreach (var DependencyClass in DependencyClasses)
            {
                builder.Append(GetInclude(DependencyClass));
            }

            builder.Append("\r\n");

            bodyBuilder.Remove(bodyBuilder.Length - 2, 2);

            bodyBuilder.AppendFormat(";\r\n" +
                                     "\t}}\r\n" +
                                     "}};\r\n" +
                                     "\r\n" +
                                     "static FRegister{0} Register{1};",
                classObj.EngineName,
                classObj.EngineName);

            builder.Append(bodyBuilder);

            return bExportProperty || bExportFunction;
        }

        private static void ExportFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)
        {
            builder.Append(
                $"\t\t\t.Function(\"{function.SourceName}\", BINDING_OVERLOAD({GetFunctionSignature(classObj, function)}, &{classObj.SourceName}::{function.SourceName}");

            if (function.HasParameters)
            {
                builder.Append($", {GetFunctionParamName(function)}");
            }

            if (!function.FunctionFlags.HasAnyFlags(EFunctionFlags.Static))
            {
                builder.Append(", EFunctionInteract::Virtual");
            }

            if (function.HasParameters)
            {
                builder.Append(GetFunctionDefaultValue(function));
            }

            builder.Append("))\r\n");
        }

        private static void ExportProperty(StringBuilder builder, UhtClass classObj, UhtProperty property)
        {
            builder.Append(
                $"\t\t\t.Property(\"{property.SourceName}\", BINDING_PROPERTY(&{classObj.SourceName}::{property.SourceName}))\r\n");
        }

        private static string GetParamPropertySignature(UhtProperty? property)
        {
            if (property == null)
            {
                return "void";
            }

            var builder = new StringBuilder();

            var caps = property.PropertyCaps;

            var isInterfaceProp = property is UhtInterfaceProperty;

            var passCppArgsByRef = caps.HasAnyFlags(UhtPropertyCaps.PassCppArgsByRef);

            var isConstParam = property.PropertyFlags.HasAnyFlags(EPropertyFlags.ConstParm) ||
                               (isInterfaceProp && !property.PropertyFlags.HasAnyFlags(EPropertyFlags.OutParm));

            var isConstArgsByRef = property.ArrayDimensions == null && passCppArgsByRef &&
                                   !property.PropertyFlags.HasAnyFlags(
                                       EPropertyFlags.ConstParm | EPropertyFlags.OutParm);

            var isOnConstClass = false;

            if (property is UhtObjectProperty objectProperty)
            {
                isOnConstClass = objectProperty.Class.ClassFlags.HasAnyFlags(EClassFlags.Const) ||
                                 objectProperty.MetaData.TryGetValue(UhtNames.NativeConst, out _);
            }

            var shouldHaveRef =
                property.PropertyFlags.HasAnyFlags(EPropertyFlags.OutParm | EPropertyFlags.ReferenceParm);

            var constAtTheBeginning = isOnConstClass || isConstArgsByRef || (isConstParam && !shouldHaveRef);

            if (constAtTheBeginning)
            {
                if (property is UhtArrayProperty or UhtInterfaceProperty or UhtSoftObjectProperty)
                {
                    if (property.RefQualifier == UhtPropertyRefQualifier.ConstRef)
                    {
                        builder.Append("const ");
                    }
                }
                else
                {
                    builder.Append("const ");
                }
            }

            if (property is UhtEnumProperty enumProperty)
            {
                builder.Append(enumProperty.Enum.CppType);
            }
            else if (property is UhtInterfaceProperty interfaceProperty)
            {
                if (interfaceProperty.InterfaceClass == interfaceProperty.Session.IInterface)
                {
                    builder.Append("FScriptInterface");
                }
                else
                {
                    property.AppendText(builder, UhtPropertyTextType.ExportMember);
                }
            }
            else
            {
                property.AppendText(builder, UhtPropertyTextType.ExportMember);
            }

            var fromConstClass = false;

            if (property.Outer is UhtClass outerClass)
            {
                fromConstClass = outerClass.ClassFlags.HasAnyFlags(EClassFlags.Const);
            }

            var constAtTheEnd = fromConstClass || (isConstParam && shouldHaveRef);

            if (constAtTheEnd)
            {
                if (property is UhtArrayProperty or UhtInterfaceProperty or UhtSoftObjectProperty)
                {
                    if (property.RefQualifier == UhtPropertyRefQualifier.ConstRef)
                    {
                        builder.Append(" const");
                    }
                }
                else
                {
                    builder.Append(" const");
                }
            }

            shouldHaveRef = passCppArgsByRef;

            if (shouldHaveRef ||
                property.ArrayDimensions == null &&
                (passCppArgsByRef ||
                 property.PropertyFlags.HasAnyFlags(EPropertyFlags.OutParm | EPropertyFlags.ReferenceParm)))
            {
                if (property is UhtArrayProperty or UhtStrProperty or UhtTextProperty or UhtInterfaceProperty
                    or UhtSoftObjectProperty)
                {
                    if (property.RefQualifier != UhtPropertyRefQualifier.None)
                    {
                        builder.Append('&');
                    }
                }
                else
                {
                    builder.Append('&');
                }
            }

            return builder.ToString();
        }

        private static string GetReturnPropertySignature(UhtProperty? property)
        {
            if (property == null)
            {
                return "void";
            }

            var builder = new StringBuilder();

            if (property.PropertyFlags.HasAnyFlags(EPropertyFlags.ConstParm) ||
                property.RefQualifier == UhtPropertyRefQualifier.ConstRef)
            {
                builder.Append("const ");
            }

            if (property is UhtEnumProperty enumProperty)
            {
                builder.Append(enumProperty.Enum.CppType);
            }
            else
            {
                property.AppendText(builder, UhtPropertyTextType.ExportMember);
            }

            if (property.RefQualifier == UhtPropertyRefQualifier.ConstRef)
            {
                builder.Append('&');
            }

            return builder.ToString();
        }

        private static string GetFunctionSignature(UhtClass classObj, UhtFunction function)
        {
            var builder = new StringBuilder();

            builder.Append(GetReturnPropertySignature(function.ReturnProperty));

            if (function.FunctionFlags.HasAnyFlags(EFunctionFlags.Static))
            {
                builder.Append("(*)");
            }
            else
            {
                builder.Append($"({classObj.SourceName}::*)");
            }

            builder.Append('(');

            foreach (var child in function.Children)
            {
                if (child is UhtProperty property)
                {
                    if (!property.PropertyFlags.HasAnyFlags(EPropertyFlags.ReturnParm))
                    {
                        builder.Append(GetParamPropertySignature(property));

                        builder.Append(", ");
                    }
                }
            }

            if (function.HasParameters)
            {
                builder.Remove(builder.Length - 2, 2);
            }

            builder.Append(')');

            if (function.FunctionFlags.HasAnyFlags(EFunctionFlags.Const))
            {
                builder.Append("const");
            }

            return builder.ToString();
        }

        private static string GetFunctionParamName(UhtFunction function)
        {
            var builder = new StringBuilder();

            builder.Append("TArray<FString>{");

            foreach (var child in function.Children)
            {
                if (child is UhtProperty property)
                {
                    if (!property.PropertyFlags.HasAnyFlags(EPropertyFlags.ReturnParm))
                    {
                        builder.Append($"\"{property.SourceName}\", ");
                    }
                }
            }

            builder.Remove(builder.Length - 2, 2);

            builder.Append('}');

            return builder.ToString();
        }

        private static string GetFunctionDefaultValue(UhtFunction function)
        {
            var builder = new StringBuilder();

            foreach (var child in function.Children)
            {
                if (child is UhtProperty property)
                {
                    if (!property.PropertyFlags.HasAnyFlags(EPropertyFlags.ReturnParm))
                    {
                        if (property.DefaultValueTokens != null)
                        {
                            builder.Append(", ");

                            var DefaultValue = new StringBuilder();

                            foreach (var ValueToken in property.DefaultValueTokens)
                            {
                                DefaultValue.Append(ValueToken.Value);
                            }

                            if (DefaultValue.ToString() == "NULL")
                            {
                                builder.Append("nullptr");
                            }
                            else
                            {
                                builder.Append(DefaultValue);
                            }
                        }
                    }
                }
            }

            return builder.ToString();
        }

        private string GetHeaderFile(UhtClass classObj)
        {
            return Path.Combine(HeaderPath[classObj.Package.ShortName], classObj.HeaderFile.FilePath);
        }

        private static string GenerateInclude(string file)
        {
            return $"#include \"{file}\"\r\n";
        }

        private string GetInclude(UhtClass classObj)
        {
            return GenerateInclude(GetHeaderFile(classObj));
        }

        private void GetPlugins(string InPathName, Dictionary<string, string> Plugins)
        {
            var Suffix = "*.uplugin";

            var DirectoryInfo = new DirectoryInfo(InPathName);

            foreach (var Item in DirectoryInfo.GetFiles(Suffix))
            {
                if (Item.DirectoryName != null)
                {
                    Plugins[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
                }
            }

            foreach (var Directories in DirectoryInfo.GetDirectories())
            {
                foreach (var Item in Directories.GetFiles(Suffix, SearchOption.AllDirectories))
                {
                    if (Item.DirectoryName != null)
                    {
                        Plugins[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
                    }
                }
            }
        }

        private void GetModules(string InPathName, Dictionary<string, string> Modules)
        {
            var Suffix = "*.Build.cs";

            var DirectoryInfo = new DirectoryInfo(InPathName);

            foreach (var Item in DirectoryInfo.GetFiles(Suffix))
            {
                if (Item.DirectoryName != null)
                {
                    Modules[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
                }
            }

            foreach (var Directories in DirectoryInfo.GetDirectories())
            {
                foreach (var Item in Directories.GetFiles(Suffix, SearchOption.AllDirectories))
                {
                    if (Item.DirectoryName != null)
                    {
                        Modules[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
                    }
                }
            }
        }

        private void GetModules(string InPathName, HashSet<string> Modules)
        {
            var Suffix = "*.Build.cs";

            var DirectoryInfo = new DirectoryInfo(InPathName);

            foreach (var Item in DirectoryInfo.GetFiles(Suffix))
            {
                Modules.Add(Item.Name.Remove(Item.Name.Length - Suffix.Length + 1));
            }

            foreach (var Directories in DirectoryInfo.GetDirectories())
            {
                foreach (var Item in Directories.GetFiles(Suffix, SearchOption.AllDirectories))
                {
                    if (Item.DirectoryName != null)
                    {
                        Modules.Add(Item.Name.Remove(Item.Name.Length - Suffix.Length + 1));
                    }
                }
            }
        }
    }
}