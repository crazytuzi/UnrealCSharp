#include "Commandlet/GeneratorCodeCommandlet.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "UnrealCSharpEditor.h"

int32 UGeneratorCodeCommandlet::Main(const FString& Params)
{
	FString TargetPlatform;

	FParse::Value(*Params, TEXT("-Platform="), TargetPlatform);

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
