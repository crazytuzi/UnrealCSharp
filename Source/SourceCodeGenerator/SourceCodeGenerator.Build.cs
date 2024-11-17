using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class SourceCodeGenerator : ModuleRules
	{
		public SourceCodeGenerator(ReadOnlyTargetRules Target) : base(Target)
		{
#if UE_5_2_OR_LATER
			IWYUSupport = IWYUSupport.None;
#else
			bEnforceIWYU = false;
#endif

			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicIncludePaths.AddRange(
				new string[]
				{
					"Programs/UnrealHeaderTool/Public",
				}
			);


			PrivateIncludePaths.AddRange(
				new string[]
				{
					"SourceCodeGenerator/Private",
				}
			);


			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
				}
			);

			PublicDefinitions.Add("HACK_HEADER_GENERATOR=1");
		}
	}
}