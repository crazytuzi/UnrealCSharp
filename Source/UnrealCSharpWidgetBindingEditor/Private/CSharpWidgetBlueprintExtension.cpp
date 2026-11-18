#include "CSharpWidgetBlueprintExtension.h"

#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "CSharpBlueprintMember.h"
#include "K2Node_CSharpMemberBase.h"
#include "Kismet2/CompilerResultsLog.h"
#include "WidgetBlueprint.h"
#include "WidgetBlueprintCompiler.h"

#define LOCTEXT_NAMESPACE "CSharpWidgetBlueprintExtension"

const FCSharpWidgetBinding* UCSharpWidgetBlueprintExtension::FindBinding(const FName& InWidgetName,
                                                                         const FName& InPropertyName) const
{
	return Bindings.FindByPredicate([&](const FCSharpWidgetBinding& InBinding)
	{
		return InBinding.Matches(InWidgetName, InPropertyName);
	});
}

void UCSharpWidgetBlueprintExtension::SetBinding(const FCSharpWidgetBinding& InBinding)
{
	Modify();

	RemoveBinding(InBinding.WidgetName, InBinding.PropertyName);

	Bindings.Add(InBinding);
}

bool UCSharpWidgetBlueprintExtension::RemoveBinding(const FName& InWidgetName, const FName& InPropertyName)
{
	Modify();

	return Bindings.RemoveAll([&](const FCSharpWidgetBinding& InBinding)
	{
		return InBinding.Matches(InWidgetName, InPropertyName);
	}) > 0;
}

const TArray<FCSharpWidgetBinding>& UCSharpWidgetBlueprintExtension::GetBindings() const
{
	return Bindings;
}

FName UCSharpWidgetBlueprintExtension::GetWidgetKey(const UWidgetBlueprint* InWidgetBlueprint, const UWidget* InWidget)
{
	if (InWidgetBlueprint == nullptr || InWidget == nullptr || InWidgetBlueprint->WidgetTree == nullptr ||
		InWidgetBlueprint->WidgetTree->FindWidget(InWidget->GetFName()) == nullptr)
	{
		return NAME_None;
	}

	return InWidget->GetFName();
}

void UCSharpWidgetBlueprintExtension::HandleBeginCompilation(FWidgetBlueprintCompilerContext& InCreationContext)
{
	Super::HandleBeginCompilation(InCreationContext);

	CompilerContext = &InCreationContext;
}

void UCSharpWidgetBlueprintExtension::HandleFinishCompilingClass(UWidgetBlueprintGeneratedClass* Class)
{
	Super::HandleFinishCompilingClass(Class);

	if (CompilerContext == nullptr || !CompilerContext->bIsFullCompile || Class == nullptr)
	{
		return;
	}

	TArray<FCSharpWidgetBinding> ValidBindings;

	for (const auto& Binding : Bindings)
	{
		if (FCSharpWidgetBinding ValidBinding; ValidateBinding(Binding, Class, ValidBinding))
		{
			ValidBindings.Add(ValidBinding);
		}
	}

	static const FName ExtensionName(TEXT("CSharpWidgetBindings"));

	if (const auto Previous = StaticFindObjectFast(UCSharpWidgetBindingClassExtension::StaticClass(), Class,
	                                               ExtensionName, true))
	{
		Previous->Rename(
			*MakeUniqueObjectName(GetTransientPackage(), Previous->GetClass(),
			                      *FString::Printf(TEXT("TRASH_%s"), *Previous->GetName())).ToString(),
			GetTransientPackage(), REN_NonTransactional | REN_DoNotDirty | REN_DontCreateRedirectors);
	}

	if (ValidBindings.IsEmpty())
	{
		return;
	}

	const auto Extension = NewObject<UCSharpWidgetBindingClassExtension>(Class, ExtensionName);

	Extension->Bindings = MoveTemp(ValidBindings);

	CompilerContext->AddExtension(Class, Extension);
}

void UCSharpWidgetBlueprintExtension::HandleEndCompilation()
{
	Super::HandleEndCompilation();

	CompilerContext = nullptr;
}

bool UCSharpWidgetBlueprintExtension::ValidateBinding(const FCSharpWidgetBinding& InBinding,
                                                      UWidgetBlueprintGeneratedClass* InClass,
                                                      FCSharpWidgetBinding& OutBinding) const
{
	auto& MessageLog = CompilerContext->MessageLog;

	const auto WidgetBlueprint = GetWidgetBlueprint();

	const UWidget* Widget = nullptr;

	if (!InBinding.WidgetName.IsNone() && WidgetBlueprint != nullptr && WidgetBlueprint->WidgetTree != nullptr)
	{
		Widget = WidgetBlueprint->WidgetTree->FindWidget(InBinding.WidgetName);
	}

	if (Widget == nullptr)
	{
		MessageLog.Warning(*FText::Format(LOCTEXT("WidgetMissing", "C# binding target widget {0} was not found, binding of {1} is skipped"),
		                                  FText::FromName(InBinding.WidgetName),
		                                  FText::FromName(InBinding.PropertyName)).ToString());

		return false;
	}

	const auto DelegateProperty = FCSharpWidgetBinding::FindDelegateProperty(Widget->GetClass(), InBinding.PropertyName);

	if (DelegateProperty == nullptr || DelegateProperty->SignatureFunction == nullptr)
	{
		MessageLog.Warning(*FText::Format(LOCTEXT("DelegateMissing", "{0}.{1} is not bindable, C# binding is skipped"),
		                                  FText::FromName(InBinding.WidgetName),
		                                  FText::FromName(InBinding.PropertyName)).ToString());

		return false;
	}

	if (InBinding.OwnerClass == nullptr)
	{
		MessageLog.Error(*FText::Format(LOCTEXT("OwnerClassMissing", "The owner class of C# member {0} bound to {1}.{2} could not be loaded"),
		                                FText::FromName(InBinding.MemberName),
		                                FText::FromName(InBinding.WidgetName),
		                                FText::FromName(InBinding.PropertyName)).ToString());

		return false;
	}

	OutBinding = InBinding;

	auto bDomainReady = false;

	auto bValid = true;

	UK2Node_CSharpMemberBase::WithScriptDomain([&]
	{
		bDomainReady = true;

		FCSharpBlueprintMemberInfo Info;

		if (!FCSharpBlueprintMemberLibrary::ResolveDeclared(
			FCSharpBlueprintMemberLibrary::GetOverrideClassReflection(InBinding.OwnerClass), InBinding.OwnerClass,
			static_cast<ECSharpBlueprintMemberKind>(InBinding.Kind), InBinding.MemberName, InBinding.ParamCount, Info))
		{
			MessageLog.Warning(*FText::Format(LOCTEXT("MemberMissing", "C# member {0} bound to {1}.{2} was not found in {3}, the binding is skipped. Remove or rebind it in the designer"),
			                                  FText::FromName(InBinding.MemberName),
			                                  FText::FromName(InBinding.WidgetName),
			                                  FText::FromName(InBinding.PropertyName),
			                                  InBinding.OwnerClass->GetDisplayNameText()).ToString());

			bValid = false;

			return;
		}

		const auto Signature = FCSharpBlueprintMemberLibrary::BuildSignature(Info, TEXT("CSharpWidgetBindingSignature"));

		if (Signature == nullptr)
		{
			MessageLog.Error(*FText::Format(LOCTEXT("UnsupportedSignature", "C# member {0} bound to {1}.{2} has a signature not supported by Blueprint"),
			                                FText::FromName(InBinding.MemberName),
			                                FText::FromName(InBinding.WidgetName),
			                                FText::FromName(InBinding.PropertyName)).ToString());

			bValid = false;

			return;
		}

		if (!Signature->IsSignatureCompatibleWith(DelegateProperty->SignatureFunction))
		{
			MessageLog.Error(*FText::Format(LOCTEXT("SignatureMismatch", "C# member {0} does not match the signature of {1}.{2} (Blueprint Float maps to C# double)"),
			                                FText::FromName(InBinding.MemberName),
			                                FText::FromName(InBinding.WidgetName),
			                                FText::FromName(InBinding.PropertyName)).ToString());

			bValid = false;
		}
		else
		{
			OutBinding.ParamCount = Info.GetParamCount();

			OutBinding.SignatureHash = FCSharpBlueprintMemberLibrary::ComputeSignatureHash(Signature);

			OutBinding.DisplayName = FCSharpBlueprintMemberLibrary::GetDisplayName(Info);
		}

		FCSharpBlueprintMemberLibrary::DestroySignature(Signature);
	});

	if (!bDomainReady)
	{
		MessageLog.Note(*FText::Format(LOCTEXT("DomainNotReady", "C# runtime is not ready, binding {0}.{1} -> {2} uses its cached signature"),
		                               FText::FromName(InBinding.WidgetName),
		                               FText::FromName(InBinding.PropertyName),
		                               FText::FromName(InBinding.MemberName)).ToString());
	}

	return bValid;
}

#undef LOCTEXT_NAMESPACE
