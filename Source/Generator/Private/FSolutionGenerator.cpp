#include "FSolutionGenerator.h"
#include "CoreMacro/Macro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Misc/FileHelper.h"

void FSolutionGenerator::Generator()
{
	const auto TemplatePath = FUnrealCSharpFunctionLibrary::GetPluginPath() / TEMPLATE;

	CopyCSProj(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetUEPath(),
		                FUnrealCSharpFunctionLibrary::GetUEProjectName() + PROJECT_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetUEProjectName() + PROJECT_SUFFIX);

	CopyCSProj(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGamePath(),
		                FUnrealCSharpFunctionLibrary::GetGameProjectName() + PROJECT_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetGameProjectName() + PROJECT_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGamePath() / FODY_WEAVER_XML),
		TemplatePath / FODY_WEAVER_XML);

	CopySolution(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetBasePath(),
		                FUnrealCSharpFunctionLibrary::GetBaseName() + SOLUTION_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetBaseName() + SOLUTION_SUFFIX);
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src)
{
	if (auto& FileManager = IFileManager::Get(); !FileManager.FileExists(*Dest))
	{
		FileManager.Copy(*Dest, *Src);
	}
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src,
                                      const TFunction<void(FString& InResult)>& InCopyTemplate)
{
	FString Result;

	FFileHelper::LoadFileToString(Result, *Src);

	auto Index = 0;

	const auto PluginBaseDir = FUnrealCSharpFunctionLibrary::GetPluginBaseDir();

	PluginBaseDir.FindLastChar('/', Index);

	Result = Result.Replace(*PLUGIN_NAME, *PluginBaseDir.Right(PluginBaseDir.Len() - Index - 1));

	InCopyTemplate(Result);

	auto& FileManager = IFileManager::Get();

	FFileHelper::SaveStringToFile(Result, *Dest, FFileHelper::EEncodingOptions::ForceUTF8, &FileManager);
}

void FSolutionGenerator::CopyCSProj(const FString& Dest, const FString& Src)
{
	CopyTemplate(Dest, Src, [](FString& InResult)
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

		InResult = InResult.Replace(TEXT("<DefineConstants>$(DefineConstants);</DefineConstants>"), *DefineConstants);
	});
}

void FSolutionGenerator::CopySolution(const FString& Dest, const FString& Src)
{
	CopyTemplate(Dest, Src, [](FString&)
	{
	});
}
