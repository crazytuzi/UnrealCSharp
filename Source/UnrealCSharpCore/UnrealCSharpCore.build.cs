// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using EpicGames.Core;
using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealCSharpCore : ModuleRules
{
	public UnrealCSharpCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

#if UE_5_5_OR_LATER
		UndefinedIdentifierWarningLevel = WarningLevel.Off;
#else
		bEnableUndefinedIdentifierWarnings = false;
#endif

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
				"Mono"
				// ... add other public dependencies that you statically link with here ...
			}
		);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"DirectoryWatcher"
					// ... add other public dependencies that you statically link with here ...
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"BlueprintGraph",
					"UnrealEd"
					// ... add other public dependencies that you statically link with here ...
				}
			);
		}

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Json",
				"CrossVersion",
				"Projects"
				// ... add private dependencies that you statically link with here ...	
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UMGEditor"
					// ... add private dependencies that you statically link with here ...	
				}
			);
		}

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

		GeneratorModules();

		var SettingFilePath = Path.Combine(Target.ProjectFile.Directory.FullName,
			"Config",
			"DefaultUnrealCSharpEditorSetting.ini");

		var SettingConfigFile = File.Exists(SettingFilePath)
			? new ConfigFile(new FileReference(SettingFilePath))
			: new ConfigFile();

		var SettingSection = "/Script/UnrealCSharpCore.UnrealCSharpEditorSetting";

		bool GetBoolValue(string key, bool defaultValue)
		{
			if (SettingConfigFile.TryGetSection(SettingSection, out var SettingConfigSection))
			{
				var SettingConfigHierarchySection = new ConfigHierarchySection(
					new List<ConfigFileSection> { SettingConfigSection });

				if (SettingConfigHierarchySection.TryGetValue(key, out var Value))
				{
					return bool.Parse(Value.ToLower());
				}
			}

			return defaultValue;
		}

		PublicDefinitions.Add($"WITH_BINDING={(GetBoolValue("bEnableExport", false) ? "1" : "0")}");
	}

	private void GeneratorModules()
	{
		var ProjectPath = Path.GetDirectoryName(Target.ProjectFile?.FullName);

		if (ProjectPath == null)
		{
			return;
		}

		var Intermediate = Path.Combine(ProjectPath, "Intermediate");

		var JsonFullFilename = Path.Combine(Intermediate, "UnrealCSharp_Modules.json");

		if (!Directory.Exists(Intermediate))
		{
			Directory.CreateDirectory(Intermediate);
		}

		var ProjectPlugins = new Dictionary<string, string>();

		GetModules(Path.GetFullPath(Path.Combine(ProjectPath, "Plugins/")), ProjectPlugins);

		GetPlugins(Path.GetFullPath(Path.Combine(ProjectPath, "Plugins/")), ProjectPlugins);

		var EngineModules = new Dictionary<string, string>();

		GetModules(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Developer/")), EngineModules);

		GetModules(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Editor/")), EngineModules);

		GetModules(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Programs/")), EngineModules);

		GetModules(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Runtime/")), EngineModules);

		var EnginePlugins = new Dictionary<string, string>();

		GetModules(Path.GetFullPath(Path.Combine(EngineDirectory, "Plugins/")), EnginePlugins);

		GetPlugins(Path.GetFullPath(Path.Combine(EngineDirectory, "Plugins/")), EnginePlugins);

		using var Writer = new JsonWriter(JsonFullFilename);

		Writer.WriteObjectStart();

		Writer.WriteObjectStart("ProjectModules");

		foreach (var Item in Target.ExtraModuleNames)
		{
			Writer.WriteValue(Item, Path.Join(Target.ProjectFile.Directory.FullName, "Source", Item));
		}

		Writer.WriteObjectEnd();

		Writer.WriteObjectStart("ProjectPlugins");

		foreach (var Item in ProjectPlugins)
		{
			Writer.WriteValue(Item.Key, Item.Value);
		}

		Writer.WriteObjectEnd();

		Writer.WriteObjectStart("EngineModules");

		foreach (var Item in EngineModules)
		{
			Writer.WriteValue(Item.Key, Item.Value);
		}

		Writer.WriteObjectEnd();

		Writer.WriteObjectStart("EnginePlugins");

		foreach (var Item in EnginePlugins)
		{
			Writer.WriteValue(Item.Key, Item.Value);
		}

		Writer.WriteObjectEnd();

		Writer.WriteObjectEnd();
	}

	private void GetPlugins(string InPathName, Dictionary<string, string> Plugins)
	{
		var Suffix = "*.uplugin";

		var DirectoryInfo = new DirectoryInfo(InPathName);

		foreach (var Item in DirectoryInfo.GetFiles(Suffix))
		{
			Plugins[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
		}

		foreach (var Directories in DirectoryInfo.GetDirectories())
		{
			foreach (var Item in Directories.GetFiles(Suffix, SearchOption.AllDirectories))
			{
				Plugins[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
			}
		}
	}

	private void GetModules(string InPathName, Dictionary<string, string> Modules)
	{
		var Suffix = "*.Build.cs";

		var DirectoryInfo = new DirectoryInfo(InPathName);

		foreach (var Item in DirectoryInfo.GetFiles(Suffix))
		{
			Modules[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
		}

		foreach (var Directories in DirectoryInfo.GetDirectories())
		{
			foreach (var Item in Directories.GetFiles(Suffix, SearchOption.AllDirectories))
			{
				Modules[Item.Name.Remove(Item.Name.Length - Suffix.Length + 1)] = Item.DirectoryName;
			}
		}
	}
}