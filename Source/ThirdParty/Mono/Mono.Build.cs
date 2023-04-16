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
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, Target.Platform.ToString(), "mono-2.0-sgen.lib"));

			RuntimeDependencies.Add("$(BinaryOutputDir)/mono-2.0-sgen.dll",
				Path.Combine(LibraryPath, Target.Platform.ToString(), "mono-2.0-sgen.dll"));

			var Files = GetFiles(Path.Combine(LibraryPath, "mono"))
				.Union(GetFiles(Path.Combine(ModuleDirectory, "etc")));

			foreach (var File in Files)
			{
				var ModuleLastDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, ".."));

				var DestPath = File.Substring(ModuleLastDirectory.Length + 1,
					File.Length - ModuleLastDirectory.Length - 1);

				RuntimeDependencies.Add("$(BinaryOutputDir)/" + DestPath, File);
			}
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