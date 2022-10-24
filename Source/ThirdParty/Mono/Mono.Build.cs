using System.IO;
using UnrealBuildTool;

public class Mono : ModuleRules
{
    public Mono(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            var LibPath = Path.Combine(ModuleDirectory, "lib/Win64/mono-2.0-sgen.lib");

            PublicSystemLibraryPaths.Add(Path.GetDirectoryName(LibPath));

            PublicAdditionalLibraries.Add("mono-2.0-sgen.lib");
        }
    }
}
