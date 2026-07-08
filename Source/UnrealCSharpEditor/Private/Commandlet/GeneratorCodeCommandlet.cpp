#include "Commandlet/GeneratorCodeCommandlet.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "HAL/PlatformFileManager.h"
#include "UnrealCSharpEditor.h"

int32 UGeneratorCodeCommandlet::Main(const FString& Params)
{
	FString TargetPlatform;

	FParse::Value(*Params, TEXT("-Platform="), TargetPlatform);

	FUnrealCSharpCoreModuleDelegates::OnUnloadAssemblies.Broadcast();

	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	for (const auto& AssemblyPath : FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath())
	{
		if (PlatformFile.FileExists(*AssemblyPath))
		{
			PlatformFile.DeleteFile(*AssemblyPath);
		}
	}

	if (!TargetPlatform.IsEmpty())
	{
		FUnrealCSharpEditorModule::Generator(TargetPlatform);
	}
	else
	{
		FUnrealCSharpEditorModule::Generator();
	}

	return 0;
}
