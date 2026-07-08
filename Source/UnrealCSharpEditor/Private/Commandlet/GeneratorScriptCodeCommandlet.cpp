#include "Commandlet/GeneratorScriptCodeCommandlet.h"
#include "UnrealCSharpEditor.h"

int32 UGeneratorScriptCodeCommandlet::Main(const FString& Params)
{
	if (FString Platform; FParse::Value(*Params, TEXT("-Platform="), Platform))
	{
		FUnrealCSharpEditorModule::Generator(Platform);
	}

	return 0;
}
