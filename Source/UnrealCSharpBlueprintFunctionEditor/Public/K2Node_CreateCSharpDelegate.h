#pragma once

#include "CoreMinimal.h"
#include "K2Node_CSharpMemberBase.h"
#include "K2Node_CreateCSharpDelegate.generated.h"

UCLASS()
class UNREALCSHARPBLUEPRINTFUNCTIONEDITOR_API UK2Node_CreateCSharpDelegate : public UK2Node_CSharpMemberBase
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

	virtual FLinearColor GetNodeTitleColor() const override;

	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin,
	                                    FString& OutReason) const override;

	virtual bool IsNodePure() const override { return true; }

	virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;

	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;

	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;

	virtual ECSharpBlueprintMemberKind GetMemberKind() const override;

	virtual bool HandlesMemberKind(ECSharpBlueprintMemberKind InKind) const override;

	virtual void InitializeFromSpawnData(const FCSharpBlueprintMemberSpawnData& InData) override;

	virtual FString GetMenuNameForSpawnData(const FCSharpBlueprintMemberSpawnData& InData) const override;

public:
	UEdGraphPin* GetDelegateOutPin() const;

	UFunction* GetConnectedDelegateSignature() const;

	bool IsCompatibleWithDelegateSignature(const UFunction* InSignature, FString* OutReason = nullptr) const;

	static FName GetDelegateOutPinName();
};
