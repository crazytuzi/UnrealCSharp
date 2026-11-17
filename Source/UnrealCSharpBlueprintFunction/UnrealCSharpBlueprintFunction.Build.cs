using UnrealBuildTool;

public class UnrealCSharpBlueprintFunction : ModuleRules
{
    public UnrealCSharpBlueprintFunction(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "UMG", "UnrealCSharpCore"]);

        PrivateDependencyModuleNames.AddRange(["UnrealCSharp"]);
    }
}
