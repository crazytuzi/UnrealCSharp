using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using EpicGames.Core;
using UnrealBuildTool;
using Console = Internal.Console;

public class Mono : ModuleRules
{
	private MonoConfig _MonoConfig;
	private string SharedLibrary;
	private string[] StaticLibraries;
	private string IncludeDirectory;
	private string PdbFile;
	public Mono(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		_MonoConfig = GetConfig();
		var MethodNameTemplate = "BuildFor{0}";
		if (_MonoConfig.BuildFromSource == true)
		{
			MethodNameTemplate = "BuildFor{0}WithSource";
			if (CheckSourcePath(_MonoConfig.DotNetRuntimeSourcePath) == false)
			{
				throw new Exception("mono runtime source path error");
			}
		}
		
		var MethodName = string.Format(MethodNameTemplate, Target.Platform.ToString());
		Console.WriteLine("\n build from: " + MethodName);
		var BuildMethod = GetType().GetMethod(MethodName, BindingFlags.Instance | BindingFlags.NonPublic);
		if (BuildMethod == null)
			throw new NotSupportedException(MethodName);
		BuildMethod.Invoke(this, new Object[]{});
	}

	private void BuildForWin64()
	{
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src"));
		var LibraryPath = Path.Combine(ModuleDirectory, "lib");
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

		var Files = GetFiles(Path.Combine(LibraryPath, "net7.0"));

		foreach (var File in Files)
		{
			var ModuleLastDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, ".."));

			var DestPath = File.Substring(ModuleLastDirectory.Length + 1,
				File.Length - ModuleLastDirectory.Length - 1);

			RuntimeDependencies.Add("$(BinaryOutputDir)/" + DestPath, File);
		}
	}


	private void BuildForWin64WithSource()
	{
		var Configuration = "Release";
		if (IsDebug() == true)
		{
			Configuration = "Debug";
		}
		
		SharedLibrary = $"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\bin\\coreclr.dll";
		StaticLibraries = new []
		{
			$"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\coreclr.import.lib",
			$"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-component-debugger-static.lib",
			$"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-component-diagnostics_tracing-static.lib",
			$"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-component-hot_reload-static.lib",
			$"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\mono-profiler-aot.lib",
			$"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\lib\\monosgen-2.0.lib",
		};
		IncludeDirectory = $"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\include\\mono-2.0";
		PdbFile = $"{_MonoConfig.DotNetRuntimeSourcePath}\\artifacts\\obj\\mono\\windows.x64.{Configuration}\\out\\bin\\mono-sgen.pdb";
		if (CheckMonoSouceCompiled() == false)
		{
			Console.WriteLine("Compile Mono from source code!");
			ComplieMono();
		}
		CopyDependencies();
	}

	private void CopyDependencies()
	{
		
		PublicIncludePaths.Add(IncludeDirectory);
		RuntimeDependencies.Add("$(BinaryOutputDir)/coreclr.dll", SharedLibrary);
		foreach (var StaticLibrary in StaticLibraries)
		{
			PublicAdditionalLibraries.Add(StaticLibrary);
		}

		if (IsDebug() == true)
		{
			RuntimeDependencies.Add("$(BinaryOutputDir)/mono-sgen.pdb", PdbFile);
		}
		
		
		var LibraryPath = Path.Combine(ModuleDirectory, "lib");
		var Files = GetFiles(Path.Combine(LibraryPath, "net7.0"));

		foreach (var File in Files)
		{
			var ModuleLastDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, ".."));

			var DestPath = File.Substring(ModuleLastDirectory.Length + 1,
				File.Length - ModuleLastDirectory.Length - 1);

			RuntimeDependencies.Add("$(BinaryOutputDir)/" + DestPath, File);
		}
	}

	private void ComplieMono()
	{
		var complieCmd = "./build.cmd mono -os windows -arch x64 ";
		if (IsDebug() == true)
		{
			complieCmd += "-c debug";
		}
		else
		{
			complieCmd += "-c release";
		}
		Console.WriteLine("build mono cmd: " + complieCmd);
		var startInfo = new ProcessStartInfo
		{
			FileName = "powershell.exe",
			WorkingDirectory = _MonoConfig.DotNetRuntimeSourcePath,
			UseShellExecute = false,
			Arguments = complieCmd,
			RedirectStandardOutput = true,
			StandardOutputEncoding = Encoding.UTF8
		};
		var process = new Process();
		process.StartInfo = startInfo;
		string OutPut = "";
		process.OutputDataReceived += (sender, e) =>
		{
			if (e.Data != null)
			{
				OutPut += (e.Data + "\n");
			}
		};
		
		process.Start();
		process.BeginOutputReadLine();
		process.WaitForExit();
		process.Close();
		string LogDir = Target.ProjectFile.Directory + "/Saved/Logs";
		string LogFile = LogDir + "/MonoBuildLog-" + DateTime.Now.ToString("yyyy.MM.dd-HH.mm.ss") + ".log";
		if (Directory.Exists(LogDir) == false)
		{
			Directory.CreateDirectory(LogDir);
		}
		using (StreamWriter sr = new StreamWriter(LogFile)) 
		{
			sr.Write(OutPut);
		}

		if (OutPut.IndexOf("Build failed with exit code") > 0)
		{
			throw new Exception("Build Mono failed, please to see log: " + LogFile);
		}
		

	}
	private bool CheckMonoSouceCompiled()
	{
		if (File.Exists(SharedLibrary) == false)
		{
			Console.WriteLine("File is not Exits:" + SharedLibrary);
			return false;
		}
		foreach (var path in StaticLibraries)
		{
			if (File.Exists(path) == false)
			{
				Console.WriteLine("File is not Exits:" + path);
				return false;
			}
		}

		if (Directory.Exists(IncludeDirectory) == false)
		{
			Console.WriteLine("File is not Exits:" + IncludeDirectory);
			return false;
		}

		if (IsDebug())
		{
			if (File.Exists(PdbFile) == false)
			{
				Console.WriteLine("File is not Exits:" + PdbFile);
				return false;
			}
		}
		return true;
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

	public MonoConfig GetConfig()
	{
		
		var configFilePath = PluginDirectory + "/Config/UnrealCSharp.ini";
		var configFileReference = new FileReference(configFilePath);
		var configFile = FileReference.Exists(configFileReference)
			? new ConfigFile(configFileReference)
			: new ConfigFile();
        var config = new ConfigHierarchy(new[] { configFile });
		
        const string section = "BuildSettings";

        var monoConfig = new MonoConfig();
        if (config.GetBool(section, "BuildFromSource", out monoConfig.BuildFromSource) == true)
        {
	        config.GetString(section, "DotNetRuntimeSourcePath", out monoConfig.DotNetRuntimeSourcePath);
        }
		
        return monoConfig;
	}

	public bool CheckSourcePath(string Path)
	{
		if (File.Exists($"{_MonoConfig.DotNetRuntimeSourcePath}//build.cmd") == true)
			return true;
		return false;
	}
	
	private bool IsDebug()
	{
		return Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.DebugGame || Target.Configuration == UnrealTargetConfiguration.Development;
	}
}

public class MonoConfig
{
	public bool BuildFromSource;
	public string DotNetRuntimeSourcePath;
}