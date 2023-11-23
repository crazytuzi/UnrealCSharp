#include "Dynamic/FDynamicGenerator.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicStructGenerator.h"
#include "Dynamic/FDynamicEnumGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"

void FDynamicGenerator::Generator()
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

	if (FMonoDomain::bLoadSucceed)
	{
		FDynamicClassGenerator::Generator();

		FDynamicStructGenerator::Generator();

		FDynamicEnumGenerator::Generator();

		FMonoDomain::Deinitialize();
	}
}

#if WITH_EDITOR
void FDynamicGenerator::CodeAnalysisGenerator()
{
	FDynamicClassGenerator::CodeAnalysisGenerator();

	FDynamicStructGenerator::CodeAnalysisGenerator();

	FDynamicEnumGenerator::CodeAnalysisGenerator();
}
#endif

#if WITH_EDITOR
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

	for (const auto& Data : FileChangeData)
	{
		if (FPaths::GetExtension(Data.Filename) == TEXT("cs"))
		{
			auto Filename = FPaths::GetBaseFilename(Data.Filename);

			if (const auto MonoClass = FMonoDomain::Class_From_Name(FDynamicGeneratorCore::GetClassNameSpace(),
			                                                        Filename))
			{
				if (FDynamicClassGenerator::IsDynamicClass(MonoClass))
				{
					FDynamicClassGenerator::Generator(MonoClass, true);
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
	}

	if (FMonoDomain::bLoadSucceed)
	{
		FMonoDomain::Deinitialize();
	}
}
#endif
