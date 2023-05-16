// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
#if UE_5_0_OR_LATER
using EpicGames.Core;
#else
using Tools.DotNETCommon;
#endif
using UnrealBuildTool;
using System.Collections.Generic;
using System.Linq;

public class UnrealCSharpCore : ModuleRules
{
	public UnrealCSharpCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableUndefinedIdentifierWarnings = false;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
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
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

#if UE_5_0_OR_LATER
		var ProjectPath = Path.GetDirectoryName(Target.ProjectFile?.FullName);
#else
		var ProjectPath = Path.GetDirectoryName(Target.ProjectFile.FullName);

		if (ProjectPath == null) return;
#endif
		var Intermediate = Path.Combine(ProjectPath, "Intermediate");

		var JsonFullFilename = Path.Combine(Intermediate, "UnrealCSharp_GameModules.json");

		if (!Directory.Exists(Intermediate))
		{
			Directory.CreateDirectory(Intermediate);
		}

		var GameModules = new List<string>();

		var ProjectPlugins =
			Plugins.ReadProjectPlugins(
				new DirectoryReference(Path.GetFullPath(Path.Combine(PluginDirectory, "../../"))));

		foreach (var ProjectPlugin in ProjectPlugins)
		{
			GameModules.Add(ProjectPlugin.Name);
		}

		using (var Writer = new JsonWriter(JsonFullFilename))
		{
			Writer.WriteObjectStart();

			Writer.WriteStringArrayField("GameModules", GameModules.Union(Target.ExtraModuleNames));

			Writer.WriteObjectEnd();
		}
	}
}
