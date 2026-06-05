#include "Commandlet/GeneratorCodeCommandlet.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "UnrealCSharpEditor.h"

int32 UGeneratorCodeCommandlet::Main(const FString& Params)
{
	FString TargetPlatform;

	FParse::Value(*Params, TEXT("-Platform="), TargetPlatform);

	if (!TargetPlatform.IsEmpty())
	{
		const auto OriginalPlatformName = FUnrealCSharpFunctionLibrary::GetForcedPlatformName();

		FUnrealCSharpFunctionLibrary::SetForcedPlatformName(TargetPlatform);

		FUnrealCSharpEditorModule::Generator();

		FUnrealCSharpFunctionLibrary::SetForcedPlatformName(OriginalPlatformName);
	}
	else
	{
		FUnrealCSharpEditorModule::Generator();
	}

	return 0;
}
