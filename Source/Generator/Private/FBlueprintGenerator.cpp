#include "FBlueprintGenerator.h"
#include "FClassGenerator.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "WidgetBlueprint.h"
#include "FGeneratorCore.h"
#include "UEVersion.h"

void FBlueprintGenerator::Generator()
{
	const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	TArray<FAssetData> OutAssetData;

	TArray<UUserDefinedEnum*> UserDefinedEnums;

#if UE_GET_ASSETS_BY_PATHS
	for (const auto& AssetsPath : FGeneratorCore::GetSupportedAssetPath())
	{
		AssetRegistryModule.Get().GetAssetsByPath(AssetsPath, OutAssetData, true);
#else
	AssetRegistryModule.Get().GetAssetsByPaths(FGeneratorCore::GetSupportedAssetPath(), OutAssetData, true);
#endif

	for (const auto& AssetData : OutAssetData)
	{
		if (const auto AssetDataClass = AssetData.GetClass())
		{
			const auto& AssetName = AssetDataClass->GetFName();

			if (AssetName == UBlueprint::StaticClass()->GetFName() ||
				AssetName == UWidgetBlueprint::StaticClass()->GetFName())
			{
				if (const auto Blueprint = LoadObject<
					UBlueprint>(nullptr, *AssetData.ObjectPath.ToString()))
				{
					if (const auto Class = Cast<UClass>(Blueprint->GeneratedClass))
					{
						FClassGenerator::Generator(Class);
					}
				}
			}
			else if (AssetName == UUserDefinedStruct::StaticClass()->GetFName())
			{
				if (const auto UserDefinedStruct = LoadObject<
					UUserDefinedStruct>(nullptr, *AssetData.ObjectPath.ToString()))
				{
					FStructGenerator::Generator(UserDefinedStruct);
				}
			}
			else if (AssetName == UUserDefinedEnum::StaticClass()->GetFName())
			{
				if (const auto UserDefinedEnum = LoadObject<
					UUserDefinedEnum>(nullptr, *AssetData.ObjectPath.ToString()))
				{
					UserDefinedEnums.Emplace(UserDefinedEnum);
				}
			}
		}
	}

#if UE_GET_ASSETS_BY_PATHS
	}
#endif

	for (const auto& UserDefinedEnum : UserDefinedEnums)
	{
		FEnumGenerator::Generator(UserDefinedEnum);
	}
}
