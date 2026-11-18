#pragma once

#include "CoreMinimal.h"
#include "K2Node_CSharpMemberBase.h"
#include "K2Node_CallCSharpFunction.generated.h"

UCLASS()
class UNREALCSHARPBLUEPRINTFUNCTIONEDITOR_API UK2Node_CallCSharpFunction : public UK2Node_CSharpMemberBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

	virtual ECSharpBlueprintMemberKind GetMemberKind() const override;

	virtual bool HandlesMemberKind(ECSharpBlueprintMemberKind InKind) const override;
};
