#include "Dynamic/FDynamicGenerator.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicEnumGenerator.h"
#include "Dynamic/FDynamicStructGenerator.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"

void FDynamicGenerator::Generator()
{
	if (!FMonoDomain::bLoadSucceed)
	{
		FMonoDomain::Initialize({
			"",
			FUnrealCSharpFunctionLibrary::GetAssemblyUtilPath() /
			FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() + DLL_SUFFIX,
			{
				FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
				DLL_SUFFIX,
				FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
				DLL_SUFFIX
			}
		});
	}

	if (FMonoDomain::bLoadSucceed)
	{
		FDynamicEnumGenerator::Generator();

		FDynamicStructGenerator::Generator();

		FDynamicClassGenerator::Generator();

		FMonoDomain::Deinitialize();
	}
}

#if WITH_EDITOR
void FDynamicGenerator::CodeAnalysisGenerator()
{
	FDynamicEnumGenerator::CodeAnalysisGenerator();

	FDynamicStructGenerator::CodeAnalysisGenerator();

	FDynamicClassGenerator::CodeAnalysisGenerator();

	if (IsRunningCookCommandlet())
	{
		CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS, true);
	}
}

void FDynamicGenerator::Generator(const TArray<FFileChangeData>& FileChangeData)
{
	if (FMonoDomain::bLoadSucceed)
	{
		FMonoDomain::Deinitialize();
	}

	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetAssemblyUtilPath() /
		FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() + DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	TArray<FString> FileChange;

	for (const auto& Data : FileChangeData)
	{
		if (FPaths::GetExtension(Data.Filename) == TEXT("cs"))
		{
			FileChange.AddUnique(FPaths::GetBaseFilename(Data.Filename));
		}
	}

	for (const auto& File : FileChange)
	{
		if (const auto MonoClass = FMonoDomain::Class_From_Name(FDynamicGeneratorCore::GetClassNameSpace(), File))
		{
			if (FDynamicClassGenerator::IsDynamicClass(MonoClass))
			{
				FDynamicClassGenerator::Generator(MonoClass);
			}
			else if (FDynamicStructGenerator::IsDynamicStruct(MonoClass))
			{
				FDynamicStructGenerator::Generator(MonoClass, true);
			}
			else if (FDynamicEnumGenerator::IsDynamicEnum(MonoClass))
			{
				FDynamicEnumGenerator::Generator(MonoClass, true);
			}
		}
	}

	if (FMonoDomain::bLoadSucceed)
	{
		FMonoDomain::Deinitialize();
	}
}

void FDynamicGenerator::OnPrePIEEnded()
{
	FDynamicClassGenerator::OnPrePIEEnded();
}
#endif
