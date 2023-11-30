#include "Listener/FEditorListener.h"
#include "Interfaces/IMainFrameModule.h"
#include "DirectoryWatcherModule.h"
#include "FAssetGenerator.h"
#include "FCodeAnalysis.h"
#include "FCSharpCompiler.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Dynamic/FDynamicGenerator.h"

bool FEditorListener::bIsPIEPlaying = false;

FEditorListener::FEditorListener()
{
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddStatic(&FEditorListener::OnPostEngineInit);

	OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddStatic(&FEditorListener::OnPreBeginPIE);

	OnCancelPIEDelegateHandle = FEditorDelegates::CancelPIE.AddStatic(&FEditorListener::OnCancelPIEEnded);

	const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	AssetRegistryModule.Get().OnFilesLoaded().AddRaw(this, &FEditorListener::OnFilesLoaded);

	auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	OnMainFrameCreationFinishedDelegateHandle = MainFrameModule.OnMainFrameCreationFinished().AddRaw(
		this, &FEditorListener::OnMainFrameCreationFinished);

	auto& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(TEXT("DirectoryWatcher"));

	const auto& ChangedDirectories = FUnrealCSharpFunctionLibrary::GetChangedDirectories();

	for (const auto& Directory : ChangedDirectories)
	{
		DirectoryWatcherModule.Get()->RegisterDirectoryChangedCallback_Handle(
			Directory,
			IDirectoryWatcher::FDirectoryChanged::CreateRaw(this, &FEditorListener::OnDirectoryChanged),
			OnDirectoryChangedDelegateHandle,
			IDirectoryWatcher::WatchOptions::IncludeDirectoryChanges
		);
	}
}

FEditorListener::~FEditorListener()
{
	if (OnDirectoryChangedDelegateHandle.IsValid())
	{
		auto& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(
			TEXT("DirectoryWatcher"));

		const auto& ChangedDirectories = FUnrealCSharpFunctionLibrary::GetChangedDirectories();

		for (const auto& Directory : ChangedDirectories)
		{
			DirectoryWatcherModule.Get()->UnregisterDirectoryChangedCallback_Handle(
				Directory, OnDirectoryChangedDelegateHandle);
		}
	}

	if (OnMainFrameCreationFinishedDelegateHandle.IsValid())
	{
		auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

		MainFrameModule.OnMainFrameCreationFinished().Remove(OnMainFrameCreationFinishedDelegateHandle);
	}

	if (OnCancelPIEDelegateHandle.IsValid())
	{
		FEditorDelegates::CancelPIE.Remove(OnCancelPIEDelegateHandle);
	}

	if (OnPreBeginPIEDelegateHandle.IsValid())
	{
		FEditorDelegates::PreBeginPIE.Remove(OnPreBeginPIEDelegateHandle);
	}

	if (OnPostEngineInitDelegateHandle.IsValid())
	{
		FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitDelegateHandle);
	}
}

void FEditorListener::OnPostEngineInit()
{
	FCodeAnalysis::CodeAnalysis();

	FDynamicGenerator::CodeAnalysisGenerator();
}

void FEditorListener::OnPreBeginPIE(const bool)
{
	bIsPIEPlaying = true;
}

void FEditorListener::OnCancelPIEEnded()
{
	bIsPIEPlaying = false;
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
	OnAssetChanged([&]
	{
		FAssetGenerator::Generator(InAssetData);
	});
}

void FEditorListener::OnAssetRemoved(const FAssetData& InAssetData) const
{
	OnAssetChanged([&]
	{
		FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			*FUnrealCSharpFunctionLibrary::GetFileName(InAssetData));
	});
}

void FEditorListener::OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const
{
	OnAssetChanged([&]
	{
		FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			*FUnrealCSharpFunctionLibrary::GetOldFileName(InAssetData, InOldObjectPath));

		FAssetGenerator::Generator(InAssetData);
	});
}

void FEditorListener::OnAssetUpdated(const FAssetData& InAssetData) const
{
	OnAssetChanged([&]
	{
		FAssetGenerator::Generator(InAssetData);
	});
}

void FEditorListener::OnMainFrameCreationFinished(const TSharedPtr<SWindow> InRootWindow, bool)
{
	InRootWindow->GetOnWindowActivatedEvent().AddRaw(this, &FEditorListener::OnWindowActivatedEvent);
}

void FEditorListener::OnWindowActivatedEvent()
{
	if (FileChanges.Num() > 0)
	{
		FCSharpCompiler::Get().Compile(FileChanges);

		FileChanges.Reset();
	}
}

void FEditorListener::OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges)
{
	FileChanges.Append(InFileChanges);
}

void FEditorListener::OnAssetChanged(const TFunction<void()>& InGenerator)
{
	if (!bIsPIEPlaying)
	{
		FGeneratorCore::BeginGenerator();

		InGenerator();

		FCSharpCompiler::Get().Compile();

		FGeneratorCore::EndGenerator();
	}
}
