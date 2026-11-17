#pragma once

#include "CoreMinimal.h"
#include "K2Node_CSharpMemberBase.h"
#include "K2Node_CSharpPropertyAccess.generated.h"

/** 读写 C# Override 类上的 [UProperty, BlueprintReadWrite/BlueprintReadOnly] 属性 */
UCLASS()
class UNREALCSHARPBLUEPRINTFUNCTIONEDITOR_API UK2Node_CSharpPropertyAccess : public UK2Node_CSharpMemberBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

	virtual FLinearColor GetNodeTitleColor() const override;

	virtual ECSharpBlueprintMemberKind GetMemberKind() const override;

	virtual bool HandlesMemberKind(ECSharpBlueprintMemberKind InKind) const override;

	virtual void InitializeFromSpawnData(const FCSharpBlueprintMemberSpawnData& InData) override;

	virtual FString GetMenuNameForSpawnData(const FCSharpBlueprintMemberSpawnData& InData) const override;

public:
	UEdGraphPin* GetValuePin() const;

public:
	UPROPERTY()
	bool bIsSetter = false;
};
