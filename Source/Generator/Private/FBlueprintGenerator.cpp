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

#if(ENGINE_MAJOR_VERSION == 5)
	Filter.ClassPaths = {
		UBlueprint::StaticClass()->GetClassPathName(), UWidgetBlueprint::StaticClass()->GetClassPathName(),
		UUserDefinedStruct::StaticClass()->GetClassPathName(), UUserDefinedEnum::StaticClass()->GetClassPathName()
	};
#else
	Filter.ClassNames = {
		UBlueprint::StaticClass()->GetFName(), UWidgetBlueprint::StaticClass()->GetFName(),
		UUserDefinedStruct::StaticClass()->GetFName(), UUserDefinedEnum::StaticClass()->GetFName()
	};
#endif

	TArray<FAssetData> OutAssetData;

	AssetRegistryModule.Get().GetAssets(Filter, OutAssetData);

	for (const auto& AssetData : OutAssetData)
	{
		if (AssetData.AssetClass == UBlueprint::StaticClass()->GetFName() ||
			AssetData.AssetClass == UWidgetBlueprint::StaticClass()->GetFName())
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
		else if (AssetData.AssetClass == UUserDefinedStruct::StaticClass()->GetFName())
		{
			if (const auto UserDefinedStruct = LoadObject<
				UUserDefinedStruct>(nullptr, *AssetData.ObjectPath.ToString()))
			{
				FStructGenerator::Generator(UserDefinedStruct);
			}
		}
		else if (AssetData.AssetClass == UUserDefinedEnum::StaticClass()->GetFName())
		{
			if (const auto UserDefinedEnum = LoadObject<
				UUserDefinedEnum>(nullptr, *AssetData.ObjectPath.ToString()))
			{
				FEnumGenerator::Generator(UserDefinedEnum);
			}
		}
	}
}
