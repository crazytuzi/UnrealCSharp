#include "ToolBar/UnrealCSharpBlueprintToolBar.h"
#include "BlueprintEditorModule.h"
#include "SourceCodeNavigation.h"
#include "FCodeAnalysis.h"
#include "UnrealCSharpEditorCommands.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"

#define LOCTEXT_NAMESPACE "UnrealCSharpBlueprintToolBar"

FUnrealCSharpBlueprintToolBar::FUnrealCSharpBlueprintToolBar()
	: CommandList(MakeShared<FUICommandList>())
{
	BuildAction();
}

void FUnrealCSharpBlueprintToolBar::Initialize()
{
	auto& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");

	BlueprintEditorModule.GetMenuExtensibilityManager()->GetExtenderDelegates().Add(
		FAssetEditorExtender::CreateLambda(
			[&](const TSharedRef<FUICommandList> InCommandList, const TArray<UObject*> InContextSensitiveObjects)
			{
				return GenerateBlueprintExtender(InContextSensitiveObjects.IsEmpty()
					                                 ? nullptr
					                                 : Cast<UBlueprint>(InContextSensitiveObjects[0]));
			}));

	SetCodeAnalysisOverrideFilesMap();

	OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
		this, &FUnrealCSharpBlueprintToolBar::OnEndGenerator);
}

void FUnrealCSharpBlueprintToolBar::Deinitialize()
{
	if (OnEndGeneratorDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Remove(OnEndGeneratorDelegateHandle);
	}
}

void FUnrealCSharpBlueprintToolBar::OnEndGenerator()
{
	SetCodeAnalysisOverrideFilesMap();
}

void FUnrealCSharpBlueprintToolBar::BuildAction()
{
	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenFile,
		FExecuteAction::CreateLambda([this]
		{
			if (const auto OverrideFile = GetOverrideFile(); !OverrideFile.IsEmpty())
			{
				if (IFileManager::Get().FileExists(*OverrideFile))
				{
					FSourceCodeNavigation::OpenSourceFile(OverrideFile);
				}
			}
		}), FCanExecuteAction());

	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().CodeAnalysis,
		FExecuteAction::CreateLambda([this]
		{
			if (const auto OverrideFile = GetOverrideFile(); !OverrideFile.IsEmpty())
			{
				if (IFileManager::Get().FileExists(*OverrideFile))
				{
					FCodeAnalysis::Analysis(OverrideFile);
				}
			}
		}), FCanExecuteAction());

	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().OverrideBlueprint,
		FExecuteAction::CreateLambda([this]
		{
			if (Blueprint.IsValid())
			{
				const auto Content = FString::Printf(TEXT(
					"using %s;\n"
					"using %s;\n\n"
					"namespace %s\n"
					"{\n"
					"\t[Override]\n"
					"\tpublic partial class %s\n"
					"\t{\n"
					"\t\tprivate %s()\n"
					"\t\t{\n"
					"\t\t}\n\n"
					"\t\t[Override]\n"
					"\t\tpublic override void ReceiveBeginPlay()\n"
					"\t\t{\n"
					"\t\t\tbase.ReceiveBeginPlay();\n"
					"\t\t}\n\n"
					"\t\t[Override]\n"
					"\t\tpublic override void ReceiveEndPlay(EEndPlayReason EndPlayReason)\n"
					"\t\t{\n"
					"\t\t\tbase.ReceiveEndPlay(EndPlayReason);\n"
					"\t\t}\n"
					"\t}\n"
					"}"
				),
				                                     *COMBINE_NAMESPACE(NAMESPACE_SCRIPT, FString(TEXT("CoreUObject"))),
				                                     *COMBINE_NAMESPACE(NAMESPACE_SCRIPT, FString(TEXT("Engine"))),
				                                     *FUnrealCSharpFunctionLibrary::GetClassNameSpace(
					                                     Blueprint->GeneratedClass),
				                                     *FUnrealCSharpFunctionLibrary::GetFullClass(
					                                     Blueprint->GeneratedClass),
				                                     *FUnrealCSharpFunctionLibrary::GetFullClass(
					                                     Blueprint->GeneratedClass));

				if (const auto FileName = GetFileName(); FUnrealCSharpFunctionLibrary::SaveStringToFile(
					FileName, Content))
				{
					const auto Class = FString::Printf(TEXT(
						"%s.%s"
					),
					                                   *FUnrealCSharpFunctionLibrary::GetClassNameSpace(
						                                   Blueprint->GeneratedClass),
					                                   *FUnrealCSharpFunctionLibrary::GetFullClass(
						                                   Blueprint->GeneratedClass));

					DynamicOverrideFilesMap.Add(Class, FileName);
				}
			}
		}), FCanExecuteAction());
}

TSharedRef<FExtender> FUnrealCSharpBlueprintToolBar::GenerateBlueprintExtender(UBlueprint* InBlueprint)
{
	TSharedRef<FExtender> Extender(new FExtender());

	const auto ExtensionDelegate = FToolBarExtensionDelegate::CreateLambda(
		[this, InBlueprint](FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.BeginSection(NAME_None);

			ToolbarBuilder.AddComboButton(
				FUIAction(),
				FOnGetContent::CreateLambda([&]()
				{
					Blueprint = InBlueprint;

					const FUnrealCSharpEditorCommands& Commands = FUnrealCSharpEditorCommands::Get();

					FMenuBuilder MenuBuilder(true, CommandList);

					if (HasOverrideFile())
					{
						MenuBuilder.AddMenuEntry(Commands.OpenFile, NAME_None,
						                         LOCTEXT("OpenFile", "Open File"));

						MenuBuilder.AddMenuEntry(Commands.CodeAnalysis, NAME_None,
						                         LOCTEXT("CodeAnalysis", "Code Analysis"));
					}
					else
					{
						MenuBuilder.AddMenuEntry(Commands.OverrideBlueprint, NAME_None,
						                         LOCTEXT("OverrideBlueprint", "Override Blueprint"));
					}

					return MenuBuilder.MakeWidget();
				}),
				LOCTEXT("UnrealCSharpEditor_Label", "UnrealCSharp"),
				LOCTEXT("UnrealCSharpEditor_ToolTip", "UnrealCSharp"),
				FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction")
			);

			ToolbarBuilder.EndSection();
		});

	Extender->AddToolBarExtension("Debugging", EExtensionHook::After, CommandList, ExtensionDelegate);

	return Extender;
}

void FUnrealCSharpBlueprintToolBar::SetCodeAnalysisOverrideFilesMap()
{
	CodeAnalysisOverrideFilesMap = FUnrealCSharpFunctionLibrary::LoadFileToString(FString::Printf(TEXT(
		"%s/%s.json"
	),
		*FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		*OVERRIDE_FILE
	));
}

bool FUnrealCSharpBlueprintToolBar::HasOverrideFile() const
{
	if (Blueprint.IsValid())
	{
		const auto Class = FString::Printf(TEXT(
			"%s.%s"
		),
		                                   *FUnrealCSharpFunctionLibrary::GetClassNameSpace(Blueprint->GeneratedClass),
		                                   *FUnrealCSharpFunctionLibrary::GetFullClass(Blueprint->GeneratedClass));

		return CodeAnalysisOverrideFilesMap.Contains(Class) || DynamicOverrideFilesMap.Contains(Class);
	}

	return false;
}

FString FUnrealCSharpBlueprintToolBar::GetOverrideFile() const
{
	if (Blueprint.IsValid())
	{
		const auto Class = FString::Printf(TEXT(
			"%s.%s"
		),
		                                   *FUnrealCSharpFunctionLibrary::GetClassNameSpace(Blueprint->GeneratedClass),
		                                   *FUnrealCSharpFunctionLibrary::GetFullClass(Blueprint->GeneratedClass));

		if (const auto FoundOverrideFile = CodeAnalysisOverrideFilesMap.Find(Class))
		{
			return *FoundOverrideFile;
		}

		if (const auto FoundOverrideFile = DynamicOverrideFilesMap.Find(Class))
		{
			return *FoundOverrideFile;
		}
	}

	return {};
}

FString FUnrealCSharpBlueprintToolBar::GetFileName() const
{
	if (Blueprint.IsValid())
	{
		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(Blueprint->GeneratedClass);

		auto DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGameDirectory(), ModuleName);

		return FPaths::Combine(DirectoryName, Blueprint->GeneratedClass->GetName()) + CSHARP_SUFFIX;
	}

	return {};
}

#undef LOCTEXT_NAMESPACE
