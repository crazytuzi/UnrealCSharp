#include "K2Node_CallCSharpFunction.h"

#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "K2Node_CallCSharpFunction"

FText UK2Node_CallCSharpFunction::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
	const auto Title = FText::FromString(!DisplayName.IsEmpty() ? DisplayName : MemberName.ToString());

	if (TitleType == ENodeTitleType::FullTitle && !IsTargetSelf())
	{
		return FText::Format(LOCTEXT("FullTitle", "{0}\nTarget is {1} (C#)"), Title, GetOwnerClassDisplayName());
	}

	if (TitleType == ENodeTitleType::FullTitle)
	{
		return FText::Format(LOCTEXT("FullTitleSelf", "{0}\nC#"), Title);
	}

	return Title;
}

FSlateIcon UK2Node_CallCSharpFunction::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetNodeTitleColor();

	return FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
}

ECSharpBlueprintMemberKind UK2Node_CallCSharpFunction::GetMemberKind() const
{
	return ECSharpBlueprintMemberKind::Function;
}

bool UK2Node_CallCSharpFunction::HandlesMemberKind(const ECSharpBlueprintMemberKind InKind) const
{
	return InKind == ECSharpBlueprintMemberKind::Function;
}

#undef LOCTEXT_NAMESPACE
