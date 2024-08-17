#include "FSolutionGenerator.h"
#include "CoreMacro/Macro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Misc/FileHelper.h"

void FSolutionGenerator::Generator()
{
	const auto TemplatePath = FUnrealCSharpFunctionLibrary::GetPluginDirectory() / PLUGIN_TEMPLATE_PATH;

	const auto ScriptPath = FUnrealCSharpFunctionLibrary::GetPluginDirectory() / PLUGIN_SCRIPT_PATH;

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetCodeAnalysisProjectPath(),
		ScriptPath / CODE_ANALYSIS_NAME / CODE_ANALYSIS_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceTargetFramework
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(), CODE_ANALYSIS_NAME + CSHARP_SUFFIX),
		ScriptPath / CODE_ANALYSIS_NAME / CODE_ANALYSIS_NAME + CSHARP_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath(), SOURCE_GENERATOR_NAME + PROJECT_SUFFIX),
		ScriptPath / SOURCE_GENERATOR_NAME / SOURCE_GENERATOR_NAME + PROJECT_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath(),
		                UNREAL_TYPE_SOURCE_GENERATOR_NAME + CSHARP_SUFFIX),
		ScriptPath / SOURCE_GENERATOR_NAME / UNREAL_TYPE_SOURCE_GENERATOR_NAME + CSHARP_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath(),
		                ANALYZER_RELEASES_UN_SHIPPED_NAME + MARKDOWN_SUFFIX),
		ScriptPath / SOURCE_GENERATOR_NAME / ANALYZER_RELEASES_UN_SHIPPED_NAME + MARKDOWN_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetWeaversPath(), WEAVERS_NAME + PROJECT_SUFFIX),
		ScriptPath / WEAVERS_NAME / WEAVERS_NAME + PROJECT_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetWeaversPath(), UNREAL_TYPE_WEAVER_NAME + CSHARP_SUFFIX),
		ScriptPath / WEAVERS_NAME / UNREAL_TYPE_WEAVER_NAME + CSHARP_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceYield,
			&FSolutionGenerator::ReplaceDefinition
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGameDirectory() / FODY_WEAVERS_NAME + XML_SUFFIX),
		ScriptPath / WEAVERS_NAME / FODY_WEAVERS_NAME + XML_SUFFIX);

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetUEProjectPath(),
		TemplatePath / DEFAULT_UE_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplacePluginBaseDir,
			&FSolutionGenerator::ReplaceDefineConstants,
			&FSolutionGenerator::ReplaceOutputPath,
			&FSolutionGenerator::ReplaceTargetFramework
		});

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetGameProjectPath(),
		TemplatePath / DEFAULT_GAME_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceImport,
			&FSolutionGenerator::ReplaceDefineConstants,
			&FSolutionGenerator::ReplaceOutputPath,
			&FSolutionGenerator::ReplaceTargetFramework,
			&FSolutionGenerator::ReplaceProjectReference
		});

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetGameProjectPropsPath(),
		TemplatePath / DEFAULT_GAME_NAME + PROJECT_PROPS_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetFullScriptDirectory(),
		                FUnrealCSharpFunctionLibrary::GetScriptDirectory() + SOLUTION_SUFFIX),
		TemplatePath / SOLUTION_NAME + SOLUTION_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceProject
		});
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src)
{
	if (auto& FileManager = IFileManager::Get(); !FileManager.FileExists(*Dest))
	{
		FileManager.Copy(*Dest, *Src);
	}
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src,
                                      const TArray<TFunction<void(FString& OutResult)>>& InFunction)
{
	FString Result;

	FFileHelper::LoadFileToString(Result, *Src);

	for (const auto& Function : InFunction)
	{
		Function(Result);
	}

	auto& FileManager = IFileManager::Get();

	FFileHelper::SaveStringToFile(Result, *Dest, FFileHelper::EEncodingOptions::ForceUTF8, &FileManager);
}

void FSolutionGenerator::ReplacePluginBaseDir(FString& OutResult)
{
	auto Index = 0;

	const auto PluginBaseDir = FUnrealCSharpFunctionLibrary::GetPluginBaseDir();

	PluginBaseDir.FindLastChar('/', Index);

	OutResult = OutResult.Replace(*PLUGIN_NAME, *PluginBaseDir.Right(PluginBaseDir.Len() - Index - 1));
}

void FSolutionGenerator::ReplaceImport(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("<Import Project=\"\" Condition=\"Exists(\'\')\" />"),
	                              *FString::Printf(TEXT(
		                              "<Import Project=\"%s%s\" Condition=\"Exists(\'%s%s\')\" />"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetGameName(),
	                                               *PROJECT_PROPS_SUFFIX,
	                                               *FUnrealCSharpFunctionLibrary::GetGameName(),
	                                               *PROJECT_PROPS_SUFFIX
	                              ));
}

void FSolutionGenerator::ReplaceDefineConstants(FString& OutResult)
{
	FString DefineConstants;

	for (auto MajorVersion = 5; MajorVersion <= ENGINE_MAJOR_VERSION; ++MajorVersion)
	{
		for (auto MinorVersion = 0; MinorVersion <= ENGINE_MINOR_VERSION; ++MinorVersion)
		{
			DefineConstants += FString::Printf(TEXT(
				"UE_%d_%d_OR_LATER;"
			),
			                                   MajorVersion,
			                                   MinorVersion
			);
		}
	}

	if (!IsRunningCookCommandlet())
	{
		DefineConstants += TEXT("WITH_EDITOR");
	}

	DefineConstants = FString::Printf(TEXT(
		"<DefineConstants>$(DefineConstants);%s</DefineConstants>"
	),
	                                  *DefineConstants
	);

	OutResult = OutResult.Replace(TEXT("<DefineConstants></DefineConstants>"), *DefineConstants);
}

void FSolutionGenerator::ReplaceOutputPath(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("<OutputPath></OutputPath>"),
	                              *FString::Printf(TEXT(
		                              "<OutputPath>..\\..\\Content\\%s</OutputPath>"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetPublishDirectory()
	                              ));
}

void FSolutionGenerator::ReplaceTargetFramework(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("<TargetFramework></TargetFramework>"),
	                              *FString::Printf(TEXT(
		                              "<TargetFramework>net%d.%d</TargetFramework>"
	                              ),
	                                               DOTNET_MAJOR_VERSION,
	                                               DOTNET_MINOR_VERSION
	                              )
	);
}

void FSolutionGenerator::ReplaceProjectReference(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("<ProjectReference Include=\"\" />"),
	                              *FString::Printf(TEXT(
		                              "<ProjectReference Include=\"..\\%s\\%s%s\" />"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetUEName(),
	                                               *FUnrealCSharpFunctionLibrary::GetUEName(),
	                                               *PROJECT_SUFFIX

	                              ));
}

void FSolutionGenerator::ReplaceYield(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("yield return \"\";"),
	                              *FString::Printf(TEXT(
		                              "yield return \"%s\";\r\n"
		                              "\r\n"
		                              "\t\t\tyield return \"%s\";"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetUEName(),
	                                               *FUnrealCSharpFunctionLibrary::GetGameName()
	                              ));
}

void FSolutionGenerator::ReplaceDefinition(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("if (definition.Name != \"\")"),
	                              *FString::Printf(TEXT(
		                              "if (definition.Name != \"%s%s\")"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetUEName(),
	                                               *DLL_SUFFIX
	                              ));

	OutResult = OutResult.Replace(TEXT("definition = ModuleDefinition.ReadModule(\"\");"),
	                              *FString::Printf(TEXT(
		                              "definition = ModuleDefinition.ReadModule(\"../../Content/%s/%s%s\");"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetPublishDirectory(),
	                                               *FUnrealCSharpFunctionLibrary::GetUEName(),
	                                               *DLL_SUFFIX
	                              ));
}

void FSolutionGenerator::ReplaceProject(FString& OutResult)
{
	OutResult = OutResult.Replace(
		TEXT(
			"Project(\"{9A19103F-16F7-4668-BE54-9A1E7A4F7556}\") = \"\", \"\", \"{7AF881DC-664B-4AF7-BCB6-8FA8CC5E8780}\""),
		*FString::Printf(TEXT(
			"Project(\"{9A19103F-16F7-4668-BE54-9A1E7A4F7556}\") = \"%s\", \"%s\\%s%s\", \"{7AF881DC-664B-4AF7-BCB6-8FA8CC5E8780}\""
		),
		                 *FUnrealCSharpFunctionLibrary::GetUEName(),
		                 *FUnrealCSharpFunctionLibrary::GetUEName(),
		                 *FUnrealCSharpFunctionLibrary::GetUEName(),
		                 *PROJECT_SUFFIX
		));

	OutResult = OutResult.Replace(
		TEXT(
			"Project(\"{9A19103F-16F7-4668-BE54-9A1E7A4F7556}\") = \"\", \"\", \"{A2B210E9-51AE-490B-8B87-F8492CB2A417}\""),
		*FString::Printf(TEXT(
			"Project(\"{9A19103F-16F7-4668-BE54-9A1E7A4F7556}\") = \"%s\", \"%s\\%s%s\", \"{A2B210E9-51AE-490B-8B87-F8492CB2A417}\""
		),
		                 *FUnrealCSharpFunctionLibrary::GetGameName(),
		                 *FUnrealCSharpFunctionLibrary::GetGameName(),
		                 *FUnrealCSharpFunctionLibrary::GetGameName(),
		                 *PROJECT_SUFFIX
		));
}
