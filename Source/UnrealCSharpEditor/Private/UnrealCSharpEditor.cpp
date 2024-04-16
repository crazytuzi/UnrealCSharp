// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpEditor.h"
#include "FAssetGenerator.h"
#include "FClassGenerator.h"
#include "FCSharpCompiler.h"
#include "FGeneratorCore.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "FSolutionGenerator.h"
#include "FBindingClassGenerator.h"
#include "FBindingEnumGenerator.h"
#include "UnrealCSharpEditorStyle.h"
#include "UnrealCSharpEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Internationalization/Culture.h"
#include "FCodeAnalysis.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Misc/ScopedSlowTask.h"
#include "Dynamic/FDynamicGenerator.h"
#include "ToolBar/UnrealCSharpToolBar.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorModule"

void FUnrealCSharpEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FUnrealCSharpEditorStyle::Initialize();

	FUnrealCSharpEditorStyle::ReloadTextures();

	FUnrealCSharpEditorCommands::Register();

	UnrealCSharpToolBar = MakeShared<FUnrealCSharpToolBar>();

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUnrealCSharpEditorModule::RegisterMenus));

	CodeAnalysisConsoleCommand = MakeUnique<FAutoConsoleCommand>(
		TEXT("UnrealCSharp.Editor.CodeAnalysis"), TEXT(""),
		FConsoleCommandDelegate::CreateLambda(
			[]()
			{
				FCodeAnalysis::CodeAnalysis();
			}));

	SolutionGeneratorConsoleCommand = MakeUnique<FAutoConsoleCommand>(
		TEXT("UnrealCSharp.Editor.SolutionGenerator"), TEXT(""),
		FConsoleCommandDelegate::CreateLambda(
			[]()
			{
				FSolutionGenerator::Generator();
			}));

	CompileConsoleCommand = MakeUnique<FAutoConsoleCommand>(
		TEXT("UnrealCSharp.Editor.Compile"), TEXT(""),
		FConsoleCommandDelegate::CreateLambda(
			[]()
			{
				FCSharpCompiler::Get().Compile([]()
				{
				});
			}));

	GeneratorConsoleCommand = MakeUnique<FAutoConsoleCommand>(
		TEXT("UnrealCSharp.Editor.Generator"), TEXT(""),
		FConsoleCommandDelegate::CreateLambda(
			[]()
			{
				Generator();
			}));

	if (IsRunningCookCommandlet())
	{
		Generator();
	}
}

void FUnrealCSharpEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUnrealCSharpEditorStyle::Shutdown();

	FUnrealCSharpEditorCommands::Unregister();
}

void FUnrealCSharpEditorModule::PluginButtonClicked() const
{
	Generator();
}

void FUnrealCSharpEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	if (UnrealCSharpToolBar.IsValid())
	{
		UnrealCSharpToolBar->Initialize();
	}
}

void FUnrealCSharpEditorModule::Generator()
{
	FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.Broadcast();

	static FString DefaultCultureName = TEXT("en");

	const auto CurrentCultureName = FInternationalization::Get().GetCurrentCulture().Get().GetName();

	if (!CurrentCultureName.Equals(DefaultCultureName))
	{
		FInternationalization::Get().SetCurrentCulture(DefaultCultureName);
	}

	FScopedSlowTask SlowTask(12, LOCTEXT("GeneratingCodeAction", "Generating Code Action"));

	SlowTask.MakeDialog();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Code Analysis"));

	FCodeAnalysis::CodeAnalysis();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Code Analysis Generator"));

	FDynamicGenerator::CodeAnalysisGenerator();

	FGeneratorCore::BeginGenerator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Class Generator"));

	FClassGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Struct Generator"));

	FStructGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Enum Generator"));

	FEnumGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Asset Generator"));

	FAssetGenerator::Generator();

	FGeneratorCore::EndGenerator();

	if (!CurrentCultureName.Equals(DefaultCultureName))
	{
		FInternationalization::Get().SetCurrentCulture(CurrentCultureName);
	}

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Solution Generator"));

	FSolutionGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "BindingClass Generator"));

	FBindingClassGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "BindingEnum Generator"));

	FBindingEnumGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Garbage Collect"));

	CollectGarbage(RF_NoFlags, true);

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Compiler"));

	FCSharpCompiler::Get().ImmediatelyCompile();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Completion"));

	FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Broadcast();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpEditorModule, UnrealCSharpEditor)
