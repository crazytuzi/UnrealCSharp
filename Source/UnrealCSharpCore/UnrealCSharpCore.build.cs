// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using EpicGames.Core;
using UnrealBuildTool;

public class UnrealCSharpCore : ModuleRules
{
	public UnrealCSharpCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
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
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Json"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		var ProjectDir = Path.GetDirectoryName(Target.ProjectFile?.FullName);
		
		var Intermediate = Path.Combine(ProjectDir, "Intermediate");

		var JsonFullFilename = Path.Combine(Intermediate, "UnrealCSharp_GameModules.json");
		
		if (!Directory.Exists(Intermediate))
		{
			Directory.CreateDirectory(Intermediate);
		}

		Console.WriteLine("UnrealCSharp :Write json to: " + JsonFullFilename);
		
		using (var Writer = new JsonWriter(JsonFullFilename))
		{
			Writer.WriteObjectStart();
			Writer.WriteStringArrayField("GameModules", Target.ExtraModuleNames);
			Writer.WriteObjectEnd();
		}

	}
}
