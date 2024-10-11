#include "FAssetGenerator.h"
#include "FClassGenerator.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "WidgetBlueprint.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"
#include "UEVersion.h"
#include "Setting/UnrealCSharpEditorSetting.h"

TArray<UUserDefinedEnum*> FAssetGenerator::UserDefinedEnums;

void FAssetGenerator::Generator()
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->IsGenerateAsset())
		{
			const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
				TEXT("AssetRegistry"));

			TArray<FAssetData> OutAssetData;

			AssetRegistryModule.Get().GetAssetsByPaths(FGeneratorCore::GetSupportedAssetPath(), OutAssetData, true);

			for (const auto& AssetData : OutAssetData)
			{
				Generator(AssetData, true);
			}

			for (const auto& UserDefinedEnum : UserDefinedEnums)
			{
				FEnumGenerator::Generator(UserDefinedEnum);
			}

			UserDefinedEnums.Empty();
		}
	}
}

void FAssetGenerator::Generator(const FAssetData& InAssetData, const bool bDelayedGeneratorUserDefinedEnum)
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->IsGenerateAsset())
		{
			if (const auto AssetDataClass = InAssetData.GetClass())
			{
				if (const auto& AssetDataClassName = AssetDataClass->GetFName();
					FGeneratorCore::GetSupportedAssetClassName().Contains(AssetDataClassName))
				{
					if (AssetDataClassName == UBlueprint::StaticClass()->GetFName() ||
						AssetDataClassName == UWidgetBlueprint::StaticClass()->GetFName())
					{
						if (const auto Blueprint = LoadObject<
#if UE_ASSET_DATA_GET_OBJECT_PATH_STRING
							UBlueprint>(nullptr, *InAssetData.GetObjectPathString()))
#else
							UBlueprint>(nullptr, *InAssetData.ObjectPath.ToString()))
#endif
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
#if UE_ASSET_DATA_GET_OBJECT_PATH_STRING
							UUserDefinedStruct>(nullptr, *InAssetData.GetObjectPathString()))
#else
							UUserDefinedStruct>(nullptr, *InAssetData.ObjectPath.ToString()))
#endif
						{
							FStructGenerator::Generator(UserDefinedStruct);
						}
					}
					else if (AssetDataClassName == UUserDefinedEnum::StaticClass()->GetFName())
					{
						if (const auto UserDefinedEnum = LoadObject<
#if UE_ASSET_DATA_GET_OBJECT_PATH_STRING
							UUserDefinedEnum>(nullptr, *InAssetData.GetObjectPathString()))
#else
							UUserDefinedEnum>(nullptr, *InAssetData.ObjectPath.ToString()))
#endif
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

	const auto ClassName = FUnrealCSharpFunctionLibrary::GetAssetName(InAssetData, InAssetData.AssetName.ToString());

	FString UsingNameSpaceContent;

	const auto NameSpaceContent = FString::Printf(TEXT(
		"%s%s"
	),
	                                              *NAMESPACE_ROOT,
	                                              *InAssetData.PackagePath.ToString().Replace(TEXT("/"), TEXT(".")));

	TSet<FString> UsingNameSpaces{COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)};

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
#if UE_ASSET_DATA_GET_OBJECT_PATH_STRING
		                                     InAssetData, InAssetData.GetObjectPathString()),
#else
		                                     InAssetData, InAssetData.ObjectPath.ToString()),
#endif
	                                     *ClassName,
	                                     *FUnrealCSharpFunctionLibrary::GetAssetClass(
		                                     InAssetData, FUnrealCSharpFunctionLibrary::GetFullClass(SuperClass))
	);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FUnrealCSharpFunctionLibrary::GetFileName(InAssetData), Content);
}
