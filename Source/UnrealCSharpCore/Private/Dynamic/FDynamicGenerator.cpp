#include "Dynamic/FDynamicGenerator.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoDomainScope.h"
#include "Dynamic/FDynamicEnumGenerator.h"
#include "Dynamic/FDynamicStructGenerator.h"
#include "Dynamic/FDynamicInterfaceGenerator.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"

#if WITH_EDITOR
bool FDynamicGenerator::bIsFullGenerator{};

TMap<FString, FString> FDynamicGenerator::CodeAnalysisDynamicFilesMap{};
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

bool FDynamicGenerator::IsDynamicClass(const UClass* InClass)
{
	return InClass->IsChildOf(UInterface::StaticClass())
		       ? FDynamicInterfaceGenerator::IsDynamicInterface(InClass)
		       : FDynamicClassGenerator::IsDynamicClass(InClass);
}

bool FDynamicGenerator::IsDynamicStruct(const UScriptStruct* InScriptStruct)
{
	return FDynamicStructGenerator::IsDynamicStruct(InScriptStruct);
}

bool FDynamicGenerator::IsDynamicEnum(const UEnum* InEnum)
{
	return FDynamicEnumGenerator::IsDynamicEnum(InEnum);
}

FString FDynamicGenerator::GetNameSpace(const UClass* InClass)
{
	return InClass->IsChildOf(UInterface::StaticClass())
		       ? FDynamicInterfaceGenerator::GetNameSpace(InClass)
		       : FDynamicClassGenerator::GetNameSpace(InClass);
}

FString FDynamicGenerator::GetNameSpace(const UScriptStruct* InScriptStruct)
{
	return FDynamicStructGenerator::GetNameSpace(InScriptStruct);
}

FString FDynamicGenerator::GetNameSpace(const UEnum* InEnum)
{
	return FDynamicEnumGenerator::GetNameSpace(InEnum);
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

void FDynamicGenerator::SetCodeAnalysisDynamicFilesMap()
{
	CodeAnalysisDynamicFilesMap = FUnrealCSharpFunctionLibrary::LoadFileToString(FString::Printf(TEXT(
		"%s/%s.json"
	),
		*FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		*DYNAMIC_FILE
	));
}

FString FDynamicGenerator::GetDynamicFile(const UClass* InClass)
{
	return GetDynamicFile(FString::Printf(TEXT(
		"%s.%s"),
	                                      *GetNameSpace(InClass),
	                                      *FUnrealCSharpFunctionLibrary::GetFullClass(InClass)
	));
}

FString FDynamicGenerator::GetDynamicFile(const FString& InName)
{
	const auto FoundDynamicFile = CodeAnalysisDynamicFilesMap.Find(InName);

	return FoundDynamicFile != nullptr ? *FoundDynamicFile : FString{};
}

FString FDynamicGenerator::GetDynamicNormalizeFile(const UClass* InClass)
{
	auto File = GetDynamicFile(InClass);

	FPaths::NormalizeFilename(File);

	return File;
}

void FDynamicGenerator::Generator(const TArray<FFileChangeData>& InFileChangeData)
{
	if (!InFileChangeData.IsEmpty())
	{
		FDynamicGeneratorCore::BeginCodeAnalysisGenerator();

		FMonoDomainScope([InFileChangeData]()
		{
			TArray<FString> FileChange;

			for (const auto& Data : InFileChangeData)
			{
				FileChange.AddUnique(Data.Filename);
			}

			for (const auto& File : FileChange)
			{
				if (IFileManager::Get().FileExists(*File))
				{
					switch (MonoClass* Class; GetDynamicType(File, Class))
					{
					case EDynamicType::Class:
						{
							FDynamicClassGenerator::Generator(Class, EDynamicClassGeneratorType::FileChange);
						}
						break;
					case EDynamicType::Struct:
						{
							FDynamicStructGenerator::Generator(Class);
						}
						break;
					case EDynamicType::Enum:
						{
							FDynamicEnumGenerator::Generator(Class);
						}
						break;
					case EDynamicType::Interface:
						{
							FDynamicInterfaceGenerator::Generator(Class);
						}
						break;
					default: ;
					}
				}
			}
		});

		FDynamicGeneratorCore::EndCodeAnalysisGenerator();
	}
}

void FDynamicGenerator::OnPrePIEEnded(const bool bIsSimulating)
{
	FDynamicClassGenerator::OnPrePIEEnded(bIsSimulating);
}

bool FDynamicGenerator::IsFullGenerator()
{
	return bIsFullGenerator;
}

EDynamicType FDynamicGenerator::GetDynamicType(const FString& InFile, MonoClass*& OutMonoClass)
{
	for (auto const& [Name, File] : CodeAnalysisDynamicFilesMap)
	{
		if (FPaths::IsSamePath(File, InFile))
		{
			if (auto Index = 0; Name.FindLastChar(TEXT('.'), Index))
			{
				OutMonoClass = FMonoDomain::Class_From_Name(Name.Left(Index), Name.Right(Name.Len() - Index - 1));

				return FDynamicGeneratorCore::GetDynamicType(Name);
			}

			break;
		}
	}

	return EDynamicType::None;
}
#endif
