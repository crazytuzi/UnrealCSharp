#include "Commandlet/GeneratorScriptCodeCommandlet.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/CommandLine.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Domain/Script/IScriptDomain.h"
#include "UnrealCSharpEditor.h"

int32 UGeneratorScriptCodeCommandlet::Main(const FString& Params)
{
	int32 Result = 0;

	if (FString Platform; FParse::Value(*Params, TEXT("Platform="), Platform))
	{
		if (FParse::Param(*Params, TEXT("Rebuild")))
		{
			if (const auto ScriptDomain = IScriptDomain::Get())
			{
				ScriptDomain->Deinitialize();
			}

			auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

			for (const auto& AssemblyPublishPath : FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath())
			{
				if (PlatformFile.FileExists(*AssemblyPublishPath))
				{
					PlatformFile.DeleteFile(*AssemblyPublishPath);
				}
			}
		}

		FUnrealCSharpEditorModule::Generator(Platform, true);
	}
	else
	{
		Result = 1;
	}

	return Result;
}

bool UGeneratorScriptCodeCommandlet::IsRunningGeneratorScriptCodeCommandlet()
{
	FString Value;

	return FParse::Value(FCommandLine::Get(), TEXT("run="), Value) &&
		Value.Equals(TEXT("GeneratorScriptCode"), ESearchCase::IgnoreCase);
}
