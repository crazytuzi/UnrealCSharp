#include "FAssetGenerator.h"
#include "FClassGenerator.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "WidgetBlueprint.h"
#include "FGeneratorCore.h"
#include "UEVersion.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

TArray<UUserDefinedEnum*> FAssetGenerator::UserDefinedEnums;

void FAssetGenerator::Generator()
{
	const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	TArray<FAssetData> OutAssetData;

#if UE_GET_ASSETS_BY_PATHS
	for (const auto& AssetsPath : FGeneratorCore::GetSupportedAssetPath())
	{
		AssetRegistryModule.Get().GetAssetsByPath(AssetsPath, OutAssetData, true);
#else
	AssetRegistryModule.Get().GetAssetsByPaths(FGeneratorCore::GetSupportedAssetPath(), OutAssetData, true);
#endif

	for (const auto& AssetData : OutAssetData)
	{
		Generator(AssetData, true);
	}

#if UE_GET_ASSETS_BY_PATHS
	}
#endif

	for (const auto& UserDefinedEnum : UserDefinedEnums)
	{
		FEnumGenerator::Generator(UserDefinedEnum);
	}

	UserDefinedEnums.Empty();
}

void FAssetGenerator::Generator(const FAssetData& InAssetData, const bool bDelayedGeneratorUserDefinedEnum)
{
	if (const auto AssetDataClass = InAssetData.GetClass())
	{
		const auto& AssetDataClassName = AssetDataClass->GetFName();

		if (FGeneratorCore::GetSupportedAssetClassName().Contains(AssetDataClassName))
		{
			if (AssetDataClassName == UBlueprint::StaticClass()->GetFName() ||
				AssetDataClassName == UWidgetBlueprint::StaticClass()->GetFName())
			{
				if (const auto Blueprint = LoadObject<
					UBlueprint>(nullptr, *InAssetData.ObjectPath.ToString()))
				{
					if (const auto Class = Cast<UClass>(Blueprint->GeneratedClass))
					{
						FClassGenerator::Generator(Class);
					}
				}
			}
			else if (AssetDataClassName == UUserDefinedStruct::StaticClass()->GetFName())
			{
				if (const auto UserDefinedStruct = LoadObject<
					UUserDefinedStruct>(nullptr, *InAssetData.ObjectPath.ToString()))
				{
					FStructGenerator::Generator(UserDefinedStruct);
				}
			}
			else if (AssetDataClassName == UUserDefinedEnum::StaticClass()->GetFName())
			{
				if (const auto UserDefinedEnum = LoadObject<
					UUserDefinedEnum>(nullptr, *InAssetData.ObjectPath.ToString()))
				{
					if (bDelayedGeneratorUserDefinedEnum)
					{
						UserDefinedEnums.Emplace(UserDefinedEnum);
					}
					else
					{
						FEnumGenerator::Generator(UserDefinedEnum);
					}
				}
			}
			else
			{
				GeneratorAsset(InAssetData);
			}
		}
	}
}

void FAssetGenerator::GeneratorAsset(const FAssetData& InAssetData)
{
	const auto SuperClass = InAssetData.GetClass();

	if (SuperClass == nullptr)
	{
		return;
	}

	if (!FGeneratorCore::IsSupported(SuperClass))
	{
		return;
	}

	auto ClassName = FUnrealCSharpFunctionLibrary::GetAssetName(InAssetData, InAssetData.AssetName.ToString());

	FString UsingNameSpaceContent;

	const auto NameSpaceContent = FString::Printf(TEXT(
		"%s%s"
	),
	                                              TEXT("Script"),
	                                              *InAssetData.PackagePath.ToString().Replace(TEXT("/"), TEXT(".")));

	TSet<FString> UsingNameSpaces{TEXT("Script.Common")};

	UsingNameSpaces.Add(FUnrealCSharpFunctionLibrary::GetClassNameSpace(SuperClass));

	for (auto UsingNameSpace : UsingNameSpaces)
	{
		UsingNameSpaceContent += FString::Printf(TEXT(
			"using %s;\n"
		),
		                                         *UsingNameSpace);
	}

	const auto Content = FString::Printf(TEXT(
		"%s\n"
		"namespace %s\n"
		"{\n"
		"\t[PathName(\"%s\")]\n"
		"\tpublic partial class %s: %s\n"
		"\t{\n"
		"\t}\n"
		"}"
	),
	                                     *UsingNameSpaceContent,
	                                     *NameSpaceContent,
	                                     *FUnrealCSharpFunctionLibrary::GetObjectPathName(
		                                     InAssetData, InAssetData.ObjectPath.ToString()),
	                                     *ClassName,
	                                     *FUnrealCSharpFunctionLibrary::GetAssetClass(
		                                     InAssetData, FUnrealCSharpFunctionLibrary::GetFullClass(SuperClass))
	);

	auto ModuleName = InAssetData.PackagePath.ToString();

	auto DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGenerationPath(ModuleName), ModuleName);

	const auto FileName = FPaths::Combine(DirectoryName, ClassName) + TEXT(".cs");

	FGeneratorCore::SaveStringToFile(FileName, Content);
}
