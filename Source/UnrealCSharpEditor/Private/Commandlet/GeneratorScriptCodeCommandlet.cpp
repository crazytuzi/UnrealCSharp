#include "Commandlet/GeneratorScriptCodeCommandlet.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "HAL/PlatformFileManager.h"
#include "UnrealCSharpEditor.h"

int32 UGeneratorScriptCodeCommandlet::Main(const FString& Params)
{
	if (FString Platform; FParse::Value(*Params, TEXT("-Platform="), Platform))
	{
		FUnrealCSharpCoreModuleDelegates::OnUnloadAssemblies.Broadcast();

		auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		for (const auto& AssemblyPath : FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath())
		{
			if (PlatformFile.FileExists(*AssemblyPath))
			{
				PlatformFile.DeleteFile(*AssemblyPath);
			}
		}

		FUnrealCSharpEditorModule::Generator(Platform);
	}

	return 0;
}
