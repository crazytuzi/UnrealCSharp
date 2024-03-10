﻿#include "Dynamic/FDynamicGenerator.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicEnumGenerator.h"
#include "Dynamic/FDynamicStructGenerator.h"
#include "Dynamic/FDynamicInterfaceGenerator.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"

#if WITH_EDITOR
bool FDynamicGenerator::bIsFullGenerator{};
#endif

void FDynamicGenerator::Generator()
{
#if WITH_EDITOR
	bIsFullGenerator = true;
#endif

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

		FDynamicInterfaceGenerator::Generator();

		FDynamicClassGenerator::Generator();

		FMonoDomain::Deinitialize();
	}

#if WITH_EDITOR
	bIsFullGenerator = false;
#endif
}

#if WITH_EDITOR
void FDynamicGenerator::CodeAnalysisGenerator()
{
	FDynamicGeneratorCore::BeginCodeAnalysisGenerator();

	FDynamicEnumGenerator::CodeAnalysisGenerator();

	FDynamicStructGenerator::CodeAnalysisGenerator();

	FDynamicInterfaceGenerator::CodeAnalysisGenerator();

	FDynamicClassGenerator::CodeAnalysisGenerator();

	FDynamicGeneratorCore::EndCodeAnalysisGenerator();

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
				FDynamicStructGenerator::Generator(MonoClass);
			}
			else if (FDynamicEnumGenerator::IsDynamicEnum(MonoClass))
			{
				FDynamicEnumGenerator::Generator(MonoClass);
			}
			else if (FDynamicInterfaceGenerator::IsDynamicInterface(MonoClass))
			{
				FDynamicInterfaceGenerator::Generator(MonoClass);
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

bool FDynamicGenerator::IsFullGenerator()
{
	return bIsFullGenerator;
}
#endif
