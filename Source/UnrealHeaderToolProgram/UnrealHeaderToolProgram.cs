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
	internal class SourceCodeGeneratorBase
	{
		[UhtExporter(Name = "UnrealCSharp", Description = "UnrealCSharp Source Code Generator", Options = UhtExporterOptions.Default, ModuleName = "UnrealCSharp")]
		private static void SourceCodeGeneratorUbtPluginExporter(IUhtExportFactory factory)
		{
			new SourceCodeGeneratorBase(factory).Generate();
		}

		private readonly IUhtExportFactory Factory;

		private UhtSession Session => Factory.Session;
		
		BorrowStringBuilder classborrower = new(StringBuilderCache.Big);


		public SourceCodeGeneratorBase(IUhtExportFactory factory)
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
			
			DirectoryReference configDirectory = DirectoryReference.Combine(Unreal.EngineDirectory, "Programs/UnrealBuildTool");
			ConfigHierarchy ini = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, configDirectory, BuildHostPlatform.Current.Platform);
			ini.GetArray("Plugins", "ScriptSupportedModules", out var supportedScriptModules);

			List<UhtClass> classes = new();
			
			List<Task?> tasks = new();
			
			foreach (var package in Session.Packages)
			{
				if (package.Module.ModuleType != UHTModuleType.EngineRuntime && package.Module.ModuleType != UHTModuleType.GameRuntime)
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
					classborrower.StringBuilder.Append(classObj.EngineName);

					classborrower.StringBuilder.Append("		Yes\r\n");
					
					classes.Add(classObj);
					
					tasks.Add(Factory.CreateTask(_ => { ExportClass(classObj); }));
				}
				else
				{
					classborrower.StringBuilder.Append(classObj.EngineName);

					classborrower.StringBuilder.Append("		No\r\n");
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
			// if (classObj.EngineName == "GameplayStatics" || classObj.EngineName =="KismetSystemLibrary")
			// {
			// 	return false;
			// }
			return classObj.ClassFlags.HasAnyFlags(EClassFlags.RequiredAPI | EClassFlags.MinimalAPI) &&
			       !classObj.ClassFlags.HasAnyFlags(EClassFlags.Interface);
		}

		/// <summary>
		/// Test to see if the given function should be exported
		/// </summary>
		/// <param name="function">Function to test</param>
		/// <returns>True if the function should be exported</returns>
		protected virtual bool CanExportFunction(UhtFunction function)
		{
			if (!function.FunctionFlags.HasAnyFlags(EFunctionFlags.Public))
			{
				return false;
			}
			
			// if (!function.FunctionFlags.HasAnyFlags(EFunctionFlags.RequiredAPI))
			// {
			// 	return false;
			// }

			if (!function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.RequiredAPI))
			{
				if (function.Outer is UhtClass uhtClass)
				{
					if (!Project.ContainsKey(uhtClass.Package.ShortName))
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			
			if (function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.CustomThunk))
			{
				return false;
			}
			
			if(function.MetaData.TryGetValue(UhtNames.BlueprintInternalUseOnly, out var value))
			{
				if (value == "true")
				{
					return false;
				}
			}
			
			if (function.FunctionType != UhtFunctionType.Function)
			{
				return false;
			}
			
			if(function is { HasReturnProperty: true, ReturnProperty: UhtMapProperty })
			{
				return false;
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
			return property.PropertyFlags.HasAnyFlags(EPropertyFlags.NativeAccessSpecifierPublic) && IsPropertyTypeSupported(property);
		}

		private static bool IsPropertyTypeSupported(UhtProperty property)
		{
			if (property is UhtArrayProperty arrayProperty)
			{
				return IsPropertyTypeSupported(arrayProperty.ValueProperty);
			}

			if (property is UhtObjectProperty objectProperty)
			{
				if(!objectProperty.Class.ClassFlags.HasAnyFlags(
					   EClassFlags.RequiredAPI | EClassFlags.MinimalAPI))
				{
					return false;
				}
			}

			if (property is UhtObjectPtrProperty objectPtrProperty)
			{
				if(!objectPtrProperty.Class.ClassFlags.HasAnyFlags(
					   EClassFlags.RequiredAPI | EClassFlags.MinimalAPI))
				{
					return false;
				}
			}

			if (property is UhtDelegateProperty or UhtMulticastDelegateProperty)
			{
				return false;
			}

			if (property is UhtStructProperty structProperty)
			{
				if (!structProperty.ScriptStruct.HasNoOpConstructor)
				{
					return false;
				}
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
				var fileName = Factory.MakePath(classObj.EngineName, ".binding.inl");
				
				Factory.CommitOutput(fileName, borrower.StringBuilder);
				
				ExportClasses.Add(classObj);
			}
		}

		private void Finish()
		{
			var fileName111 = Factory.MakePath("Out", ".binding.inl");
				
			Factory.CommitOutput(fileName111, classborrower.StringBuilder);
			
			var packages = new Dictionary<UhtPackage, BorrowStringBuilder>();

			foreach (var Class in ExportClasses)
			{
				if (!packages.ContainsKey(Class.Package))
				{
					packages.Add(Class.Package, new BorrowStringBuilder(StringBuilderCache.Big));

					packages[Class.Package].StringBuilder.Append("#pragma once\r\n\r\n");
				}
				
				packages[Class.Package].StringBuilder.AppendFormat("#include \"{0}.binding.inl\"\r\n", Class.EngineName);
			}

			foreach (var package in packages)
			{
				var fileName = Factory.MakePath(package.Key, "Header.binding.inl");
				
				Factory.CommitOutput(fileName, package.Value.StringBuilder);
			}
		}

		private bool ExportClass(StringBuilder builder, UhtClass classObj)
		{
			builder.Append("#pragma once\r\n\r\n");
			
			using BorrowStringBuilder headerBorrower = new(StringBuilderCache.Big);

			headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[classObj.Package.ShortName], classObj.HeaderFile.FilePath));
			
			using BorrowStringBuilder bodyBorrower = new(StringBuilderCache.Big);
			
			bodyBorrower.StringBuilder.AppendFormat("struct FRegister{0}\r\n" +
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
					if (property is UhtObjectProperty objectProperty1)
					{
						headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[objectProperty1.Class.Package.ShortName], objectProperty1.Class.HeaderFile.FilePath));
					}
					else if (property is UhtClassProperty classProperty)
					{
						if (classProperty.MetaClass != null)
						{
							headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[classProperty.MetaClass.Package.ShortName], classProperty.MetaClass.HeaderFile.FilePath));
						}
					}
					else if (property is UhtObjectPtrProperty objectPtrProperty)
					{
						headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[objectPtrProperty.Class.Package.ShortName], objectPtrProperty.Class.HeaderFile.FilePath));
					}
					else if (property is UhtArrayProperty { ValueProperty: UhtObjectProperty objectProperty2 })
					{
						headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[objectProperty2.Class.Package.ShortName], objectProperty2.Class.HeaderFile.FilePath));
					}
					
					ExportProperty(bodyBorrower.StringBuilder, classObj, property);

					bExportProperty = true;
				}
			}
			
			var bExportFunction = false;
		
			foreach (var function in classObj.Functions.Reverse())
			{
				if (CanExportFunction(function))
				{
					foreach (UhtProperty property in function.Children)
					{
						if (property is UhtObjectProperty objectProperty1)
						{
							headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[objectProperty1.Class.Package.ShortName], objectProperty1.Class.HeaderFile.FilePath));
						}
						else if (property is UhtArrayProperty { ValueProperty: UhtObjectProperty objectProperty2 })
						{
							headerBorrower.StringBuilder.AppendFormat("#include \"{0}\"\r\n", Path.Combine(HeaderPath[objectProperty2.Class.Package.ShortName], objectProperty2.Class.HeaderFile.FilePath));
						}
					}

					ExportFunction(bodyBorrower.StringBuilder, classObj, function);

					bExportFunction = true;
				}
			}
			
			// bodyBorrower.StringBuilder.Remove(builder.Length - 2, 2);

			bodyBorrower.StringBuilder.AppendFormat(";\r\n" + 
			                                        "\t}}\r\n" + 
			                                        "}};\r\n" + 
			                                        "\r\n" +
			                                        "static FRegister{0} Register{1};",
				classObj.EngineName, 
				classObj.EngineName);

			builder.Append(headerBorrower.StringBuilder);
			
			builder.Append("\r\n");

			builder.Append(bodyBorrower.StringBuilder);

			return bExportProperty || bExportFunction || true;
		}

		private static void ExportFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)
		{
			builder.Append($"\t\t\t.Function(\"{function.SourceName}\", BINDING_OVERLOAD({GetFunctionSignature(classObj, function)}, &{classObj.SourceName}::{function.SourceName}");

			if (function.HasParameters)
			{
				builder.Append(", ");
				
				builder.Append(GetFunctionParam(classObj, function));
			}

			if (!function.FunctionFlags.HasAnyFlags(EFunctionFlags.Static))
			{
				builder.Append(", EFunctionInteract::Virtual");
			}

			if (function.HasParameters)
			{
				builder.Append(GetFunctionDefaultParam(classObj, function));
			}
			
			builder.Append("))\r\n");
		}

		private static void ExportProperty(StringBuilder builder, UhtClass classObj, UhtProperty property)
		{
			builder.Append($"\t\t\t.Property(\"{property.SourceName}\", BINDING_PROPERTY(&{classObj.SourceName}::{property.SourceName}))\r\n");
		}

		private static string GetPropertySignature(UhtProperty? property)
		{
			if (property == null)
			{
				return "void";
			}
			
			var builder = new StringBuilder();
			
			var caps = property.PropertyCaps;

			var isParameter = true;
			bool isInterfaceProp = property is UhtInterfaceProperty;

			bool passCppArgsByRef = caps.HasAnyFlags(UhtPropertyCaps.PassCppArgsByRef);
			bool isConstParam = isParameter && (property.PropertyFlags.HasAnyFlags(EPropertyFlags.ConstParm) || (isInterfaceProp && !property.PropertyFlags.HasAnyFlags(EPropertyFlags.OutParm)));
			bool isConstArgsByRef = isParameter && property.ArrayDimensions == null && passCppArgsByRef && !property.PropertyFlags.HasAnyFlags(EPropertyFlags.ConstParm | EPropertyFlags.OutParm);
			bool isOnConstClass = false;
			if (property is UhtObjectProperty objectProperty)
			{
				isOnConstClass = objectProperty.Class.ClassFlags.HasAnyFlags(EClassFlags.Const);

				if (!isOnConstClass)
				{
					if(objectProperty.MetaData.TryGetValue(UhtNames.NativeConst, out var value))
					{
						isOnConstClass = true;
					}
				}
			}
			bool shouldHaveRef = property.PropertyFlags.HasAnyFlags(EPropertyFlags.OutParm | EPropertyFlags.ReferenceParm);

			bool constAtTheBeginning = isOnConstClass || isConstArgsByRef || (isConstParam && !shouldHaveRef);
			
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
				// if (interfaceProperty.InterfaceClass.ClassFlags.HasAnyFlags(EClassFlags.Interface))
				if (interfaceProperty.InterfaceClass == interfaceProperty.Session.IInterface)
				{
					builder.Append("FScriptInterface");
				}
				else
				{
					property.AppendText(builder, UhtPropertyTextType.ExportMember);
				}
			}
			// else if (property is UhtInterfaceProperty interfaceProperty)
			// {
			// 	builder.Append(interfaceProperty.InterfaceClass.SourceName);
			// }
			
			// else if (property is UhtObjectProperty objectProperty13)
			// {
			// 	// if (objectProperty13.Class.ClassFlags.HasAnyFlags(EClassFlags.Const))
			// 	// {
			// 	// 	builder.Append("const ");
			// 	// }
			// 	if (property.RefQualifier == UhtPropertyRefQualifier.ConstRef)
			// 	{
			// 		builder.Append("const ");
			// 	}
			// 	
			// 	builder.Append(objectProperty13.Class.SourceName).Append("*");
			// }
			else
			{
				property.AppendText(builder, UhtPropertyTextType.ExportMember);
			}

			bool fromConstClass = false;
			if (property.Outer != null)
			{
				if (property.Outer is UhtClass outerClass)
				{
					fromConstClass = outerClass.ClassFlags.HasAnyFlags(EClassFlags.Const);
				}
			}

			bool constAtTheEnd = fromConstClass || (isConstParam && shouldHaveRef);
			if (!constAtTheBeginning && constAtTheEnd)
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
			if (shouldHaveRef || isParameter && 
			    property.ArrayDimensions == null && 
			    (passCppArgsByRef || property.PropertyFlags.HasAnyFlags(EPropertyFlags.OutParm | EPropertyFlags.ReferenceParm)))
			{
				if (property is UhtArrayProperty or UhtStrProperty or UhtTextProperty or UhtInterfaceProperty or UhtSoftObjectProperty)
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
			
			StringBuilder builder = new StringBuilder();
			
			bool isOnConstClass = false;
			if (property is UhtObjectProperty objectProperty)
			{
				isOnConstClass = objectProperty.Class.ClassFlags.HasAnyFlags(EClassFlags.Const);
			}
			
			// property.PropertyFlags.HasAnyFlags(EPropertyFlags.ConstParm)
			
			if(property.PropertyFlags.HasAnyFlags(EPropertyFlags.ConstParm) || property.RefQualifier == UhtPropertyRefQualifier.ConstRef || isOnConstClass)
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

			if(property.RefQualifier == UhtPropertyRefQualifier.ConstRef)
			{
				builder.Append('&');
			}
			
			return builder.ToString();
		}

		private static string GetFunctionSignature(UhtClass classObj, UhtFunction function)
		{
			StringBuilder builder = new StringBuilder();
			
			builder.Append(GetReturnPropertySignature(function.ReturnProperty));
			// builder.Append(GetPropertySignature(function.ReturnProperty));

			if (function.FunctionFlags.HasAnyFlags(EFunctionFlags.Static))
			{
				builder.Append("(*)");
			}
			else
			{
				builder.AppendFormat("({0}::*)", classObj.SourceName);
			}

			builder.Append("(");

			foreach (UhtProperty property in function.Children)
			{
				if (!property.PropertyFlags.HasAnyFlags(EPropertyFlags.ReturnParm))
				{
					builder.Append(GetPropertySignature(property));

					builder.Append(",");
				}
			}

			if (function.HasParameters)
			{
				builder.Remove(builder.Length - 1, 1);
			}

			builder.Append(")");

			if (function.FunctionFlags.HasAnyFlags(EFunctionFlags.Const))
			{
				builder.Append("const");
			}

			return builder.ToString();
		}

		private static string GetFunctionParam(UhtClass classObj, UhtFunction function)
		{
			StringBuilder builder = new StringBuilder();
			
			builder.Append("TArray<FString>{");
			
			foreach (UhtProperty property in function.Children)
			{
				if (!property.PropertyFlags.HasAnyFlags(EPropertyFlags.ReturnParm))
				{
					builder.Append("\"");
					
					builder.Append(property.SourceName);
					
					builder.Append("\"");

					builder.Append(",");
				}
			}

			builder.Remove(builder.Length - 1, 1);

			builder.Append("}");

			return builder.ToString();
		}

		private static string GetFunctionDefaultParam(UhtClass classObj, UhtFunction function)
		{
			StringBuilder builder = new StringBuilder();
			
			foreach (UhtProperty property in function.Children)
			{
				if (!property.PropertyFlags.HasAnyFlags(EPropertyFlags.ReturnParm))
				{
					if (property.DefaultValueTokens != null)
					{
						builder.Append(",");

						StringBuilder DefaultValue = new StringBuilder();

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

			return builder.ToString();
		}
		
		private void GetPlugins(string InPathName, Dictionary<string,string> Plugins)
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

		private void GetModules(string InPathName, Dictionary<string,string> Modules)
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

		private List<UhtClass> ExportClasses = new();

		private Dictionary<string, string> Project = new Dictionary<string, string>();
		
		private Dictionary<string,string> HeaderPath = new();
	}
}
