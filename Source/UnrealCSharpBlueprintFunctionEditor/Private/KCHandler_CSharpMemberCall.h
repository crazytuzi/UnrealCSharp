#pragma once

#include "CoreMinimal.h"
#include "KismetCompilerMisc.h"

/**
 * 把 UK2Node_CSharpMemberBase 编译成一条对 UCSharpBlueprintFunctionLibrary 变参函数的 KCST_CallFunction：
 * RHS = [Target, MemberName, ParamCount, SignatureHash, 成员引脚项...]
 */
class FKCHandler_CSharpMemberCall final : public FNodeHandlingFunctor
{
public:
	explicit FKCHandler_CSharpMemberCall(FKismetCompilerContext& InCompilerContext);

public:
	virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;

	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;

private:
	FBPTerminal* MakeLiteralTerm(FKismetFunctionContext& Context, UEdGraphNode* Node, const FName& InCategory,
	                             const FString& InValue) const;
};
