using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnrealBuildTool;

public class Mono : ModuleRules
{
	public Mono(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src"));

		var LibraryPath = Path.Combine(ModuleDirectory, "lib");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
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

			var Files = GetFiles(Path.Combine(LibraryPath, Target.Platform.ToString(), "net7.0"));

			foreach (var File in Files)
			{
				var ModuleLastDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, ".."));

				var DestPath = File.Substring(ModuleLastDirectory.Length + 1,
					File.Length - ModuleLastDirectory.Length - 1);

				RuntimeDependencies.Add("$(BinaryOutputDir)/" + DestPath, File);
			}
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(), "libmonosgen-2.0.a"));

			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(),
				"libmono-component-debugger-static.a"));

			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(),
				"libmono-component-diagnostics_tracing-static.a"));

			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(),
				"libmono-component-hot_reload-static.a"));

			// PublicAdditionalLibraries.Add(
			// 	Path.Combine(LibraryPath, Target.Platform.ToString(), "mono-profiler-aot.lib"));

			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(), "libmonosgen-2.0.a"));

			RuntimeDependencies.Add("$(BinaryOutputDir)/libmonosgen-2.0.so",
				Path.Combine(LibraryPath, Target.Platform.ToString(), "libmonosgen-2.0.so"));

			// RuntimeDependencies.Add("$(BinaryOutputDir)/mono-sgen.pdb",
			// 	Path.Combine(LibraryPath, Target.Platform.ToString(), "mono-sgen.pdb"));

			var Files = GetFiles(Path.Combine(LibraryPath, Target.Platform.ToString(), "net7.0"));

			foreach (var File in Files)
			{
				var ModuleLastDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, ".."));

				var DestPath = File.Substring(ModuleLastDirectory.Length + 1,
					File.Length - ModuleLastDirectory.Length - 1);

				RuntimeDependencies.Add("$(BinaryOutputDir)/" + DestPath, File);
			}

			string APLName = "Mono_APL.xml";

			string RelativeAPLPath = Utils.MakePathRelativeTo(Path.Combine(ModuleDirectory, "lib", "Android"),
				Target.RelativeEnginePath);

			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(RelativeAPLPath, APLName));
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
}