#include "FSolutionGenerator.h"
#include "Misc/FileHelper.h"
#include "CoreMacro/Macro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"
#include "FGeneratorCore.h"

void FSolutionGenerator::Generator()
{
	const auto TemplatePath = FUnrealCSharpFunctionLibrary::GetPluginTemplateDirectory();

	const auto ScriptPath = FUnrealCSharpFunctionLibrary::GetPluginScriptDirectory();

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetCodeAnalysisProjectPath(),
		ScriptPath / CODE_ANALYSIS_NAME / CODE_ANALYSIS_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceTargetFramework,
			&FSolutionGenerator::AddProjectGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(), CODE_ANALYSIS_NAME + CSHARP_SUFFIX),
		ScriptPath / CODE_ANALYSIS_NAME / CODE_ANALYSIS_NAME + CSHARP_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::AddCSharpGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath(), SOURCE_GENERATOR_NAME + PROJECT_SUFFIX),
		ScriptPath / SOURCE_GENERATOR_NAME / SOURCE_GENERATOR_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::AddProjectGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath(),
		                UNREAL_TYPE_SOURCE_GENERATOR_NAME + CSHARP_SUFFIX),
		ScriptPath / SOURCE_GENERATOR_NAME / UNREAL_TYPE_SOURCE_GENERATOR_NAME + CSHARP_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::AddCSharpGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath(),
		                ANALYZER_RELEASES_UN_SHIPPED_NAME + MARKDOWN_SUFFIX),
		ScriptPath / SOURCE_GENERATOR_NAME / ANALYZER_RELEASES_UN_SHIPPED_NAME + MARKDOWN_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetWeaversPath(), WEAVERS_NAME + PROJECT_SUFFIX),
		ScriptPath / WEAVERS_NAME / WEAVERS_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>{
			&FSolutionGenerator::ReplaceOutputPath,
			&FSolutionGenerator::AddProjectGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetWeaversPath(), UNREAL_TYPE_WEAVER_NAME + CSHARP_SUFFIX),
		ScriptPath / WEAVERS_NAME / UNREAL_TYPE_WEAVER_NAME + CSHARP_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceYield,
			&FSolutionGenerator::ReplaceDefinition,
			&FSolutionGenerator::ReplaceScriptPath,
			&FSolutionGenerator::AddCSharpGeneratorHeaderComment
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
			&FSolutionGenerator::ReplaceTargetFramework,
			&FSolutionGenerator::AddProjectGeneratorHeaderComment
		});

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetGameProjectPath(),
		TemplatePath / DEFAULT_GAME_NAME + PROJECT_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceImport,
			&FSolutionGenerator::ReplaceTargetFramework,
			&FSolutionGenerator::ReplaceProjectReference
		},
		false);

	CopyTemplate(
		FUnrealCSharpFunctionLibrary::GetGamePropsPath(),
		TemplatePath / DEFAULT_GAME_NAME + PROPS_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>{
			&FSolutionGenerator::ReplaceOutputPath,
			&FSolutionGenerator::AddProjectGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetFullScriptDirectory(), SHARED_NAME + PROPS_SUFFIX),
		FPaths::Combine(TemplatePath, SHARED_NAME + PROPS_SUFFIX),
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceDefineConstants,
			&FSolutionGenerator::AddProjectGeneratorHeaderComment
		});

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetFullScriptDirectory(),
		                FUnrealCSharpFunctionLibrary::GetScriptDirectory() + SOLUTION_SUFFIX),
		TemplatePath / SOLUTION_NAME + SOLUTION_SUFFIX,
		TArray<TFunction<void(FString& OutResult)>>
		{
			&FSolutionGenerator::ReplaceProject,
			&FSolutionGenerator::ReplaceProjectPlaceholder,
			&FSolutionGenerator::ReplaceSolutionConfigurationPlatformsPlaceholder,
			&FSolutionGenerator::AddSolutionGeneratorHeaderComment
		});
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src, const bool bReplaceExistingFile)
{
	if (auto& FileManager = IFileManager::Get(); !FileManager.FileExists(*Dest) || bReplaceExistingFile)
	{
		FileManager.Copy(*Dest, *Src);
	}
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src,
                                      const TArray<TFunction<void(FString& OutResult)>>& InFunction,
                                      const bool bReplaceExistingFile)
{
	if (auto& FileManager = IFileManager::Get(); !FileManager.FileExists(*Dest) || bReplaceExistingFile)
	{
		FString Result;

		FFileHelper::LoadFileToString(Result, *Src);

		for (const auto& Function : InFunction)
		{
			Function(Result);
		}

		FUnrealCSharpFunctionLibrary::SaveStringToFile(*Dest, Result);
	}
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
	                                               *PROPS_SUFFIX,
	                                               *FUnrealCSharpFunctionLibrary::GetGameName(),
	                                               *PROPS_SUFFIX
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
	OutResult = OutResult.Replace(TEXT("<ScriptOutputPath></ScriptOutputPath>"),
	                              *FString::Printf(TEXT(
		                              "<ScriptOutputPath>..\\..\\Content\\%s</ScriptOutputPath>"
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

	OutResult = OutResult.Replace(TEXT("var ueAssemblyName = \"\";"),
	                              *FString::Printf(TEXT(
		                              "var ueAssemblyName = \"%s\";"
	                              ),
	                                               *FUnrealCSharpFunctionLibrary::GetUEName()
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

void FSolutionGenerator::ReplaceProjectPlaceholder(FString& OutResult)
{
	FString Projects;

	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		for (const auto& CustomProject : UnrealCSharpSetting->GetCustomProjects())
		{
			Projects += FString::Printf(TEXT(
				"Project(\"{%s}\") = \"%s\", \"%s\\%s%s\", \"{%s}\"\n"
				"EndProject\n"
			),
			                            *CSHARP_GUID,
			                            *CustomProject.Name,
			                            *CustomProject.Name,
			                            *CustomProject.Name,
			                            *PROJECT_SUFFIX,
			                            *CustomProject.GUID()
			);
		}
	}

	OutResult = OutResult.Replace(*FString::Printf(TEXT(
		                              "%s"
		                              "\r\n"),
	                                               *PROJECT_PLACEHOLDER
	                              ),
	                              *Projects);
}

void FSolutionGenerator::ReplaceSolutionConfigurationPlatformsPlaceholder(FString& OutResult)
{
	FString SolutionConfigurationPlatforms;

	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		for (const auto& CustomProject : UnrealCSharpSetting->GetCustomProjects())
		{
			SolutionConfigurationPlatforms += FString::Printf(TEXT(
				"\t\t{%s}.Debug|Any CPU.ActiveCfg = Debug|Any CPU\n"
				"\t\t{%s}.Debug|Any CPU.Build.0 = Debug|Any CPU\n"
				"\t\t{%s}.Release|Any CPU.ActiveCfg = Release|Any CPU\n"
				"\t\t{%s}.Release|Any CPU.Build.0 = Release|Any CPU\n"
			),
			                                                  *CustomProject.GUID(),
			                                                  *CustomProject.GUID(),
			                                                  *CustomProject.GUID(),
			                                                  *CustomProject.GUID()
			);
		}
	}

	OutResult = OutResult.Replace(*FString::Printf(TEXT(
		                              "\t\t{%s}.Release|Any CPU.Build.0 = Release|Any CPU"
		                              "\r\n"
	                              ),
	                                               *SOLUTION_CONFIGURATION_PLATFORMS_PLACEHOLDER
	                              ),
	                              *SolutionConfigurationPlatforms);
}

void FSolutionGenerator::ReplaceScriptPath(FString& OutResult)
{
	OutResult = OutResult.Replace(TEXT("var scriptPathName = \"\";"),
	                              *FString::Printf(TEXT(
		                              "var scriptPathName = \"%s\";"
	                              ),
	                                               *PLUGIN_SCRIPT_PATH
	                              ));
}

void FSolutionGenerator::AddProjectGeneratorHeaderComment(FString& OutResult)
{
	OutResult = FString::Printf(TEXT(
		"<!-- ===========================================================================\n"
		"    Generated code exported from UnrealCSharp.\n"
		"    DO NOT modify this manually!\n"
		"============================================================================ -->\n"
		"\n"
		"%s"
	),
	                            *OutResult
	);
}

void FSolutionGenerator::AddSolutionGeneratorHeaderComment(FString& OutResult)
{
	OutResult = FString::Printf(TEXT(
		"# ===========================================================================\n"
		"#    Generated code exported from UnrealCSharp.\n"
		"#    DO NOT modify this manually!\n"
		"# ===========================================================================\n"
		"\n"
		"%s"
	),
	                            *OutResult
	);
}

void FSolutionGenerator::AddCSharpGeneratorHeaderComment(FString& OutResult)
{
	OutResult = FString::Printf(TEXT(
		"%s\n%s"
	),
	                            *FGeneratorCore::GetGeneratorHeaderComment(),
	                            *OutResult
	);
}
