﻿#include "NewClass/DynamicNewClassUtils.h"
#include "Interfaces/IMainFrameModule.h"
#include "Misc/FileHelper.h"
#include "AddToProjectConfig.h"
#include "Blueprint/UserWidget.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "NewCLass/SDynamicNewClassDialog.h"

#define LOCTEXT_NAMESPACE "DynamicNewClassUtils"

void FDynamicNewClassUtils::OpenAddDynamicClassToProjectDialog(const FString& InInitialPath)
{
	const auto WindowTitle = LOCTEXT("AddCodeWindowHeader_DynamicCppClass", "Add Dynamic C# Class");

	const auto WindowSize = FVector2D(940, 540);

	const auto AddCodeWindow =
		SNew(SWindow)
		.Title(WindowTitle)
		.ClientSize(WindowSize)
		.SizingRule(ESizingRule::FixedSize)
		.SupportsMinimize(false)
		.SupportsMaximize(false);

	const auto NewClassDialog =
		SNew(SDynamicNewClassDialog)
		.ParentWindow(AddCodeWindow)
		.InitialPath(InInitialPath);

	AddCodeWindow->SetContent(NewClassDialog);

	const auto MainFrameModule = FModuleManager::LoadModulePtr<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameModule == nullptr)
	{
		return;
	}

	if (const auto ParentWindow = MainFrameModule->GetParentWindow())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(AddCodeWindow, ParentWindow.ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(AddCodeWindow);
	}
}

TArray<FProjectContent> FDynamicNewClassUtils::GetProjectContent()
{
	TArray CustomProjectsName = {FUnrealCSharpFunctionLibrary::GetGameName()};

	CustomProjectsName.Append(FUnrealCSharpFunctionLibrary::GetCustomProjectsName());

	TArray<FProjectContent> ProjectContents;

	for (const auto& ProjectName : CustomProjectsName)
	{
		ProjectContents.Add(FProjectContent(ProjectName,
		                                    FUnrealCSharpFunctionLibrary::GetFullScriptDirectory() /
		                                    ProjectName));
	}

	return ProjectContents;
}

void FDynamicNewClassUtils::GetDynamicClassContent(const UClass* InParentClass, const FString& InNewClassName,
                                                   FString& OutContent)
{
	OutContent.Empty();

	if (InParentClass == nullptr)
	{
		return;
	}

	const auto AncestorClass = GetAncestorClass(InParentClass);

	if (AncestorClass == nullptr)
	{
		return;
	}

	const auto bIsCppParentClass = InParentClass->IsNative() &&
		!FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(InParentClass);

	const auto ParentNamespace = FUnrealCSharpFunctionLibrary::GetClassNameSpace(InParentClass);

	const auto ParentClassName = (bIsCppParentClass ? InParentClass->GetPrefixCPP() : TEXT("")) +
		InParentClass->GetName();

	const auto GeneratedClassName = FString::Printf(TEXT(
		"%s%s"
	),
	                                                bIsCppParentClass && !InNewClassName.EndsWith(TEXT("_C"))
		                                                ? InParentClass->GetPrefixCPP()
		                                                : TEXT(""),
	                                                *InNewClassName
	);

	const auto TemplateFileName = FUnrealCSharpFunctionLibrary::GetPluginTemplateDynamicFileName(AncestorClass);

	FFileHelper::LoadFileToString(OutContent, *TemplateFileName);

	AddNamespace(ParentNamespace, OutContent);

	OutContent.ReplaceInline(*FString::Printf(TEXT(
		                         ": %s"
	                         ),
	                                          *FUnrealCSharpFunctionLibrary::GetFullClass(AncestorClass)
	                         ),
	                         *FString::Printf(TEXT(
		                         ": %s"
	                         ),
	                                          *ParentClassName
	                         )
	);

	const auto OldClassFullName = FString::Printf(TEXT(
		"%s%s%s"
	),
	                                              AncestorClass->GetPrefixCPP(),
	                                              *DYNAMIC_CLASS_DEFAULT_PREFIX,
	                                              *AncestorClass->GetName()
	);

	OutContent.ReplaceInline(*FString::Printf(TEXT(
		                         "%s"
	                         ),
	                                          *OldClassFullName
	                         ),
	                         *FString::Printf(TEXT(
		                         "%s"
	                         ),
	                                          *GeneratedClassName
	                         )
	);
}

FString FDynamicNewClassUtils::GetAssetGeneratedClassName(const FAssetData& InAssetData)
{
	FString GeneratedClass;

	InAssetData.GetTagValue(TEXT("GeneratedClass"), GeneratedClass);

	int32 DotIndex;

	GeneratedClass.FindLastChar('.', DotIndex);

	if (DotIndex != INDEX_NONE)
	{
		GeneratedClass = GeneratedClass.Mid(DotIndex + 1).TrimEnd();

		GeneratedClass.RemoveFromEnd(TEXT("'"));
	}

	return GeneratedClass;
}

FString FNewClassInfo::GetClassNameCPP() const
{
	switch (ClassType)
	{
	case EClassType::UObject:
		{
			return BaseClass ? BaseClass->GetName() : TEXT("");
		}
	case EClassType::EmptyCpp:
		{
			return TEXT("");
		}
	case EClassType::SlateWidget:
		{
			return TEXT("CompoundWidget");
		}
	case EClassType::SlateWidgetStyle:
		{
			return TEXT("SlateWidgetStyle");
		}
	case EClassType::UInterface:
		{
			return TEXT("Interface");
		}
	default:
		break;
	}

	return TEXT("");
}

FText FNewClassInfo::GetClassName() const
{
	switch (ClassType)
	{
	case EClassType::UObject:
		{
			return BaseClass ? BaseClass->GetDisplayNameText() : FText::GetEmpty();
		}
	case EClassType::EmptyCpp:
		{
			return LOCTEXT("NoParentClass", "None");
		}
	case EClassType::SlateWidget:
		{
			return LOCTEXT("SlateWidgetParentClass", "Slate Widget");
		}
	case EClassType::SlateWidgetStyle:
		{
			return LOCTEXT("SlateWidgetStyleParentClass", "Slate Widget Style");
		}
	case EClassType::UInterface:
		{
			return LOCTEXT("UInterfaceParentClass", "Unreal Interface");
		}
	default:
		break;
	}

	return FText::GetEmpty();
}

FText FNewClassInfo::GetClassDescription(const bool bFullDescription) const
{
	switch (ClassType)
	{
	case EClassType::UObject:
		{
			if (BaseClass)
			{
				auto ClassDescription = BaseClass->GetToolTipText(!bFullDescription).ToString();

				if (!bFullDescription)
				{
					if (auto FullStopIndex = 0; ClassDescription.FindChar('.', FullStopIndex))
					{
						ClassDescription.LeftInline(FullStopIndex + 1,
#if UE_F_STRING_LEFT_CHOP_IN_LINE_E_ALLOW_SHRINKING
						                            EAllowShrinking::No
#else
						                            false
#endif
						);
					}

					ClassDescription.ReplaceInline(TEXT("\n"), TEXT(" "), ESearchCase::CaseSensitive);
				}

				return FText::FromString(ClassDescription);
			}
		}
		break;
	case EClassType::EmptyCpp:
		{
			return LOCTEXT("EmptyClassDescription", "An empty C++ class with a default constructor and destructor.");
		}
	case EClassType::SlateWidget:
		{
			return LOCTEXT("SlateWidgetClassDescription", "A custom Slate widget, deriving from SCompoundWidget.");
		}
	case EClassType::SlateWidgetStyle:
		{
			return LOCTEXT("SlateWidgetStyleClassDescription",
			               "A custom Slate widget style, deriving from FSlateWidgetStyle, along with its associated UObject wrapper class.");
		}
	case EClassType::UInterface:
		{
			return LOCTEXT("UInterfaceClassDescription",
			               "A UObject Interface class, to be implemented by other UObject-based classes.");
		}
	default:
		break;
	}

	return FText::GetEmpty();
}

UClass* FDynamicNewClassUtils::GetAncestorClass(const UClass* InClass)
{
	if (!InClass)
	{
		return nullptr;
	}

	static TArray TemplateClasses =
	{
		AActor::StaticClass(),
		UActorComponent::StaticClass(),
		UUserWidget::StaticClass(),
		UObject::StaticClass()
	};

	for (const auto& TemplateClass : TemplateClasses)
	{
		if (InClass->IsChildOf(TemplateClass))
		{
			return TemplateClass;
		}
	}

	return nullptr;
}

void FDynamicNewClassUtils::AddNamespace(const FString& InNamespace, FString& OutContent)
{
	if (OutContent.IsEmpty() || InNamespace.IsEmpty())
	{
		return;
	}

	TSet<FString> Namespaces;

	TArray<FString> Lines;

	const FString Using = TEXT("using");

	const FString NameSpace = TEXT("namespace");

	OutContent.ParseIntoArrayLines(Lines, false);

	for (const auto& Line : Lines)
	{
		if (auto TrimmedLine = Line.TrimStartAndEnd(); TrimmedLine.StartsWith(Using))
		{
			auto Path = TrimmedLine
			            .RightChop(Using.Len())
			            .LeftChop(1)
			            .TrimStartAndEnd();

			if (Path != DYNAMIC_CLASS_DEFAULT_NAMESPACE)
			{
				Namespaces.Add(Path);
			}
		}
		else if (TrimmedLine.StartsWith(NameSpace))
		{
			const auto Path = TrimmedLine
			                  .RightChop(NameSpace.Len())
			                  .TrimStartAndEnd();

			Namespaces.Add(Path);

			break;
		}
	}

	if (!Namespaces.Contains(InNamespace))
	{
		OutContent.ReplaceInline(
			*FString::Printf(TEXT(
				"%s %s;"
			),
			                 *Using,
			                 *DYNAMIC_CLASS_DEFAULT_NAMESPACE
			),
			*FString::Printf(TEXT(
				"%s %s;"
			),
			                 *Using,
			                 *InNamespace
			)
		);
	}
	else
	{
		OutContent.ReplaceInline(
			*FString::Printf(TEXT(
				"%s %s;%s"
			),
			                 *Using,
			                 *DYNAMIC_CLASS_DEFAULT_NAMESPACE,
			                 LINE_TERMINATOR
			),
			TEXT("")
		);
	}
}

#undef LOCTEXT_NAMESPACE
