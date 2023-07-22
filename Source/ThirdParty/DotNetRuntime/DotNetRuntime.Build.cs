using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using UnrealBuildTool;

public class DotNetRuntime : ModuleRules
{
	string LibraryPath;

	private Dictionary<(UnrealTargetPlatform, bool IsBuildFromSource), Action> BuildFuncDictionary;

	public DotNetRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		InitBuildFuncDictionary();
		Type = ModuleType.External;
		LibraryPath = Path.Combine(ModuleDirectory, "lib");
		bool IsBuildFromSource = true;
        if (BuildFuncDictionary.TryGetValue((Target.Platform, IsBuildFromSource), out var BuildFunction))
		{
			BuildFunction?.Invoke();
		}
		else if (BuildFuncDictionary.TryGetValue((Target.Platform, !IsBuildFromSource), out BuildFunction))
		{
			BuildFunction?.Invoke();
		}
		else
		{
			throw new NotSupportedException();
		}


    }

	private void InitBuildFuncDictionary()
	{
		BuildFuncDictionary = new Dictionary<(UnrealTargetPlatform, bool IsBuildFromSource), Action>()
		{
			{ (UnrealTargetPlatform.Win64, false), CopyMonoDependenciesForWin64},
			{ (UnrealTargetPlatform.Win64, true), BuildMonoForWin64}
		};
	}

	public void CopyMonoDependenciesForWin64()
	{
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src"));

		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(), "coreclr.import.lib"));

		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(),
			"mono-component-debugger-static.lib"));

		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(),
			"mono-component-diagnostics_tracing-static.lib"));

		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(),
			"mono-component-hot_reload-static.lib"));

		PublicAdditionalLibraries.Add(
			Path.Combine(LibraryPath, Target.Platform.ToString(), "mono-profiler-aot.lib"));

		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(), "monosgen-2.0.lib"));

		RuntimeDependencies.Add("$(BinaryOutputDir)/coreclr.dll",
			Path.Combine(LibraryPath, Target.Platform.ToString(), "coreclr.dll"));

		RuntimeDependencies.Add("$(BinaryOutputDir)/mono-sgen.pdb",
			Path.Combine(LibraryPath, Target.Platform.ToString(), "mono-sgen.pdb"));

		CopyMonoLibrariesForWin64();

    }


	private void CopyMonoLibrariesForWin64()
	{
		var Files = GetFiles(Path.Combine(Path.Combine(LibraryPath, Target.Platform.ToString()), "net7.0"));

		foreach (var File in Files)
		{
			var ModuleLastDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, ".."));
			var fileInfo = new FileInfo(File);
			
			
			RuntimeDependencies.Add("$(BinaryOutputDir)/net7.0/" + fileInfo.Name, File);
		}
	}

	private static IEnumerable<string> GetFiles(string InDirectory, string InPattern = "*.*")
	{
		var Files = new List<string>();

		var Strings = Directory.GetFiles(InDirectory, InPattern);

		foreach (var File in Strings)
		{
			Files.Add(File);
		}

		foreach (var File in Directory.GetDirectories(InDirectory))
		{
			Files.AddRange(GetFiles(File, InPattern));
		}

		return Files;
	}
	private void BuildMonoForWin64()
	{
		var complieCmd = "./build.cmd mono -arch x64 ";
		var Configuration = "Release";
		if (IsDebug() == true)
		{
			complieCmd += "-c debug";
			Configuration = "Debug";
		}
		else
		{
			complieCmd += "-c release";
			Configuration = "Release";
		}

		Console.WriteLine("build mono cmd: " + complieCmd);
        var startInfo = new ProcessStartInfo
		{
			FileName = "powershell.exe",
			WorkingDirectory = ModuleDirectory + "/src/runtime",
			UseShellExecute = false,
			Arguments = complieCmd,
		};
		var process = new Process();
		process.StartInfo = startInfo;
		process.Start();
		process.WaitForExit();
		process.Close();
		
		
		
		// 头文件
		PublicIncludePaths.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\include\\mono-2.0");
			
		// 静态库
		PublicAdditionalLibraries.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\coreclr.import.lib");
		PublicAdditionalLibraries.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-component-debugger-static.lib");
		PublicAdditionalLibraries.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-component-diagnostics_tracing-static.lib");
		PublicAdditionalLibraries.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-component-hot_reload-static.lib");
		PublicAdditionalLibraries.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-profiler-aot.lib");
		PublicAdditionalLibraries.Add($"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\monosgen-2.0.lib");

		// 动态库
		RuntimeDependencies.Add("$(BinaryOutputDir)/coreclr.dll", $"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\bin\\coreclr.dll");

		// 调试符号
		if (IsDebug() == true)
		{
			RuntimeDependencies.Add("$(BinaryOutputDir)/mono-sgen.pdb", $"{ModuleDirectory}\\src\\runtime\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\bin\\mono-sgen.pdb");
		}
		
		CopyMonoLibrariesForWin64();
	}
	

	private bool IsDebug()
	{
		return Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.DebugGame || Target.Configuration == UnrealTargetConfiguration.Development;
	}
}