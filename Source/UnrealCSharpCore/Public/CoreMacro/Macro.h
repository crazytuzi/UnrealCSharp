#pragma once

#define PLUGIN_NAME FString(TEXT("UnrealCSharp"))

#define PLUGIN_SCRIPT_PATH FString(TEXT("Script"))

#define PLUGIN_TEMPLATE_PATH FString(TEXT("Template"))

#define SOLUTION_NAME FString(TEXT("Script"))

#define DEFAULT_UE_NAME FString(TEXT("UE"))

#define DEFAULT_GAME_NAME FString(TEXT("Game"))

#define DEFAULT_OVERRIDE_FUNCTION_NAME_PREFIX FString(TEXT(""))

#define DEFAULT_OVERRIDE_FUNCTION_NAME_SUFFIX FString(TEXT("_Override"))

#define CODE_ANALYSIS_NAME FString(TEXT("CodeAnalysis"))

#define SOURCE_GENERATOR_NAME FString(TEXT("SourceGenerator"))

#define WEAVERS_NAME FString(TEXT("Weavers"))

#define UNREAL_TYPE_SOURCE_GENERATOR_NAME FString(TEXT("UnrealTypeSourceGenerator"))

#define ANALYZER_RELEASES_UN_SHIPPED_NAME FString(TEXT("AnalyzerReleases.Unshipped"))

#define UNREAL_TYPE_WEAVER_NAME FString(TEXT("UnrealTypeWeaver"))

#define FODY_WEAVERS_NAME FString(TEXT("FodyWeavers"))

#define PROXY_NAME FString(TEXT("Proxy"))

#define BINDING_NAME FString(TEXT("Binding"))

#define CSHARP_GUID FString(TEXT("9A19103F-16F7-4668-BE54-9A1E7A4F7556"))

#define PROJECT_PLACEHOLDER FString(TEXT("ProjectPlaceholder"))

#define SOLUTION_CONFIGURATION_PLATFORMS_PLACEHOLDER FString(TEXT("SolutionConfigurationPlatformsPlaceholder"))

#define PROJECT_SUFFIX FString(TEXT(".csproj"))

#define PROJECT_PROPS_SUFFIX FString(TEXT(".csproj.props"))

#define SOLUTION_SUFFIX FString(TEXT(".sln"))

#define DLL_SUFFIX FString(TEXT(".dll"))

#define CSHARP_SUFFIX FString(TEXT(".cs"))

#define MARKDOWN_SUFFIX FString(TEXT(".md"))

#define XML_SUFFIX FString(TEXT(".xml"))

#define DEFAULT_PUBLISH_DIRECTORY FString(TEXT("Script"))

#define DEFAULT_SCRIPT_DIRECTORY FString(TEXT("Script"))

#define OVERRIDE_FUNCTION FString(TEXT("OverrideFunction"))

#define OVERRIDE_FILE FString(TEXT("OverrideFile"))

#define DYNAMIC FString(TEXT("Dynamic"))

#define DYNAMIC_FILE FString(TEXT("DynamicFile"))

#define ACTOR_PREFIX AActor::StaticClass()->GetPrefixCPP()

#define OBJECT_PREFIX UObject::StaticClass()->GetPrefixCPP()

#define INTERFACE_PREFIX UInterface::StaticClass()->GetPrefixCPP()

#define STRUCT_PREFIX TBaseStructure<FVector>::Get()->GetPrefixCPP()

#define PLACEHOLDER _
