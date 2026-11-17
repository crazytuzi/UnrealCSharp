#include "KCHandler_CSharpMemberCall.h"

#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "K2Node_CSharpMemberBase.h"
#include "KismetCastingUtils.h"
#include "KismetCompiledFunctionContext.h"
#include "KismetCompiler.h"

#define LOCTEXT_NAMESPACE "KCHandler_CSharpMemberCall"

FKCHandler_CSharpMemberCall::FKCHandler_CSharpMemberCall(FKismetCompilerContext& InCompilerContext) :
	FNodeHandlingFunctor(InCompilerContext)
{
}

void FKCHandler_CSharpMemberCall::RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node)
{
	const auto MemberNode = CastChecked<UK2Node_CSharpMemberBase>(Node);

	const auto Schema = CompilerContext.GetSchema();

	const auto TargetPin = MemberNode->GetTargetPin();

	for (const auto Pin : Node->Pins)
	{
		if (Pin == nullptr || Pin->bOrphanedPin || Schema->IsExecPin(*Pin))
		{
			continue;
		}

		if (Pin == TargetPin)
		{
			MemberNode->RegisterTargetNetIfUnlinked(Context, Pin);

			continue;
		}

		if (Pin->Direction == EGPD_Input)
		{
			if (Pin->LinkedTo.IsEmpty())
			{
				RegisterLiteral(Context, Pin);
			}
		}
		else
		{
			const auto Term = Context.CreateLocalTerminalFromPinAutoChooseScope(
				Pin, Context.NetNameMap->MakeValidName(Pin));

			Context.NetMap.Add(Pin, Term);
		}
	}
}

void FKCHandler_CSharpMemberCall::Compile(FKismetFunctionContext& Context, UEdGraphNode* Node)
{
	const auto MemberNode = CastChecked<UK2Node_CSharpMemberBase>(Node);

	const auto LibraryFunction = MemberNode->GetLibraryFunction();

	if (LibraryFunction == nullptr)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("LibraryFunctionMissing", "@@ could not find the UCSharpBlueprintFunctionLibrary entry function").
		                                 ToString(), Node);

		return;
	}

	const auto TargetPin = MemberNode->GetTargetPin();

	if (TargetPin == nullptr)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("TargetPinMissing", "@@ is missing its Target pin").ToString(), Node);

		return;
	}

	const auto IsLinkedToInterface = [](const UEdGraphPin* InPin)
	{
		return InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Object &&
			InPin->LinkedTo.Num() > 0 && InPin->LinkedTo[0] != nullptr &&
			InPin->LinkedTo[0]->PinType.PinCategory == UEdGraphSchema_K2::PC_Interface;
	};

	if (IsLinkedToInterface(TargetPin))
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("InterfaceTarget", "@@ cannot be connected to an interface pin directly, cast it to an object first").ToString(),
		                                 TargetPin);

		return;
	}

	const auto TargetTerm = Context.NetMap.Find(FEdGraphUtilities::GetNetFromPin(TargetPin));

	if (TargetTerm == nullptr)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("TargetTermMissing", "Failed to resolve the Target of @@").ToString(), TargetPin);

		return;
	}

	TArray<FBPTerminal*> RHSTerms;

	RHSTerms.Add(*TargetTerm);

	RHSTerms.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Name, MemberNode->MemberName.ToString()));

	RHSTerms.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Int, LexToString(MemberNode->ParamCount)));

	RHSTerms.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Int,
	                             LexToString(static_cast<int32>(MemberNode->SignatureHash))));

	TArray<UEdGraphPin*> MemberPins;

	MemberNode->GetMemberPins(MemberPins);

	auto bHasError = false;

	for (const auto Pin : MemberPins)
	{
		const auto FoundTerm = Context.NetMap.Find(FEdGraphUtilities::GetNetFromPin(Pin));

		if (FoundTerm == nullptr)
		{
			CompilerContext.MessageLog.Error(*LOCTEXT("TermMissing", "Failed to resolve the value passed into @@").ToString(), Pin);

			bHasError = true;

			continue;
		}

		auto Term = *FoundTerm;

		if (Pin->Direction == EGPD_Input)
		{
			if (IsLinkedToInterface(Pin))
			{
				CompilerContext.MessageLog.Error(*LOCTEXT("InterfaceParam", "@@ cannot be connected to an interface pin directly, cast it to an object first").
				                                 ToString(), Pin);

				bHasError = true;
			}

			if (const auto CastTerm = UE::KismetCompiler::CastingUtils::InsertImplicitCastStatement(Context, Pin, Term))
			{
				if (Pin->PinType.bIsReference)
				{
					CompilerContext.MessageLog.Error(*LOCTEXT("RefImplicitCast",
					                                          "Reference parameter @@ does not support implicit float/double conversion, connect a variable of the same precision").
					                                 ToString(), Pin);

					bHasError = true;
				}

				Term = CastTerm;
			}

			if (Pin->PinType.bIsReference && !Term->IsTermWritable())
			{
				CompilerContext.MessageLog.Error(*LOCTEXT("RefReadOnly", "Cannot pass a read-only variable to reference parameter @@").ToString(), Pin);

				bHasError = true;
			}
		}

		RHSTerms.Add(Term);
	}

	if (bHasError)
	{
		return;
	}

	auto& Statement = Context.AppendStatementForNode(Node);

	Statement.Type = KCST_CallFunction;

	Statement.FunctionToCall = LibraryFunction;

	Statement.FunctionContext = nullptr;

	Statement.LHS = nullptr;

	Statement.RHS = MoveTemp(RHSTerms);

	if (!MemberNode->IsNodePure())
	{
		GenerateSimpleThenGoto(Context, *Node);
	}
}

FBPTerminal* FKCHandler_CSharpMemberCall::MakeLiteralTerm(FKismetFunctionContext& Context, UEdGraphNode* Node,
                                                           const FName& InCategory, const FString& InValue) const
{
	const auto Term = Context.CreateLocalTerminal(ETerminalSpecification::TS_Literal);

	Term->bIsLiteral = true;

	Term->Type.PinCategory = InCategory;

	Term->Name = InValue;

	Term->Source = Node;

	return Term;
}

#undef LOCTEXT_NAMESPACE
