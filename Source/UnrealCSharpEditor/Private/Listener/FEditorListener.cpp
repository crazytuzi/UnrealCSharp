#include "Listener/FEditorListener.h"
#include "Interfaces/IMainFrameModule.h"
#include "DirectoryWatcherModule.h"
#include "FClassGenerator.h"
#include "FCSharpCompiler.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "WidgetBlueprint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"

FEditorListener::FEditorListener()
{
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddStatic(&FEditorListener::OnPostEngineInit);

	OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddStatic(&FEditorListener::OnPreBeginPIE);

	const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	AssetRegistryModule.Get().OnFilesLoaded().AddRaw(this, &FEditorListener::OnFilesLoaded);

	auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	OnMainFrameCreationFinishedDelegateHandle = MainFrameModule.OnMainFrameCreationFinished().AddRaw(
		this, &FEditorListener::OnMainFrameCreationFinished);

	auto& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(TEXT("DirectoryWatcher"));

	DirectoryWatcherModule.Get()->RegisterDirectoryChangedCallback_Handle(
		FUnrealCSharpFunctionLibrary::GetGamePath(),
		IDirectoryWatcher::FDirectoryChanged::CreateRaw(this, &FEditorListener::OnDirectoryChanged),
		OnDirectoryChangedDelegateHandle,
		IDirectoryWatcher::WatchOptions::IncludeDirectoryChanges
	);
}

FEditorListener::~FEditorListener()
{
	if (OnDirectoryChangedDelegateHandle.IsValid())
	{
		auto& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(
			TEXT("DirectoryWatcher"));

		DirectoryWatcherModule.Get()->UnregisterDirectoryChangedCallback_Handle(
			FUnrealCSharpFunctionLibrary::GetGamePath(), OnDirectoryChangedDelegateHandle);
	}

	if (OnMainFrameCreationFinishedDelegateHandle.IsValid())
	{
		auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

		MainFrameModule.OnMainFrameCreationFinished().Remove(OnMainFrameCreationFinishedDelegateHandle);
	}

	if (OnPreBeginPIEDelegateHandle.IsValid())
	{
		FCoreDelegates::OnPostEngineInit.Remove(OnPreBeginPIEDelegateHandle);
	}

	if (OnPostEngineInitDelegateHandle.IsValid())
	{
		FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitDelegateHandle);
	}
}

void FEditorListener::OnPostEngineInit()
{
	FCSharpCompiler::Get().Compile();
}

void FEditorListener::OnPreBeginPIE(const bool)
{
	while (FCSharpCompiler::Get().IsCompiling())
	{
		// @TODO

		FPlatformProcess::Sleep(0.01f);
	}
}

void FEditorListener::OnFilesLoaded()
{
	const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	AssetRegistryModule.Get().OnAssetAdded().AddRaw(this, &FEditorListener::OnAssetAdded);

	AssetRegistryModule.Get().OnAssetRemoved().AddRaw(this, &FEditorListener::OnAssetRemoved);

	AssetRegistryModule.Get().OnAssetRenamed().AddRaw(this, &FEditorListener::OnAssetRenamed);

	AssetRegistryModule.Get().OnAssetUpdated().AddRaw(this, &FEditorListener::OnAssetUpdated);
}

void FEditorListener::OnAssetAdded(const FAssetData& InAssetData) const
{
	OnAssetChanged(InAssetData,
	               [](const UClass* InClass)
	               {
		               FClassGenerator::Generator(InClass);

		               FCSharpCompiler::Get().Compile();
	               },
	               [](const UUserDefinedStruct* InUserDefinedStruct)
	               {
		               FStructGenerator::Generator(InUserDefinedStruct);

		               FCSharpCompiler::Get().Compile();
	               },
	               [](const UUserDefinedEnum* InUserDefinedEnum)
	               {
		               FEnumGenerator::Generator(InUserDefinedEnum);

		               FCSharpCompiler::Get().Compile();
	               }
	);
}

void FEditorListener::OnAssetRemoved(const FAssetData& InAssetData) const
{
	OnAssetChanged(InAssetData,
	               [](const UClass* InClass)
	               {
		               FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			               *FUnrealCSharpFunctionLibrary::GetFileName(InClass));

		               FCSharpCompiler::Get().Compile();
	               },
	               [](const UUserDefinedStruct* InUserDefinedStruct)
	               {
		               FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			               *FUnrealCSharpFunctionLibrary::GetFileName(InUserDefinedStruct));

		               FCSharpCompiler::Get().Compile();
	               },
	               [](const UUserDefinedEnum* InUserDefinedEnum)
	               {
		               FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			               *FUnrealCSharpFunctionLibrary::GetFileName(InUserDefinedEnum));

		               FCSharpCompiler::Get().Compile();
	               }
	);
}

void FEditorListener::OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const
{
	OnAssetChanged(InAssetData,
	               [&](const UClass* InClass)
	               {
		               FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			               *FUnrealCSharpFunctionLibrary::GetOldFileName(
				               InClass, FString::Printf(
					               TEXT("%s_C"),
					               *InOldObjectPath.Right(
						               InOldObjectPath.Len() - InOldObjectPath.Find(TEXT(".")) - 1))));

		               FClassGenerator::Generator(InClass);

		               FCSharpCompiler::Get().Compile();
	               },
	               [&](const UUserDefinedStruct* InUserDefinedStruct)
	               {
		               FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			               *FUnrealCSharpFunctionLibrary::GetOldFileName(InUserDefinedStruct,
			                                                             InOldObjectPath.Right(
				                                                             InOldObjectPath.Len() - InOldObjectPath.
				                                                             Find(
					                                                             TEXT(".")) - 1)));

		               FStructGenerator::Generator(InUserDefinedStruct);

		               FCSharpCompiler::Get().Compile();
	               },
	               [&](const UUserDefinedEnum* InUserDefinedEnum)
	               {
		               FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			               *FUnrealCSharpFunctionLibrary::GetOldFileName(InUserDefinedEnum,
			                                                             InOldObjectPath.Right(
				                                                             InOldObjectPath.Len() - InOldObjectPath.
				                                                             Find(
					                                                             TEXT(".")) - 1)));

		               FEnumGenerator::Generator(InUserDefinedEnum);

		               FCSharpCompiler::Get().Compile();
	               }
	);
}

void FEditorListener::OnAssetUpdated(const FAssetData& InAssetData) const
{
	OnAssetChanged(InAssetData,
	               [](const UClass* InClass)
	               {
		               FClassGenerator::Generator(InClass);

		               FCSharpCompiler::Get().Compile();
	               },
	               [](const UUserDefinedStruct* InUserDefinedStruct)
	               {
		               FStructGenerator::Generator(InUserDefinedStruct);

		               FCSharpCompiler::Get().Compile();
	               },
	               [](const UUserDefinedEnum* InUserDefinedEnum)
	               {
		               FEnumGenerator::Generator(InUserDefinedEnum);

		               FCSharpCompiler::Get().Compile();
	               }
	);
}

void FEditorListener::OnMainFrameCreationFinished(const TSharedPtr<SWindow> InRootWindow, bool)
{
	InRootWindow->GetOnWindowActivatedEvent().AddRaw(this, &FEditorListener::OnWindowActivatedEvent);
}

void FEditorListener::OnWindowActivatedEvent()
{
	if (FileChanges.Num() > 0)
	{
		FCSharpCompiler::Get().Compile();

		FileChanges.Reset();
	}
}

void FEditorListener::OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges)
{
	FileChanges.Append(InFileChanges);
}

void FEditorListener::OnAssetChanged(const FAssetData& InAssetData,
                                     const TFunction<void(const UClass*)> InBlueprint,
                                     const TFunction<void(const UUserDefinedStruct*)> InUserDefinedStruct,
                                     const TFunction<void(const UUserDefinedEnum*)> InUserDefinedEnum) const
{
	if (InAssetData.AssetClass == UBlueprint::StaticClass()->GetFName() ||
		InAssetData.AssetClass == UWidgetBlueprint::StaticClass()->GetFName())
	{
		if (const auto Blueprint = LoadObject<UBlueprint>(nullptr, *InAssetData.ObjectPath.ToString()))
		{
			if (const auto Class = Cast<UClass>(Blueprint->GeneratedClass))
			{
				InBlueprint(Class);
			}
		}
	}
	else if (InAssetData.AssetClass == UUserDefinedStruct::StaticClass()->GetFName())
	{
		if (const auto UserDefinedStruct = LoadObject<UUserDefinedStruct>(nullptr, *InAssetData.ObjectPath.ToString()))
		{
			InUserDefinedStruct(UserDefinedStruct);
		}
	}
	else if (InAssetData.AssetClass == UUserDefinedEnum::StaticClass()->GetFName())
	{
		if (const auto UserDefinedEnum = LoadObject<UUserDefinedEnum>(nullptr, *InAssetData.ObjectPath.ToString()))
		{
			InUserDefinedEnum(UserDefinedEnum);
		}
	}
}
