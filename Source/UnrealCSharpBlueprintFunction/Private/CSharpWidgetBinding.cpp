#include "CSharpWidgetBinding.h"

#include "CSharpBlueprintMember.h"
#include "CSharpDelegateProxy.h"
#include "Blueprint/UserWidget.h"
#include "Log/UnrealCSharpLog.h"

FName FCSharpWidgetBinding::GetDelegatePropertyName(const FName& InPropertyName)
{
	return FName(*(InPropertyName.ToString() + TEXT("Delegate")));
}

FDelegateProperty* FCSharpWidgetBinding::FindDelegateProperty(const UClass* InWidgetClass, const FName& InPropertyName)
{
	return InWidgetClass != nullptr
		       ? FindFProperty<FDelegateProperty>(InWidgetClass, GetDelegatePropertyName(InPropertyName))
		       : nullptr;
}

void UCSharpWidgetBindingClassExtension::Initialize(UUserWidget* UserWidget)
{
	Super::Initialize(UserWidget);

	if (UserWidget == nullptr || UserWidget->IsDesignTime())
	{
		return;
	}

	for (const auto& Binding : Bindings)
	{
		const auto Widget = UserWidget->GetWidgetFromName(Binding.WidgetName);

		if (Widget == nullptr)
		{
			UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpWidgetBinding: widget %s was not found in %s"),
			       *Binding.WidgetName.ToString(), *UserWidget->GetClass()->GetName());

			continue;
		}

		const auto DelegateProperty = FCSharpWidgetBinding::FindDelegateProperty(Widget->GetClass(), Binding.PropertyName);

		if (DelegateProperty == nullptr)
		{
			UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpWidgetBinding: %s.%s has no bindable delegate"),
			       *Widget->GetClass()->GetName(), *Binding.PropertyName.ToString());

			continue;
		}

		const auto Proxy = UCSharpDelegateProxy::GetOrCreate(UserWidget,
		                                                     static_cast<ECSharpBlueprintMemberKind>(Binding.Kind),
		                                                     Binding.MemberName, Binding.ParamCount,
		                                                     Binding.SignatureHash);

		if (Proxy == nullptr)
		{
			continue;
		}

		FScriptDelegate Delegate;

		Delegate.BindUFunction(Proxy, UCSharpDelegateProxy::GetInvokeFunctionName());

		DelegateProperty->SetPropertyValue_InContainer(Widget, Delegate);
	}
}
