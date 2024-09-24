#include "Dynamic/FDynamicGenerator.h"
#include "Domain/FMonoDomainScope.h"
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

	FMonoDomainScope([]()
	{
		FDynamicEnumGenerator::Generator();

		FDynamicStructGenerator::Generator();

		FDynamicInterfaceGenerator::Generator();

		FDynamicClassGenerator::Generator();

		FDynamicGeneratorCore::Generator();
	});

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
	FMonoDomainScope([FileChangeData]()
	{
		TArray<FString> FileChange;

		for (const auto& Data : FileChangeData)
		{
			FileChange.AddUnique(FPaths::GetBaseFilename(Data.Filename));
		}

		for (const auto& File : FileChange)
		{
			if (auto Class = FDynamicClassGenerator::GetMonoClass(File))
			{
				FDynamicClassGenerator::Generator(Class);
			}
			else if (Class = FDynamicStructGenerator::GetMonoClass(File); Class != nullptr)
			{
				FDynamicStructGenerator::Generator(Class);
			}
			else if (Class = FDynamicEnumGenerator::GetMonoClass(File); Class != nullptr)
			{
				FDynamicEnumGenerator::Generator(Class);
			}
			else if (Class = FDynamicInterfaceGenerator::GetMonoClass(File); Class != nullptr)
			{
				FDynamicInterfaceGenerator::Generator(Class);
			}
		}
	});
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
