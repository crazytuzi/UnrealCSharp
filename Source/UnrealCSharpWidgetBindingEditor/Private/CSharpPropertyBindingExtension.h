#pragma once

#include "CoreMinimal.h"
#include "CSharpBlueprintMember.h"
#include "IHasPropertyBindingExtensibility.h"

class FMenuBuilder;

class FCSharpPropertyBindingExtension final : public IPropertyBindingExtension,
                                              public TSharedFromThis<FCSharpPropertyBindingExtension>
{
public:
	virtual bool CanExtend(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
	                       TSharedPtr<const IPropertyHandle> PropertyHandle) const override;

	virtual TSharedPtr<FExtender> CreateMenuExtender(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget,
	                                                 TSharedPtr<IPropertyHandle> PropertyHandle) override;

	virtual void ClearCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
	                               TSharedPtr<IPropertyHandle> PropertyHandle) override;

	virtual TOptional<FName> GetCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
	                                         TSharedPtr<IPropertyHandle> PropertyHandle) const override;

	virtual const FSlateBrush* GetCurrentIcon(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
	                                          TSharedPtr<IPropertyHandle> PropertyHandle) const override;

	virtual TOptional<FLinearColor> GetCurrentIconColor(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget,
	                                                    TSharedPtr<IPropertyHandle> PropertyHandle) const override;

	virtual EDropResult OnDrop(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent,
	                           UWidgetBlueprint* WidgetBlueprint, UWidget* Widget,
	                           TSharedPtr<IPropertyHandle> PropertyHandle) override;

private:
	struct FCandidate
	{
		FCSharpBlueprintMemberInfo Info;

		FString DisplayName;

		uint32 SignatureHash = 0;
	};

	static FDelegateProperty* FindDelegateProperty(const UWidget* Widget, const TSharedPtr<const IPropertyHandle>& PropertyHandle,
	                                               FName* OutPropertyName = nullptr);

	static void CollectCandidates(const UWidgetBlueprint* WidgetBlueprint, const UFunction* DelegateSignature,
	                              TArray<FCandidate>& OutCandidates);

	void ExtendMenu(FMenuBuilder& MenuBuilder, const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget,
	                TSharedPtr<IPropertyHandle> PropertyHandle);

	static void ApplyBinding(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, const FName& PropertyName,
	                         const FCandidate& Candidate);
};
