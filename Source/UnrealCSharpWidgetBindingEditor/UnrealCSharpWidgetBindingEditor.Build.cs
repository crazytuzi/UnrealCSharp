using UnrealBuildTool;

public class UnrealCSharpWidgetBindingEditor : ModuleRules
{
    public UnrealCSharpWidgetBindingEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "UMG", "UMGEditor",
            "UnrealCSharpBlueprintFunction"]);

        PrivateDependencyModuleNames.AddRange([
            "UnrealEd", "KismetCompiler", "PropertyEditor", "Slate", "SlateCore",
            "UnrealCSharpBlueprintFunctionEditor", "UnrealCSharpCore"
        ]);
    }
}
