#include "K2Node_CSharpPropertyAccess.h"

#include "EdGraphSchema_K2.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "K2Node_CSharpPropertyAccess"

FText UK2Node_CSharpPropertyAccess::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
	const auto Name = FText::FromString(!DisplayName.IsEmpty() ? DisplayName : MemberName.ToString());

	const auto Title = bIsSetter
		                   ? FText::Format(LOCTEXT("SetTitle", "Set {0} (C#)"), Name)
		                   : FText::Format(LOCTEXT("GetTitle", "Get {0} (C#)"), Name);

	if (TitleType == ENodeTitleType::FullTitle && !IsTargetSelf())
	{
		return FText::Format(LOCTEXT("FullTitle", "{0}\nTarget is {1}"), Title, GetOwnerClassDisplayName());
	}

	return Title;
}

FSlateIcon UK2Node_CSharpPropertyAccess::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetNodeTitleColor();

	return FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.VariableIcon");
}

FLinearColor UK2Node_CSharpPropertyAccess::GetNodeTitleColor() const
{
	if (const auto ValuePin = GetValuePin())
	{
		return GetDefault<UEdGraphSchema_K2>()->GetPinTypeColor(ValuePin->PinType);
	}

	return Super::GetNodeTitleColor();
}

ECSharpBlueprintMemberKind UK2Node_CSharpPropertyAccess::GetMemberKind() const
{
	return bIsSetter ? ECSharpBlueprintMemberKind::PropertySet : ECSharpBlueprintMemberKind::PropertyGet;
}

bool UK2Node_CSharpPropertyAccess::HandlesMemberKind(const ECSharpBlueprintMemberKind InKind) const
{
	return InKind != ECSharpBlueprintMemberKind::Function;
}

void UK2Node_CSharpPropertyAccess::InitializeFromSpawnData(const FCSharpBlueprintMemberSpawnData& InData)
{
	Super::InitializeFromSpawnData(InData);

	bIsSetter = InData.Kind == ECSharpBlueprintMemberKind::PropertySet;

	bIsPure = !bIsSetter;
}

FString UK2Node_CSharpPropertyAccess::GetMenuNameForSpawnData(const FCSharpBlueprintMemberSpawnData& InData) const
{
	return FString::Printf(TEXT("%s %s"),
	                       InData.Kind == ECSharpBlueprintMemberKind::PropertySet ? TEXT("Set") : TEXT("Get"),
	                       *InData.DisplayName);
}

UEdGraphPin* UK2Node_CSharpPropertyAccess::GetValuePin() const
{
	TArray<UEdGraphPin*> MemberPins;

	GetMemberPins(MemberPins);

	return !MemberPins.IsEmpty() ? MemberPins[0] : nullptr;
}

#undef LOCTEXT_NAMESPACE
