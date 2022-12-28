#include "FBlueprintGenerator.h"
#include "FClassGenerator.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "UMGEditor/Public/WidgetBlueprint.h"

void FBlueprintGenerator::Generator()
{
	const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	FARFilter Filter;

	Filter.ClassNames = {
		UBlueprint::StaticClass()->GetFName(), UWidgetBlueprint::StaticClass()->GetFName(),
		UUserDefinedStruct::StaticClass()->GetFName(), UUserDefinedEnum::StaticClass()->GetFName()
	};

	TArray<FAssetData> OutAssetData;

	AssetRegistryModule.Get().GetAssets(Filter, OutAssetData);

	for (auto AssetData : OutAssetData)
	{
		if (const auto Blueprint = LoadObject<UBlueprint>(nullptr, *AssetData.ObjectPath.ToString()))
		{
			if (const auto Class = Cast<UClass>(Blueprint->GeneratedClass))
			{
				FClassGenerator::Generator(Class);
			}
		}
		else if (const auto UserDefinedStruct = LoadObject<UUserDefinedStruct>(
			nullptr, *AssetData.ObjectPath.ToString()))
		{
			FStructGenerator::Generator(UserDefinedStruct);
		}
		else if (const auto UserDefinedEnum = LoadObject<UUserDefinedEnum>(
			nullptr, *AssetData.ObjectPath.ToString()))
		{
			FEnumGenerator::Generator(UserDefinedEnum);
		}
	}
}
