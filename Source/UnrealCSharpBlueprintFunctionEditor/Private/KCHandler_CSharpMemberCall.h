#pragma once

#include "CoreMinimal.h"
#include "KismetCompilerMisc.h"

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
