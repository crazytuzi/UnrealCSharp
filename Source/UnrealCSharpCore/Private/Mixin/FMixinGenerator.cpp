#include "Mixin/FMixinGenerator.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoDomain.h"
#include "Mixin/FMixinClassGenerator.h"
#include "Mixin/FMixinStructGenerator.h"
#include "Mixin/FMixinEnumGenerator.h"
#include "Mixin/FMixinGeneratorCore.h"

void FMixinGenerator::Generator()
{
	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() +
		DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	if (FMonoDomain::bLoadSucceed)
	{
		FMixinClassGenerator::Generator();

		FMixinStructGenerator::Generator();

		FMixinEnumGenerator::Generator();

		FMonoDomain::Deinitialize();
	}
}

#if WITH_EDITOR
void FMixinGenerator::Generator(const TArray<FFileChangeData>& FileChangeData)
{
	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() +
		DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	for (const auto& Data : FileChangeData)
	{
		if (FPaths::GetExtension(Data.Filename) == TEXT("cs"))
		{
			auto Filename = FPaths::GetBaseFilename(Data.Filename);

			if (const auto MonoClass = FMonoDomain::Class_From_Name(FMixinGeneratorCore::GetClassNameSpace(), Filename))
			{
				if (FMixinClassGenerator::IsMixinClass(MonoClass))
				{
					FMixinClassGenerator::Generator(MonoClass, true);
				}
				else if (FMixinStructGenerator::IsMixinStruct(MonoClass))
				{
					FMixinStructGenerator::Generator(MonoClass, true);
				}
				else if (FMixinEnumGenerator::IsMixinEnum(MonoClass))
				{
					FMixinEnumGenerator::Generator(MonoClass, true);
				}
			}
		}
	}

	if (FMonoDomain::bLoadSucceed)
	{
		FMonoDomain::Deinitialize();
	}
}
#endif
