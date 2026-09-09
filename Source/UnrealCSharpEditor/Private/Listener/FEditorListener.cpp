#include "Listener/FEditorListener.h"
#include "Widgets/SCompileProgressDialog.h"
#include "Editor.h"
#include "Engine/Blueprint.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "UObject/UObjectIterator.h"
#include "Interfaces/IMainFrameModule.h"
#include "DirectoryWatcherModule.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/ThreadHeartBeat.h"
#include "HAL/ThreadManager.h"
#include "RenderingThread.h"
#include "Rendering/SlateRenderer.h"
#include "RHI.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"
#include "Widgets/SNullWidget.h"
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

		OnEndPIEDelegateHandle = FEditorDelegates::EndPIE.AddRaw(this, &FEditorListener::OnEndPIE);

		OnCancelPIEDelegateHandle = FEditorDelegates::CancelPIE.AddRaw(this, &FEditorListener::OnCancelPIE);

		OnBeginGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.AddRaw(
			this, &FEditorListener::OnBeginGenerator);

		OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
			this, &FEditorListener::OnEndGenerator);

		OnCompileDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnCompile.AddRaw(
			this, &FEditorListener::OnCompile);

		if (GEditor != nullptr)
		{
			if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
				UUnrealCSharpEditorSetting>())
			{
				if (UnrealCSharpEditorSetting->EnableCompileOnBlueprintCompiled())
				{
					OnBlueprintCompiledDelegateHandle = GEditor->OnBlueprintCompiled().AddRaw(
						this, &FEditorListener::OnBlueprintCompiled);
				}
			}
		}

		const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<
			FAssetRegistryModule>(TEXT("AssetRegistry"));

		AssetRegistryModule.Get().OnFilesLoaded().AddRaw(this, &FEditorListener::OnFilesLoaded);

		auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

		OnMainFrameCreationFinishedDelegateHandle = MainFrameModule.OnMainFrameCreationFinished().AddRaw(
			this, &FEditorListener::OnMainFrameCreationFinished);

		auto& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(
			TEXT("DirectoryWatcher"));

		for (const auto& Directory : FUnrealCSharpFunctionLibrary::GetChangedDirectories())
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

			for (const auto& Directory : FUnrealCSharpFunctionLibrary::GetChangedDirectories())
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

		if (OnEndPIEDelegateHandle.IsValid())
		{
			FEditorDelegates::EndPIE.Remove(OnEndPIEDelegateHandle);
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
}

void FEditorListener::OnPreBeginPIE(const bool bIsSimulating)
{
	TGuardValue<bool> Guard(bIsPreparingPIE, true);

	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableCompileDirtyBlueprintsPreBeginPIE())
		{
			CompileDirtyBlueprints();

			if (!bIsGenerating && !FCSharpCompiler::Get().IsCompiling())
			{
				CompileChangedBlueprints();
			}
		}

		if (UnrealCSharpEditorSetting->EnableCompilePreBeginPIE())
		{
			RequestCompile();
		}
	}

	bIsPIEPlaying = true;

	if (FCSharpCompiler::Get().IsCompiling())
	{
		WaitForCompile();
	}

	FEngineListener::OnPreBeginPIE(bIsSimulating);
}

void FEditorListener::OnPrePIEEnded(const bool bIsSimulating)
{
	FDynamicGenerator::OnPrePIEEnded(bIsSimulating);
}

void FEditorListener::OnEndPIE(const bool)
{
	bIsPIEPlaying = false;
}

void FEditorListener::OnCancelPIE()
{
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

	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableCompileOnBlueprintCompiled())
		{
			for (TObjectIterator<UBlueprint> Iterator; Iterator; ++Iterator)
			{
				if (const auto Blueprint = *Iterator)
				{
					if (Blueprint->GeneratedClass != nullptr)
					{
						CrcCompiledSignatures.Add(FSoftObjectPath(Blueprint), Blueprint->CrcLastCompiledSignature);
					}
				}
			}
		}
	}
}

void FEditorListener::OnCompile(const bool bSucceeded)
{
	if (!bSucceeded)
	{
		CompilingFileChanges.Reset();

		return;
	}

	if (!CompilingFileChanges.IsEmpty())
	{
		TArray<FString> FileChange;

		for (const auto& Data : CompilingFileChanges)
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

	CompilingFileChanges.Reset();
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
		if (FPlatformFileManager::Get().GetPlatformFile().DeleteFile(
			*FUnrealCSharpFunctionLibrary::GetFileName(InAssetData)))
		{
			FUnrealCSharpFunctionLibrary::MarkScriptChanged();
		}
	});
}

void FEditorListener::OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const
{
	OnAssetChanged(InAssetData, [&]
	{
		if (FPlatformFileManager::Get().GetPlatformFile().DeleteFile(
			*FUnrealCSharpFunctionLibrary::GetOldFileName(InAssetData, InOldObjectPath)))
		{
			FUnrealCSharpFunctionLibrary::MarkScriptChanged();
		}

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

void FEditorListener::OnApplicationActivationStateChanged(const bool bIsActive)
{
	if (bIsActive)
	{
		if (!FileChanges.IsEmpty())
		{
			if (!bIsPIEPlaying && !bIsGenerating)
			{
				Compile();
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
					if (FPaths::GetExtension(FileChange.Filename) == CSHARP_SUFFIX.RightChop(1))
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

void FEditorListener::OnBlueprintCompiled()
{
	if (bIsPIEPlaying || bIsPreparingPIE || bIsGenerating || FCSharpCompiler::Get().IsCompiling())
	{
		return;
	}

	CompileChangedBlueprints();
}

void FEditorListener::CompileChangedBlueprints()
{
	FGeneratorCore::BeginGenerator(false);

	FUnrealCSharpFunctionLibrary::ResetScriptChanged();

	for (TObjectIterator<UBlueprint> Iterator; Iterator; ++Iterator)
	{
		if (const auto Blueprint = *Iterator)
		{
			if (Blueprint->GeneratedClass != nullptr)
			{
				if (const auto AssetData = FAssetData(Blueprint);
					FGeneratorCore::IsSupported(AssetData))
				{
					const auto SoftObjectPath = FSoftObjectPath(Blueprint);

					const auto CrcLastCompiledSignature = Blueprint->CrcLastCompiledSignature;

					const auto CrcCompiledSignature = CrcCompiledSignatures.Find(SoftObjectPath);

					if (CrcCompiledSignature == nullptr)
					{
						CrcCompiledSignatures.Add(SoftObjectPath, CrcLastCompiledSignature);

						if (!IFileManager::Get().FileExists(
							*FGeneratorCore::GetFileName(static_cast<UClass*>(Blueprint->GeneratedClass))))
						{
							FAssetGenerator::Generator(AssetData);
						}

						continue;
					}

					if (*CrcCompiledSignature != CrcLastCompiledSignature)
					{
						CrcCompiledSignatures.Add(SoftObjectPath, CrcLastCompiledSignature);

						FAssetGenerator::Generator(AssetData);
					}
				}
			}
		}
	}

	FGeneratorCore::EndGenerator(false);

	if (FUnrealCSharpFunctionLibrary::IsScriptChanged())
	{
		Compile();
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
					FUnrealCSharpFunctionLibrary::ResetScriptChanged();

					InGenerator();

					if (FUnrealCSharpFunctionLibrary::IsScriptChanged())
					{
						FCSharpCompiler::Get().Compile();
					}
				}

				FGeneratorCore::EndGenerator(false);
			}
		}
	}
}

void FEditorListener::CompileDirtyBlueprints()
{
	for (TObjectIterator<UBlueprint> Blueprint; Blueprint; ++Blueprint)
	{
		if (Blueprint->Status == BS_Dirty && !Blueprint->bBeingCompiled)
		{
			FKismetEditorUtilities::CompileBlueprint(
				*Blueprint, EBlueprintCompileOptions::SkipGarbageCollection);
		}
	}
}

bool FEditorListener::IsCompileRequired() const
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	auto bNeedCompile = false;

	const auto PublishDirectory = FUnrealCSharpFunctionLibrary::GetFullPublishDirectory();

	const auto InteropAssemblyPath = FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath();

	auto FallbackTimestamp = FDateTime::MaxValue();

	for (const auto& AssemblyPath : FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath())
	{
		if (!PlatformFile.FileExists(*AssemblyPath))
		{
			return true;
		}

		if (!FPaths::IsSamePath(AssemblyPath, InteropAssemblyPath))
		{
			FallbackTimestamp = FMath::Min(FallbackTimestamp, PlatformFile.GetTimeStamp(*AssemblyPath));
		}
	}

	for (const auto& Directory : FUnrealCSharpFunctionLibrary::GetChangedDirectories())
	{
		const auto AssemblyPath = PublishDirectory / FPaths::GetCleanFilename(Directory) + DLL_SUFFIX;

		const auto AssemblyTimestamp = PlatformFile.FileExists(*AssemblyPath)
			                               ? PlatformFile.GetTimeStamp(*AssemblyPath)
			                               : FallbackTimestamp;

		PlatformFile.IterateDirectoryRecursively(
			*Directory,
			[&](const TCHAR* InFilenameOrDirectory, const bool bIsDirectory) -> bool
			{
				if (!bIsDirectory &&
					FPaths::GetExtension(InFilenameOrDirectory) == CSHARP_SUFFIX.RightChop(1) &&
					PlatformFile.GetTimeStamp(InFilenameOrDirectory) > AssemblyTimestamp)
				{
					bNeedCompile = true;

					return false;
				}

				return true;
			});

		if (bNeedCompile)
		{
			break;
		}
	}

	return bNeedCompile;
}

void FEditorListener::RequestCompile()
{
	if (!bIsGenerating && !FCSharpCompiler::Get().IsCompiling() && IsCompileRequired())
	{
		Compile();
	}
}

void FEditorListener::Compile()
{
	if (!FileChanges.IsEmpty())
	{
		CompilingFileChanges = FileChanges;

		FCSharpCompiler::Get().Compile(FileChanges);

		FileChanges.Reset();
	}
	else
	{
		FCSharpCompiler::Get().Compile();
	}
}

void FEditorListener::TickProgressWindow(const TSharedPtr<SWindow>& InWindow)
{
#if UE_F_SLATE_APPLICATION_IS_TICKING
	if (InWindow.IsValid() && !FSlateApplication::Get().IsTicking())
#else
	if (InWindow.IsValid())
#endif
	{
		FPlatformMisc::PumpMessagesForSlowTask();

		FSlateApplication::Get().Tick();

		if (GIsRHIInitialized)
		{
			ENQUEUE_RENDER_COMMAND(CompileWaitEndFrame)([](FRHICommandListImmediate& RHICmdList)
			{
				RHICmdList.EndFrame();
			});
		}

		FSlateApplication::Get().GetRenderer()->Sync();
	}
}

void FEditorListener::WaitForCompile()
{
	const auto& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	const auto ParentWindow = MainFrameModule.GetParentWindow();

	TSharedPtr<SWindow> ProgressWindow;

	TSharedPtr<SCompileProgressDialog> ProgressDialog;

	if (FSlateApplication::Get().CanDisplayWindows())
	{
		if (ParentWindow.IsValid())
		{
			ProgressDialog = SNew(SCompileProgressDialog);

			ProgressWindow = SNew(SWindow)
				.SizingRule(ESizingRule::Autosized)
				.AutoCenter(EAutoCenter::PreferredWorkArea)
				.IsPopupWindow(true)
				.CreateTitleBar(true)
				.SupportsMaximize(false)
				.SupportsMinimize(false)
				.FocusWhenFirstShown(false)
				.ActivationPolicy(EWindowActivationPolicy::Never);

			ProgressWindow->SetContent(ProgressDialog.ToSharedRef());

			FSlateApplication::Get().AddModalWindow(ProgressWindow.ToSharedRef(), ParentWindow, true);

			ProgressWindow->ShowWindow();

			TickProgressWindow(ProgressWindow);
		}
	}

	const auto StartTime = FPlatformTime::Seconds();

	auto LastTime = StartTime;

	constexpr auto IntervalSecond = 1.0 / 60.0;

	while (FCSharpCompiler::Get().IsCompiling())
	{
		FThreadHeartBeat::Get().HeartBeat();

		if (const auto Now = FPlatformTime::Seconds();
			ProgressWindow.IsValid() &&
			ProgressDialog.IsValid() &&
			Now - LastTime >= IntervalSecond)
		{
			LastTime = Now;

			FString StatusMessage = FCSharpCompiler::Get().GetCompileProgress();

			const auto ElapsedSeconds = static_cast<int32>(Now - StartTime);

			ProgressDialog->UpdateProgress(StatusMessage, ElapsedSeconds);

			TickProgressWindow(ProgressWindow);
		}

		FPlatformProcess::SleepNoStats(0.0005f);

		FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());

		FThreadManager::Get().Tick();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
	}

	if (ProgressWindow.IsValid())
	{
		ProgressWindow->SetContent(SNullWidget::NullWidget);

		ProgressWindow->RequestDestroyWindow();

		TickProgressWindow(ProgressWindow);
	}
}
