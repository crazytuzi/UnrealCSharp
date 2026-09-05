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
		if (GEditor != nullptr)
		{
			if (OnBlueprintCompiledDelegateHandle.IsValid())
			{
				GEditor->OnBlueprintCompiled().Remove(OnBlueprintCompiledDelegateHandle);
			}

			if (OnBlueprintPreCompileDelegateHandle.IsValid())
			{
				GEditor->OnBlueprintPreCompile().Remove(OnBlueprintPreCompileDelegateHandle);
			}
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
		OnBlueprintPreCompileDelegateHandle = GEditor->OnBlueprintPreCompile().AddRaw(
			this, &FEditorListener::OnBlueprintPreCompile);

		OnBlueprintCompiledDelegateHandle = GEditor->OnBlueprintCompiled().AddRaw(
			this, &FEditorListener::OnBlueprintCompiled);
	}
}

void FEditorListener::OnBlueprintPreCompile(UBlueprint* InBlueprint)
{
	if (InBlueprint != nullptr && !PendingCompiledBlueprints.Contains(InBlueprint))
	{
		PendingCompiledBlueprints.Add(InBlueprint, GetClassSignature(InBlueprint->GeneratedClass));
	}
}

void FEditorListener::OnBlueprintCompiled()
{
	if (!bIsPIEPlaying && !bIsPreparingPIE && !bIsGenerating && !FCSharpCompiler::Get().IsCompiling())
	{
		GeneratePendingCompiledBlueprints();

		if (FCSharpCompiler::Get().IsCompiling())
		{
			return;
		}

		if (!FileChanges.IsEmpty())
		{
			FCSharpCompiler::Get().Compile(FileChanges);

			FileChanges.Reset();
		}
		else if (IsScriptOutOfDate())
		{
			FCSharpCompiler::Get().Compile();
		}
	}
}

bool FEditorListener::IsScriptOutOfDate()
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	for (const auto& AssemblyPath : FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath())
	{
		if (!PlatformFile.FileExists(*AssemblyPath))
		{
			return true;
		}
	}

	const auto BuildStampPath = FUnrealCSharpFunctionLibrary::GetBuildStampPath();

	if (!PlatformFile.FileExists(*BuildStampPath))
	{
		return true;
	}

	const auto BuildStampTime = PlatformFile.GetTimeStamp(*BuildStampPath);

	auto bNeedsCompile = false;

	for (const auto& Directory : FUnrealCSharpFunctionLibrary::GetChangedDirectories())
	{
		PlatformFile.IterateDirectoryRecursively(
			*Directory,
			[&](const TCHAR* InFilenameOrDirectory, const bool bIsDirectory) -> bool
			{
				if (!bIsDirectory && FPaths::GetExtension(InFilenameOrDirectory) == TEXT("cs"))
				{
					FString NormalizedPath(InFilenameOrDirectory);

					NormalizedPath.ReplaceInline(TEXT("\\"), TEXT("/"));

					if (NormalizedPath.Contains(TEXT("/obj/")) || NormalizedPath.Contains(TEXT("/bin/")))
					{
						return true;
					}

					if (PlatformFile.GetTimeStamp(InFilenameOrDirectory) > BuildStampTime)
					{
						bNeedsCompile = true;

						return false;
					}
				}

				return true;
			});

		if (bNeedsCompile)
		{
			break;
		}
	}

	return bNeedsCompile;
}

void FEditorListener::OnPreBeginPIE(const bool bIsSimulating)
{
	bIsPreparingPIE = true;
	bool bBpCompile = false;
	for (TObjectIterator<UBlueprint> It; It; ++It)
	{
		if (It->Status == BS_Dirty && !It->bBeingCompiled)
		{
			FKismetEditorUtilities::CompileBlueprint(*It, EBlueprintCompileOptions::SkipGarbageCollection);
			bBpCompile = true;
		}
	}

	if (!bIsGenerating && !FCSharpCompiler::Get().IsCompiling() && bBpCompile)
	{
		GeneratePendingCompiledBlueprints();

		if (!FCSharpCompiler::Get().IsCompiling() && IsScriptOutOfDate())
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
		FScopedSlowTask SlowTask(1.0f, NSLOCTEXT("UnrealCSharp", "WaitingForCSharpCompile",
		                                         "Compiling C# scripts, PIE will start automatically when finished..."));
		SlowTask.MakeDialog();

		auto LastFraction = 0.0f;

		while (FCSharpCompiler::Get().IsCompiling())
		{
			FString ProgressMessage;

			auto Fraction = 0.0f;

			FCSharpCompiler::Get().GetCompileProgress(ProgressMessage, Fraction);

			const auto DeltaFraction = FMath::Max(0.0f, Fraction - LastFraction);

			LastFraction = FMath::Max(LastFraction, Fraction);

			SlowTask.EnterProgressFrame(DeltaFraction,
			                            ProgressMessage.IsEmpty()
				                            ? FText::GetEmpty()
				                            : FText::FromString(ProgressMessage));

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
		if (const auto FileName = FUnrealCSharpFunctionLibrary::GetFileName(InAssetData);
			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FileName))
		{
			FUnrealCSharpFunctionLibrary::MarkScriptFileChanged();
		}
	});
}

void FEditorListener::OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const
{
	OnAssetChanged(InAssetData, [&]
	{
		if (const auto OldFileName = FUnrealCSharpFunctionLibrary::GetOldFileName(InAssetData, InOldObjectPath);
			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*OldFileName))
		{
			FUnrealCSharpFunctionLibrary::MarkScriptFileChanged();
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
					FUnrealCSharpFunctionLibrary::ResetScriptFileChanged();

					InGenerator();

					if (FUnrealCSharpFunctionLibrary::HasScriptFileChanged())
					{
						FCSharpCompiler::Get().Compile();
					}
				}

				FGeneratorCore::EndGenerator(false);
			}
		}
	}
}

void FEditorListener::GeneratePendingCompiledBlueprints()
{
	if (PendingCompiledBlueprints.IsEmpty())
	{
		return;
	}

	TMap<TWeakObjectPtr<UBlueprint>, FString> Blueprints;

	Swap(Blueprints, PendingCompiledBlueprints);

	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (!UnrealCSharpEditorSetting->EnableAssetChanged())
		{
			return;
		}
	}

	TArray<UBlueprint*> ChangedBlueprints;

	for (const auto& [Blueprint, PreviousSignature] : Blueprints)
	{
		if (Blueprint.IsValid() && Blueprint->GeneratedClass != nullptr && Blueprint->GetOutermost() != GetTransientPackage())
		{
			if (GetClassSignature(Blueprint->GeneratedClass) != PreviousSignature)
			{
				ChangedBlueprints.Add(Blueprint.Get());
			}
		}
	}

	if (ChangedBlueprints.IsEmpty())
	{
		return;
	}

	FGeneratorCore::BeginGenerator(false);

	FUnrealCSharpFunctionLibrary::ResetScriptFileChanged();

	for (const auto Blueprint : ChangedBlueprints)
	{
		if (const FAssetData AssetData(Blueprint); FGeneratorCore::IsSupported(AssetData))
		{
			FAssetGenerator::Generator(AssetData);
		}
	}

	if (FUnrealCSharpFunctionLibrary::HasScriptFileChanged())
	{
		FCSharpCompiler::Get().Compile();
	}

	FGeneratorCore::EndGenerator(false);
}

// GetCPPType asserts on half-built classes (pre-compile skeleton / stale generated class):
// delegate SignatureFunction, struct Struct or object PropertyClass may still be null.
static FString GetSafeCPPType(const FProperty* InProperty)
{
	if (const auto DelegateProperty = CastField<FDelegateProperty>(InProperty))
	{
		return DelegateProperty->SignatureFunction != nullptr
			       ? InProperty->GetCPPType()
			       : InProperty->GetClass()->GetName();
	}

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(InProperty))
	{
		return MulticastDelegateProperty->SignatureFunction != nullptr
			       ? InProperty->GetCPPType()
			       : InProperty->GetClass()->GetName();
	}

	if (const auto StructProperty = CastField<FStructProperty>(InProperty))
	{
		return StructProperty->Struct != nullptr
			       ? InProperty->GetCPPType()
			       : InProperty->GetClass()->GetName();
	}

	if (const auto ObjectProperty = CastField<FObjectPropertyBase>(InProperty))
	{
		return ObjectProperty->PropertyClass != nullptr
			       ? InProperty->GetCPPType()
			       : InProperty->GetClass()->GetName();
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(InProperty))
	{
		return FString::Printf(TEXT("TArray<%s>"), *GetSafeCPPType(ArrayProperty->Inner));
	}

	if (const auto SetProperty = CastField<FSetProperty>(InProperty))
	{
		return FString::Printf(TEXT("TSet<%s>"), *GetSafeCPPType(SetProperty->ElementProp));
	}

	if (const auto MapProperty = CastField<FMapProperty>(InProperty))
	{
		return FString::Printf(TEXT("TMap<%s,%s>"),
		                       *GetSafeCPPType(MapProperty->KeyProp),
		                       *GetSafeCPPType(MapProperty->ValueProp));
	}

	return InProperty->GetCPPType();
}

FString FEditorListener::GetClassSignature(const UClass* InClass)
{
	if (InClass == nullptr)
	{
		return {};
	}

	TStringBuilder<1024> Builder;

	for (TFieldIterator<FProperty> It(InClass, EFieldIteratorFlags::ExcludeSuper); It; ++It)
	{
		Builder << It->GetFName() << TEXT(':') << GetSafeCPPType(*It) << TEXT(';');
	}

	for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::ExcludeSuper); It; ++It)
	{
		Builder << It->GetFName() << TEXT('(');

		for (TFieldIterator<FProperty> ParamIt(*It); ParamIt; ++ParamIt)
		{
			Builder << ParamIt->GetFName() << TEXT(':') << GetSafeCPPType(*ParamIt) << TEXT(',');
		}

		Builder << TEXT(");");
	}

	return Builder.ToString();
}
