#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "CSharpBlueprintMember.h"
#include "K2Node_CSharpMemberBase.generated.h"

class FBlueprintActionDatabaseRegistrar;
struct FBPTerminal;
struct FKismetFunctionContext;

struct FCSharpBlueprintMemberSpawnData
{
	TWeakObjectPtr<UClass> OwnerClass;

	ECSharpBlueprintMemberKind Kind = ECSharpBlueprintMemberKind::Function;

	FName MemberName;

	int32 ParamCount = 0;

	bool bIsPure = false;

	FString DisplayName;

	FString Category;

	FString ToolTip;
};

USTRUCT()
struct FCSharpBlueprintPinDescription
{
	GENERATED_BODY()

	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FEdGraphPinType PinType;

	UPROPERTY()
	TEnumAsByte<EEdGraphPinDirection> Direction = EGPD_Input;

	UPROPERTY()
	FString ToolTip;

	bool operator==(const FCSharpBlueprintPinDescription& InOther) const;

	bool operator!=(const FCSharpBlueprintPinDescription& InOther) const { return !(*this == InOther); }
};

UCLASS(Abstract)
class UNREALCSHARPBLUEPRINTFUNCTIONEDITOR_API UK2Node_CSharpMemberBase : public UK2Node
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;

	virtual FText GetTooltipText() const override;

	virtual FText GetKeywords() const override;

	virtual FLinearColor GetNodeTitleColor() const override;

	virtual bool HasExternalDependencies(TArray<UStruct*>* OptionalOutput) const override;

	virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;

	virtual bool IsNodePure() const override { return bIsPure; }

	virtual FText GetMenuCategory() const override;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;

	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;

	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;

public:
	virtual ECSharpBlueprintMemberKind GetMemberKind() const
	PURE_VIRTUAL(UK2Node_CSharpMemberBase::GetMemberKind, return ECSharpBlueprintMemberKind::Function;);

	virtual bool HandlesMemberKind(ECSharpBlueprintMemberKind InKind) const
	PURE_VIRTUAL(UK2Node_CSharpMemberBase::HandlesMemberKind, return false;);

	virtual void InitializeFromSpawnData(const FCSharpBlueprintMemberSpawnData& InData);

	virtual FString GetMenuNameForSpawnData(const FCSharpBlueprintMemberSpawnData& InData) const;

	UFunction* GetLibraryFunction() const;

	UEdGraphPin* GetTargetPin() const;

	void GetMemberPins(TArray<UEdGraphPin*>& OutPins) const;

	bool RefreshFromReflection();

	bool ResolveMember(FCSharpBlueprintMemberInfo& OutInfo) const;

	static void WithScriptDomain(const TFunctionRef<void()>& InFunction);

	static bool BuildPinDescriptions(const FCSharpBlueprintMemberInfo& InInfo,
	                                 TArray<FCSharpBlueprintPinDescription>& OutPins,
	                                 uint32& OutSignatureHash, bool& bOutIsPure);

	static FCSharpBlueprintMemberSpawnData MakeSpawnData(const FCSharpBlueprintMemberInfo& InInfo);

	FBPTerminal* RegisterTargetNetIfUnlinked(FKismetFunctionContext& Context, UEdGraphPin* TargetPin) const;

protected:
	FText GetOwnerClassDisplayName() const;

	bool IsTargetSelf() const;

	UEdGraphPin* CreateTargetPin();

private:
	static void CustomizeNewNode(UEdGraphNode* InNode, bool bIsTemplateNode, FCSharpBlueprintMemberSpawnData InData);

public:
	UPROPERTY()
	TObjectPtr<UClass> OwnerClass;

	UPROPERTY()
	FName MemberName;

	UPROPERTY()
	int32 ParamCount = 0;

	UPROPERTY()
	bool bIsPure = false;

	UPROPERTY()
	uint32 SignatureHash = 0;

	UPROPERTY()
	FString DisplayName;

	UPROPERTY()
	FString Category;

	UPROPERTY()
	FString ToolTip;

	UPROPERTY()
	TArray<FCSharpBlueprintPinDescription> CachedPins;
};
