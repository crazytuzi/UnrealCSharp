using UnrealBuildTool;

public class UnrealCSharpBlueprintFunctionEditor : ModuleRules
{
    public UnrealCSharpBlueprintFunctionEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "BlueprintGraph",
            "UnrealCSharpBlueprintFunction"]);

        PrivateDependencyModuleNames.AddRange([
            "UnrealEd", "KismetCompiler", "GraphEditor", "Slate", "SlateCore",
            "UnrealCSharp", "UnrealCSharpCore"
        ]);
    }
}
