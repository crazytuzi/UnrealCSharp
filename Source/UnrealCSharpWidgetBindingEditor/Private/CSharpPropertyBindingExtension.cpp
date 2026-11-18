#include "CSharpPropertyBindingExtension.h"

#include "CSharpWidgetBinding.h"
#include "CSharpWidgetBlueprintExtension.h"
#include "Components/Widget.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "K2Node_CSharpMemberBase.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "PropertyHandle.h"
#include "Reflection/FClassReflection.h"
#include "ScopedTransaction.h"
#include "Styling/AppStyle.h"
#include "WidgetBlueprint.h"

#define LOCTEXT_NAMESPACE "CSharpPropertyBindingExtension"

bool FCSharpPropertyBindingExtension::CanExtend(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
                                                TSharedPtr<const IPropertyHandle> PropertyHandle) const
{
	if (WidgetBlueprint == nullptr || Widget == nullptr || !PropertyHandle.IsValid() ||
		UCSharpWidgetBlueprintExtension::GetWidgetKey(WidgetBlueprint, Widget).IsNone() ||
		FindDelegateProperty(Widget, PropertyHandle) == nullptr)
	{
		return false;
	}

	auto bHasOverrideClass = false;

	UK2Node_CSharpMemberBase::WithScriptDomain([&]
	{
		for (auto Class = WidgetBlueprint->GeneratedClass.Get(); Class != nullptr; Class = Class->GetSuperClass())
		{
			if (FCSharpBlueprintMemberLibrary::GetOverrideClassReflection(Class) != nullptr)
			{
				bHasOverrideClass = true;

				return;
			}
		}
	});

	return bHasOverrideClass;
}

TSharedPtr<FExtender> FCSharpPropertyBindingExtension::CreateMenuExtender(const UWidgetBlueprint* WidgetBlueprint,
                                                                          UWidget* Widget,
                                                                          TSharedPtr<IPropertyHandle> PropertyHandle)
{
	const auto Extender = MakeShared<FExtender>();

	Extender->AddMenuExtension(TEXT("BindingActions"), EExtensionHook::After, nullptr,
	                           FMenuExtensionDelegate::CreateSP(this, &FCSharpPropertyBindingExtension::ExtendMenu,
	                                                            WidgetBlueprint, Widget, PropertyHandle));

	return Extender;
}

void FCSharpPropertyBindingExtension::ClearCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
                                                        TSharedPtr<IPropertyHandle> PropertyHandle)
{
	FName PropertyName;

	if (FindDelegateProperty(Widget, PropertyHandle, &PropertyName) == nullptr)
	{
		return;
	}

	if (const auto Extension = UWidgetBlueprintExtension::GetExtension<UCSharpWidgetBlueprintExtension>(WidgetBlueprint))
	{
		if (Extension->RemoveBinding(UCSharpWidgetBlueprintExtension::GetWidgetKey(WidgetBlueprint, Widget), PropertyName))
		{
			FBlueprintEditorUtils::MarkBlueprintAsModified(const_cast<UWidgetBlueprint*>(WidgetBlueprint));
		}
	}
}

TOptional<FName> FCSharpPropertyBindingExtension::GetCurrentValue(const UWidgetBlueprint* WidgetBlueprint,
                                                                  const UWidget* Widget,
                                                                  TSharedPtr<IPropertyHandle> PropertyHandle) const
{
	FName PropertyName;

	if (FindDelegateProperty(Widget, PropertyHandle, &PropertyName) == nullptr)
	{
		return TOptional<FName>();
	}

	if (const auto Extension = UWidgetBlueprintExtension::GetExtension<UCSharpWidgetBlueprintExtension>(WidgetBlueprint))
	{
		if (const auto Binding = Extension->FindBinding(
			UCSharpWidgetBlueprintExtension::GetWidgetKey(WidgetBlueprint, Widget), PropertyName))
		{
			return FName(*FString::Printf(TEXT("%s (C#)"), !Binding->DisplayName.IsEmpty()
				                                               ? *Binding->DisplayName
				                                               : *Binding->MemberName.ToString()));
		}
	}

	return TOptional<FName>();
}

const FSlateBrush* FCSharpPropertyBindingExtension::GetCurrentIcon(const UWidgetBlueprint* WidgetBlueprint,
                                                                   const UWidget* Widget,
                                                                   TSharedPtr<IPropertyHandle> PropertyHandle) const
{
	FName PropertyName;

	if (FindDelegateProperty(Widget, PropertyHandle, &PropertyName) == nullptr)
	{
		return nullptr;
	}

	if (const auto Extension = UWidgetBlueprintExtension::GetExtension<UCSharpWidgetBlueprintExtension>(WidgetBlueprint))
	{
		if (const auto Binding = Extension->FindBinding(
			UCSharpWidgetBlueprintExtension::GetWidgetKey(WidgetBlueprint, Widget), PropertyName))
		{
			return FAppStyle::GetBrush(static_cast<ECSharpBlueprintMemberKind>(Binding->Kind) == ECSharpBlueprintMemberKind::Function
				                           ? TEXT("Kismet.AllClasses.FunctionIcon")
				                           : TEXT("Kismet.AllClasses.VariableIcon"));
		}
	}

	return nullptr;
}

TOptional<FLinearColor> FCSharpPropertyBindingExtension::GetCurrentIconColor(const UWidgetBlueprint*, const UWidget*,
                                                                             TSharedPtr<IPropertyHandle>) const
{
	return TOptional<FLinearColor>();
}

IPropertyBindingExtension::EDropResult FCSharpPropertyBindingExtension::OnDrop(const FGeometry&, const FDragDropEvent&,
                                                                               UWidgetBlueprint*, UWidget*,
                                                                               TSharedPtr<IPropertyHandle>)
{
	return EDropResult::Unhandled;
}

FDelegateProperty* FCSharpPropertyBindingExtension::FindDelegateProperty(const UWidget* Widget,
                                                                         const TSharedPtr<const IPropertyHandle>& PropertyHandle,
                                                                         FName* OutPropertyName)
{
	if (Widget == nullptr || !PropertyHandle.IsValid() || PropertyHandle->GetProperty() == nullptr)
	{
		return nullptr;
	}

	if (const auto Parent = PropertyHandle->GetParentHandle(); Parent.IsValid() && Parent->GetProperty() != nullptr)
	{
		return nullptr;
	}

	const auto Property = PropertyHandle->GetProperty();

	const auto OwnerClass = Property->GetOwner<UClass>();

	if (OwnerClass == nullptr || !Widget->GetClass()->IsChildOf(OwnerClass))
	{
		return nullptr;
	}

	const auto DelegateProperty = FCSharpWidgetBinding::FindDelegateProperty(Widget->GetClass(), Property->GetFName());

	if (DelegateProperty == nullptr || DelegateProperty->SignatureFunction == nullptr)
	{
		return nullptr;
	}

	if (const auto ReturnProperty = DelegateProperty->SignatureFunction->GetReturnProperty();
		ReturnProperty == nullptr || !ReturnProperty->SameType(Property))
	{
		return nullptr;
	}

	if (OutPropertyName != nullptr)
	{
		*OutPropertyName = Property->GetFName();
	}

	return DelegateProperty;
}

void FCSharpPropertyBindingExtension::CollectCandidates(const UWidgetBlueprint* WidgetBlueprint,
                                                        const UFunction* DelegateSignature,
                                                        TArray<FCandidate>& OutCandidates)
{
	UK2Node_CSharpMemberBase::WithScriptDomain([&]
	{
		for (auto Class = WidgetBlueprint->GeneratedClass.Get(); Class != nullptr; Class = Class->GetSuperClass())
		{
			const auto ClassReflection = FCSharpBlueprintMemberLibrary::GetOverrideClassReflection(Class);

			if (ClassReflection == nullptr)
			{
				continue;
			}

			FCSharpBlueprintMemberLibrary::ForEachBlueprintMember(
				ClassReflection, Class, [&](const FCSharpBlueprintMemberInfo& InInfo)
				{
					if (InInfo.Kind == ECSharpBlueprintMemberKind::PropertySet ||
						(InInfo.Kind == ECSharpBlueprintMemberKind::Function && InInfo.GetParamCount() != 0))
					{
						return;
					}

					const auto Signature = FCSharpBlueprintMemberLibrary::BuildSignature(InInfo, TEXT("CSharpWidgetBindingCandidate"));

					if (Signature == nullptr)
					{
						return;
					}

					if (Signature->IsSignatureCompatibleWith(DelegateSignature))
					{
						FCandidate Candidate;

						Candidate.Info = InInfo;

						Candidate.DisplayName = FCSharpBlueprintMemberLibrary::GetDisplayName(InInfo);

						Candidate.SignatureHash = FCSharpBlueprintMemberLibrary::ComputeSignatureHash(Signature);

						OutCandidates.Add(MoveTemp(Candidate));
					}

					FCSharpBlueprintMemberLibrary::DestroySignature(Signature);
				});
		}
	});
}

void FCSharpPropertyBindingExtension::ExtendMenu(FMenuBuilder& MenuBuilder, const UWidgetBlueprint* WidgetBlueprint,
                                                 UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle)
{
	FName PropertyName;

	const auto DelegateProperty = FindDelegateProperty(Widget, PropertyHandle, &PropertyName);

	if (DelegateProperty == nullptr)
	{
		return;
	}

	TArray<FCandidate> Candidates;

	CollectCandidates(WidgetBlueprint, DelegateProperty->SignatureFunction, Candidates);

	MenuBuilder.BeginSection(TEXT("CSharp"), LOCTEXT("CSharpSection", "C#"));

	if (Candidates.IsEmpty())
	{
		const auto ReturnProperty = DelegateProperty->SignatureFunction->GetReturnProperty();

		MenuBuilder.AddMenuEntry(
			FText::Format(LOCTEXT("NoCandidate", "No C# member returning {0}"),
			              FText::FromString(ReturnProperty != nullptr ? ReturnProperty->GetCPPType() : FString())),
			LOCTEXT("NoCandidateTooltip",
			        "Declare a [UProperty, BlueprintReadOnly/BlueprintReadWrite] property or a parameterless [UFunction, BlueprintPure] method of this type on the override class"),
			FSlateIcon(),
			FUIAction(FExecuteAction(), FCanExecuteAction::CreateLambda([] { return false; })));

		MenuBuilder.EndSection();

		return;
	}

	for (const auto& Candidate : Candidates)
	{
		const auto bIsFunction = Candidate.Info.Kind == ECSharpBlueprintMemberKind::Function;

		MenuBuilder.AddMenuEntry(
			FText::FromString(Candidate.DisplayName),
			FText::Format(LOCTEXT("CandidateTooltip", "{0} {1} of C# class {2}"),
			              bIsFunction ? LOCTEXT("Function", "Function") : LOCTEXT("Property", "Property"),
			              FText::FromString(Candidate.Info.GetMemberName()),
			              Candidate.Info.OwnerClass != nullptr
				              ? Candidate.Info.OwnerClass->GetDisplayNameText()
				              : FText::GetEmpty()),
			FSlateIcon(FAppStyle::GetAppStyleSetName(),
			           bIsFunction ? TEXT("Kismet.AllClasses.FunctionIcon") : TEXT("Kismet.AllClasses.VariableIcon")),
			FUIAction(FExecuteAction::CreateLambda([WidgetBlueprint, Widget, PropertyName, Candidate]
			{
				ApplyBinding(WidgetBlueprint, Widget, PropertyName, Candidate);
			})));
	}

	MenuBuilder.EndSection();
}

void FCSharpPropertyBindingExtension::ApplyBinding(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget,
                                                   const FName& PropertyName, const FCandidate& Candidate)
{
	const auto MutableWidgetBlueprint = const_cast<UWidgetBlueprint*>(WidgetBlueprint);

	const auto WidgetKey = UCSharpWidgetBlueprintExtension::GetWidgetKey(WidgetBlueprint, Widget);

	if (MutableWidgetBlueprint == nullptr || Widget == nullptr || WidgetKey.IsNone())
	{
		return;
	}

	const FScopedTransaction Transaction(LOCTEXT("BindCSharpMember", "Bind C# Member"));

	MutableWidgetBlueprint->Modify();

	const auto WidgetName = Widget->GetName();

	MutableWidgetBlueprint->Bindings.RemoveAll([&](const FDelegateEditorBinding& InBinding)
	{
		return InBinding.ObjectName == WidgetName && InBinding.PropertyName == PropertyName;
	});

	FCSharpWidgetBinding Binding;

	Binding.WidgetName = WidgetKey;

	Binding.PropertyName = PropertyName;

	Binding.Kind = static_cast<uint8>(Candidate.Info.Kind);

	Binding.MemberName = FName(*Candidate.Info.GetMemberName());

	Binding.ParamCount = Candidate.Info.GetParamCount();

	Binding.SignatureHash = Candidate.SignatureHash;

	Binding.OwnerClass = Candidate.Info.OwnerClass;

	Binding.DisplayName = Candidate.DisplayName;

	UWidgetBlueprintExtension::RequestExtension<UCSharpWidgetBlueprintExtension>(MutableWidgetBlueprint)->SetBinding(Binding);

	FBlueprintEditorUtils::MarkBlueprintAsModified(MutableWidgetBlueprint);
}

#undef LOCTEXT_NAMESPACE
