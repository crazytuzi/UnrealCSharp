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

		GenEngineModuleFile();
	}

	private void GenEngineModuleFile()
	{
#if UE_5_0_OR_LATER
		var ProjectPath = Path.GetDirectoryName(Target.ProjectFile?.FullName);
#else
		var ProjectPath = Path.GetDirectoryName(Target.ProjectFile.FullName);

		if (ProjectPath == null) return;
#endif
		var Intermediate = Path.Combine(ProjectPath, "Intermediate");

		var JsonFullFilename = Path.Combine(Intermediate, "UnrealCSharp_Engine_GameModules.json");

		if (!Directory.Exists(Intermediate)) Directory.CreateDirectory(Intermediate);

		var GameModules = new List<string>();

		Console.WriteLine("GetEngineModule EngineDirectory: " + EngineDirectory);


		var ProjectPlugins =
			Plugins.ReadEnginePlugins(
				new DirectoryReference(Path.GetFullPath(EngineDirectory)));

		var GameCoreModules = new List<string>();
		GetAllBuildModule(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Developer/"))),
			GameCoreModules);
		GetAllBuildModule(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Editor/"))),
			GameCoreModules);
		GetAllBuildModule(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Programs/"))),
			GameCoreModules);
		GetAllBuildModule(Path.GetFullPath(Path.GetFullPath(Path.Combine(EngineDirectory, "Source/Runtime/"))),
			GameCoreModules);

		foreach (var ProjectPlugin in ProjectPlugins)
		{
			GameModules.Add(ProjectPlugin.Name);
		}

		using (var Writer = new JsonWriter(JsonFullFilename))
		{
			Writer.WriteObjectStart();

			Writer.WriteStringArrayField("GameModules", GameModules.Union(Target.ExtraModuleNames));

			Writer.WriteStringArrayField("GameCoreModules", GameCoreModules);

			Writer.WriteObjectEnd();
		}
	}

	private void GetAllBuildModule(string dir, List<string> ModulesList)
	{
		var DirectoryInfoObj = new DirectoryInfo(dir);
		var FileList = DirectoryInfoObj.GetFiles(); //文件
		var DirectoryList = DirectoryInfoObj.GetDirectories(); //文件夹
		var CheckFileExt = ".Build.cs";
		foreach (var FileInfo in FileList)
		{
			if (FileInfo.Name.EndsWith(CheckFileExt))
			{
				ModulesList.Add(FileInfo.Name.Remove(FileInfo.Name.Length - CheckFileExt.Length));
				return;
			}
		}

		//获取子文件夹内的文件列表，递归遍历  
		foreach (var dd in DirectoryList)
		{
			GetAllBuildModule(dd.FullName, ModulesList);
		}
	}
}