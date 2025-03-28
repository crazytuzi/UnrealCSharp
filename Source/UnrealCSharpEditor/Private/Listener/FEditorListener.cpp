#include "Listener/FEditorListener.h"
#include "Interfaces/IMainFrameModule.h"
#include "DirectoryWatcherModule.h"
#include "HAL/ThreadHeartBeat.h"
#include "HAL/ThreadManager.h"
#include "FAssetGenerator.h"
#include "FCodeAnalysis.h"
#include "FCSharpCompiler.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CoreMacro/Macro.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Listener/FEngineListener.h"
#include "Setting/UnrealCSharpEditorSetting.h"

FEditorListener::FEditorListener():
	bIsPIEPlaying(false),
	bIsGenerating(false)
{
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorListener::OnPostEngineInit);

	OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &FEditorListener::OnPreBeginPIE);

	OnPrePIEEndedDelegateHandle = FEditorDelegates::PrePIEEnded.AddRaw(this, &FEditorListener::OnPrePIEEnded);

	OnCancelPIEDelegateHandle = FEditorDelegates::CancelPIE.AddRaw(this, &FEditorListener::OnCancelPIE);

	OnBeginGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.AddRaw(
		this, &FEditorListener::OnBeginGenerator);

	OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
		this, &FEditorListener::OnEndGenerator);

	OnCompileDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnCompile.AddRaw(
		this, &FEditorListener::OnCompile);

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

	if (OnCompileDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnCompile.Remove(OnCompileDelegateHandle);
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

void FEditorListener::OnPreBeginPIE(const bool bIsSimulating)
{
	bIsPIEPlaying = true;

	while (FCSharpCompiler::Get().IsCompiling())
	{
		FThreadHeartBeat::Get().HeartBeat();

		FPlatformProcess::SleepNoStats(0.0001f);

		FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());

		FThreadManager::Get().Tick();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
	}

	FEngineListener::OnPreBeginPIE(bIsSimulating);
}

void FEditorListener::OnPrePIEEnded(const bool bIsSimulating)
{
	FDynamicGenerator::OnPrePIEEnded(bIsSimulating);
}

void FEditorListener::OnCancelPIE()
{
	FEngineListener::OnCancelPIE();

	bIsPIEPlaying = false;
}

void FEditorListener::OnBeginGenerator()
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableDeleteProxyDirectory())
		{
			if (const auto UEProxyDirectory = FUnrealCSharpFunctionLibrary::GetUEProxyDirectory();
				PlatformFile.DirectoryExists(*UEProxyDirectory))
			{
				PlatformFile.DeleteDirectoryRecursively(*UEProxyDirectory);
			}

			if (const auto GameProxyDirectory = FUnrealCSharpFunctionLibrary::GetGameProxyDirectory();
				PlatformFile.DirectoryExists(*GameProxyDirectory))
			{
				PlatformFile.DeleteDirectoryRecursively(*GameProxyDirectory);
			}
		}
	}

	auto BindingPath = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGameProxyDirectory(),
	                                   FUnrealCSharpFunctionLibrary::GetBindingDirectory());

	if (PlatformFile.DirectoryExists(*BindingPath))
	{
		PlatformFile.DeleteDirectoryRecursively(*BindingPath);
	}

	BindingPath = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetUEProxyDirectory(),
	                              FUnrealCSharpFunctionLibrary::GetBindingDirectory());

	if (PlatformFile.DirectoryExists(*BindingPath))
	{
		PlatformFile.DeleteDirectoryRecursively(*BindingPath);
	}

	bIsGenerating = true;

	FileChanges.Reset();
}

void FEditorListener::OnEndGenerator()
{
	bIsGenerating = false;

	FileChanges.Reset();
}

void FEditorListener::OnCompile(const TArray<FFileChangeData>& InFileChangeData)
{
	if (!InFileChangeData.IsEmpty())
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
				FCodeAnalysis::Analysis(File);
			}
		}

		FDynamicGenerator::SetCodeAnalysisDynamicFilesMap();
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
		if (!bIsPIEPlaying && !bIsGenerating)
		{
			FCSharpCompiler::Get().Compile(FileChanges);

			FileChanges.Reset();
		}
	}
}

void FEditorListener::OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges)
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableDirectoryChanged())
		{
			if (!bIsGenerating)
			{
				static auto IgnoreDirectories = TArray<FString>
				{
					PROXY_NAME,
					TEXT("obj")
				};

				for (const auto& FileChange : InFileChanges)
				{
					if (FPaths::GetExtension(FileChange.Filename) == TEXT("cs"))
					{
						auto bIsIgnored = false;

						for (const auto& ChangedDirectory : FUnrealCSharpFunctionLibrary::GetChangedDirectories())
						{
							for (const auto& IgnoreDirectory : IgnoreDirectories)
							{
								if (FPaths::IsUnderDirectory(FileChange.Filename,
								                             FPaths::Combine(ChangedDirectory, IgnoreDirectory)))
								{
									bIsIgnored = true;

									break;
								}
							}

							if (bIsIgnored)
							{
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
}

void FEditorListener::OnAssetChanged(const TFunction<void()>& InGenerator) const
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
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
