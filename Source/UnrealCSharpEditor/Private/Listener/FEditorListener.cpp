#include "Listener/FEditorListener.h"
#include "Editor.h"
#include "Engine/Blueprint.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Misc/ScopedSlowTask.h"
#include "UObject/UObjectIterator.h"
#include "Interfaces/IMainFrameModule.h"
#include "DirectoryWatcherModule.h"
#include "HAL/PlatformFileManager.h"
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
#include "UEVersion.h"

FEditorListener::FEditorListener():
	bIsPIEPlaying(false),
	bIsPreparingPIE(false),
	bIsGenerating(false)
{
	if (!IsRunningCookCommandlet())
	{
#if UE_F_CORE_DELEGATES_GET_ON_POST_ENGINE_INIT
		OnPostEngineInitDelegateHandle = FCoreDelegates::GetOnPostEngineInit().AddRaw(
			this, &FEditorListener::OnPostEngineInit);
#else
		OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddRaw(
			this, &FEditorListener::OnPostEngineInit);
#endif

		OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &FEditorListener::OnPreBeginPIE);

		OnPrePIEEndedDelegateHandle = FEditorDelegates::PrePIEEnded.AddRaw(this, &FEditorListener::OnPrePIEEnded);

		OnCancelPIEDelegateHandle = FEditorDelegates::CancelPIE.AddRaw(this, &FEditorListener::OnCancelPIE);

		OnBeginGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.AddRaw(
			this, &FEditorListener::OnBeginGenerator);

		OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
			this, &FEditorListener::OnEndGenerator);

		OnCompileDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnCompile.AddRaw(
			this, &FEditorListener::OnCompile);

		const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<
			FAssetRegistryModule>(TEXT("AssetRegistry"));

		AssetRegistryModule.Get().OnFilesLoaded().AddRaw(this, &FEditorListener::OnFilesLoaded);

		auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

		OnMainFrameCreationFinishedDelegateHandle = MainFrameModule.OnMainFrameCreationFinished().AddRaw(
			this, &FEditorListener::OnMainFrameCreationFinished);

		auto& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(
			TEXT("DirectoryWatcher"));

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
}

FEditorListener::~FEditorListener()
{
	if (!IsRunningCookCommandlet())
	{
		if (OnBlueprintCompiledDelegateHandle.IsValid() && GEditor != nullptr)
		{
			GEditor->OnBlueprintCompiled().Remove(OnBlueprintCompiledDelegateHandle);
		}

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

		if (FSlateApplication::IsInitialized() && OnApplicationActivationStateChangedDelegateHandle.IsValid())
		{
			FSlateApplication::Get().OnApplicationActivationStateChanged().Remove(
				OnApplicationActivationStateChangedDelegateHandle);
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
#if UE_F_CORE_DELEGATES_GET_ON_POST_ENGINE_INIT
			FCoreDelegates::GetOnPostEngineInit().Remove(OnPostEngineInitDelegateHandle);
#else
			FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitDelegateHandle);
#endif
		}
	}
}

void FEditorListener::OnPostEngineInit()
{
	FCodeAnalysis::CodeAnalysis();

	FDynamicGenerator::CodeAnalysisGenerator();

	if (GEditor != nullptr)
	{
		OnBlueprintCompiledDelegateHandle = GEditor->OnBlueprintCompiled().AddRaw(
			this, &FEditorListener::OnBlueprintCompiled);
	}
}

void FEditorListener::OnBlueprintCompiled()
{
	if (!bIsPIEPlaying && !bIsPreparingPIE && !bIsGenerating && !FCSharpCompiler::Get().IsCompiling())
	{
		if (!FileChanges.IsEmpty())
		{
			FCSharpCompiler::Get().Compile(FileChanges);

			FileChanges.Reset();
		}
		else
		{
			FCSharpCompiler::Get().Compile();
		}
	}
}

void FEditorListener::OnPreBeginPIE(const bool bIsSimulating)
{
	bIsPreparingPIE = true;

	for (TObjectIterator<UBlueprint> It; It; ++It)
	{
		if (It->Status == BS_Dirty && !It->bBeingCompiled)
		{
			FKismetEditorUtilities::CompileBlueprint(*It, EBlueprintCompileOptions::SkipGarbageCollection);
		}
	}

	if (!bIsGenerating && !FCSharpCompiler::Get().IsCompiling())
	{
		auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		auto bNeedsCompile = false;

		auto OldestAssemblyTime = FDateTime::MaxValue();

		for (const auto& AssemblyPath : FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath())
		{
			if (!PlatformFile.FileExists(*AssemblyPath))
			{
				bNeedsCompile = true;

				break;
			}

			OldestAssemblyTime = FMath::Min(OldestAssemblyTime, PlatformFile.GetTimeStamp(*AssemblyPath));
		}

		if (!bNeedsCompile)
		{
			for (const auto& Directory : FUnrealCSharpFunctionLibrary::GetChangedDirectories())
			{
				PlatformFile.IterateDirectoryRecursively(
					*Directory,
					[&](const TCHAR* InFilenameOrDirectory, const bool bIsDirectory) -> bool
					{
						if (!bIsDirectory && FPaths::GetExtension(InFilenameOrDirectory) == TEXT("cs") &&
							PlatformFile.GetTimeStamp(InFilenameOrDirectory) > OldestAssemblyTime)
						{
							bNeedsCompile = true;

							return false;
						}

						return true;
					});

				if (bNeedsCompile)
				{
					break;
				}
			}
		}

		if (bNeedsCompile)
		{
			if (!FileChanges.IsEmpty())
			{
				FCSharpCompiler::Get().Compile(FileChanges);

				FileChanges.Reset();
			}
			else
			{
				FCSharpCompiler::Get().Compile();
			}
		}
	}

	bIsPIEPlaying = true;

	if (FCSharpCompiler::Get().IsCompiling())
	{
		// 阻塞等待期间弹进度框,避免被误认为编辑器卡死。
		FScopedSlowTask SlowTask(1.0f, NSLOCTEXT("UnrealCSharp", "WaitingForCSharpCompile",
		                                         "正在编译 C# 脚本并重新绑定，完成后自动进入运行..."));
		SlowTask.MakeDialog();

		while (FCSharpCompiler::Get().IsCompiling())
		{
			SlowTask.EnterProgressFrame(0.0f);

			FThreadHeartBeat::Get().HeartBeat();

			FPlatformProcess::SleepNoStats(0.0001f);

			FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());

			FThreadManager::Get().Tick();

			FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		}
	}

	FEngineListener::OnPreBeginPIE(bIsSimulating);
	bIsPreparingPIE = false;
}

void FEditorListener::OnPrePIEEnded(const bool bIsSimulating)
{
	FDynamicGenerator::OnPrePIEEnded(bIsSimulating);
}

void FEditorListener::OnCancelPIE()
{
	FEngineListener::OnCancelPIE();

	bIsPreparingPIE = false;
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

		if (UnrealCSharpEditorSetting->EnableDeleteBindingDirectory())
		{
			if (const auto UEBindingDirectory = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetUEProxyDirectory(),
			                                                    FUnrealCSharpFunctionLibrary::GetBindingDirectory());
				PlatformFile.DirectoryExists(*UEBindingDirectory))
			{
				PlatformFile.DeleteDirectoryRecursively(*UEBindingDirectory);
			}

			if (const auto GameBindingDirectory = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGameProxyDirectory(),
			                                                      FUnrealCSharpFunctionLibrary::GetBindingDirectory());
				PlatformFile.DirectoryExists(*GameBindingDirectory))
			{
				PlatformFile.DeleteDirectoryRecursively(*GameBindingDirectory);
			}
		}
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

	AssetRegistryModule.Get().OnAssetUpdatedOnDisk().AddRaw(this, &FEditorListener::OnAssetUpdatedOnDisk);
}

void FEditorListener::OnAssetAdded(const FAssetData& InAssetData) const
{
	OnAssetChanged(InAssetData, [&]
	{
		FAssetGenerator::Generator(InAssetData);
	});
}

void FEditorListener::OnAssetRemoved(const FAssetData& InAssetData) const
{
	OnAssetChanged(InAssetData, [&]
	{
		FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			*FUnrealCSharpFunctionLibrary::GetFileName(InAssetData));
	});
}

void FEditorListener::OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const
{
	OnAssetChanged(InAssetData, [&]
	{
		FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(
			*FUnrealCSharpFunctionLibrary::GetOldFileName(InAssetData, InOldObjectPath));

		FAssetGenerator::Generator(InAssetData);
	});
}

void FEditorListener::OnAssetUpdatedOnDisk(const FAssetData& InAssetData) const
{
	OnAssetChanged(InAssetData, [&]
	{
		FAssetGenerator::Generator(InAssetData);
	});
}

void FEditorListener::OnMainFrameCreationFinished(const TSharedPtr<SWindow>, bool)
{
	OnApplicationActivationStateChangedDelegateHandle = FSlateApplication::Get().OnApplicationActivationStateChanged().
		AddRaw(this, &FEditorListener::OnApplicationActivationStateChanged);
}

void FEditorListener::OnApplicationActivationStateChanged(const bool IsActive)
{
	if (IsActive)
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

void FEditorListener::OnAssetChanged(const FAssetData& InAssetData, const TFunction<void()>& InGenerator) const
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableAssetChanged())
		{
			if (!bIsPIEPlaying && !bIsGenerating)
			{
				FGeneratorCore::BeginGenerator(false);

				if (FGeneratorCore::IsSupported(InAssetData))
				{
					InGenerator();

					FCSharpCompiler::Get().Compile();
				}

				FGeneratorCore::EndGenerator(false);
			}
		}
	}
}
