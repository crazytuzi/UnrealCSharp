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

		bEnableUndefinedIdentifierWarnings = false;

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
				"CrossVersion"
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

		var ProjectPlugins = new HashSet<string>();

		GetModules(Path.GetFullPath(Path.GetFullPath(Path.Combine(ProjectPath, "Plugins/"))), ProjectPlugins);

		var EngineModules = new HashSet<string>();

		GetModules(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Developer/"))),
			EngineModules);

		GetModules(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Editor/"))), EngineModules);

		GetModules(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Programs/"))),
			EngineModules);

		GetModules(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Runtime/"))), EngineModules);

		var EnginePlugins = new HashSet<string>();

		GetModules(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Plugins/"))), EnginePlugins);

		using var Writer = new JsonWriter(JsonFullFilename);

		Writer.WriteObjectStart();

		Writer.WriteStringArrayField("ProjectModules", Target.ExtraModuleNames);

		Writer.WriteStringArrayField("ProjectPlugins", ProjectPlugins);

		Writer.WriteStringArrayField("EngineModules", EngineModules);

		Writer.WriteStringArrayField("EnginePlugins", EnginePlugins);

		Writer.WriteObjectEnd();
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
				Modules.Add(Item.Name.Remove(Item.Name.Length - Suffix.Length + 1));
			}
		}
	}
}