﻿#include "Listener/FEditorListener.h"
#include "Interfaces/IMainFrameModule.h"
#include "DirectoryWatcherModule.h"
#include "FAssetGenerator.h"
#include "FCodeAnalysis.h"
#include "FCSharpCompiler.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Setting/UnrealCSharpEditorSetting.h"

FEditorListener::FEditorListener():
	bIsPIEPlaying(false),
	bIsGenerating(false)
{
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorListener::OnPostEngineInit);

	OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &FEditorListener::OnPreBeginPIE);

	OnPrePIEEndedDelegateHandle = FEditorDelegates::PrePIEEnded.AddRaw(this, &FEditorListener::OnPrePIEEnded);

	OnCancelPIEDelegateHandle = FEditorDelegates::CancelPIE.AddRaw(this, &FEditorListener::OnCancelPIEEnded);

	OnBeginGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.AddRaw(
		this, &FEditorListener::OnBeginGenerator);

	OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
		this, &FEditorListener::OnEndGenerator);

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

	if (OnEndGeneratorDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Remove(OnEndGeneratorDelegateHandle);
	}

	if (OnBeginGeneratorDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.Remove(OnBeginGeneratorDelegateHandle);
	}

	if (OnCancelPIEDelegateHandle.IsValid())
	{
		FEditorDelegates::CancelPIE.Remove(OnCancelPIEDelegateHandle);
	}

	if (OnPrePIEEndedDelegateHandle.IsValid())
	{
		FEditorDelegates::PrePIEEnded.Remove(OnPrePIEEndedDelegateHandle);
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

void FEditorListener::OnPrePIEEnded(const bool)
{
	FDynamicGenerator::OnPrePIEEnded();
}

void FEditorListener::OnCancelPIEEnded()
{
	bIsPIEPlaying = false;
}

void FEditorListener::OnBeginGenerator()
{
	bIsGenerating = true;

	FileChanges.Reset();
}

void FEditorListener::OnEndGenerator()
{
	bIsGenerating = false;

	FileChanges.Reset();
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
	if (!FileChanges.IsEmpty())
	{
		FCSharpCompiler::Get().Compile(FileChanges);

		FileChanges.Reset();
	}
}

void FEditorListener::OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges)
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableDirectoryChanged())
		{
			if (!bIsGenerating)
			{
				static auto IgnoreDirectories = TArray<FString>
				{
					TEXT("/Proxy/"),
					TEXT("/obj/")
				};

				for (const auto& FileChange : InFileChanges)
				{
					auto bIsIgnored = false;

					for (const auto& IgnoreDirectory : IgnoreDirectories)
					{
						if (FileChange.Filename.Contains(IgnoreDirectory))
						{
							bIsIgnored = true;

							break;
						}
					}

					if (!bIsIgnored)
					{
						FileChanges.Add(FileChange);
					}
				}
			}
		}
	}
}

void FEditorListener::OnAssetChanged(const TFunction<void()>& InGenerator) const
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableAssetChanged())
		{
			if (!bIsPIEPlaying && !bIsGenerating)
			{
				FGeneratorCore::BeginGenerator();

				InGenerator();

				FCSharpCompiler::Get().Compile();

				FGeneratorCore::EndGenerator();
			}
		}
	}
}
