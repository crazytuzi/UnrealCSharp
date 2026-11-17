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
			// 未连接的 Target 走 self，与 DefaultToSelf 一致
			if (Pin->LinkedTo.IsEmpty() && FKismetCompilerUtilities::ValidateSelfCompatibility(Pin, Context))
			{
				const auto Term = Context.RegisterLiteral(Pin);

				Term->Type.PinSubCategory = UEdGraphSchema_K2::PN_Self;

				Context.NetMap.Add(Pin, Term);
			}

			continue;
		}

		if (Pin->Direction == EGPD_Input)
		{
			// ref / 容器输入已在 ExpandNode 中接到临时变量，这里只剩普通字面量
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
		CompilerContext.MessageLog.Error(*LOCTEXT("LibraryFunctionMissing", "@@ 找不到 UCSharpBlueprintFunctionLibrary 入口函数").
		                                 ToString(), Node);

		return;
	}

	const auto TargetPin = MemberNode->GetTargetPin();

	if (TargetPin == nullptr)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("TargetPinMissing", "@@ 缺少 Target 引脚").ToString(), Node);

		return;
	}

	// 接口值是 16 字节的 FScriptInterface，不能直接当 UObject* 读；CallFunction 处理器会插转换，这里直接拒绝
	const auto IsLinkedToInterface = [](const UEdGraphPin* InPin)
	{
		return InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Object &&
			InPin->LinkedTo.Num() > 0 && InPin->LinkedTo[0] != nullptr &&
			InPin->LinkedTo[0]->PinType.PinCategory == UEdGraphSchema_K2::PC_Interface;
	};

	if (IsLinkedToInterface(TargetPin))
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("InterfaceTarget", "@@ 不能直接连接接口引脚，请先 Cast 为对象").ToString(),
		                                 TargetPin);

		return;
	}

	const auto TargetTerm = Context.NetMap.Find(FEdGraphUtilities::GetNetFromPin(TargetPin));

	if (TargetTerm == nullptr)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("TargetTermMissing", "无法解析 @@ 的 Target").ToString(), TargetPin);

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
			CompilerContext.MessageLog.Error(*LOCTEXT("TermMissing", "无法解析传入 @@ 的值").ToString(), Pin);

			bHasError = true;

			continue;
		}

		auto Term = *FoundTerm;

		if (Pin->Direction == EGPD_Input)
		{
			if (IsLinkedToInterface(Pin))
			{
				CompilerContext.MessageLog.Error(*LOCTEXT("InterfaceParam", "@@ 不能直接连接接口引脚，请先 Cast 为对象").
				                                 ToString(), Pin);

				bHasError = true;
			}

			if (const auto CastTerm = UE::KismetCompiler::CastingUtils::InsertImplicitCastStatement(Context, Pin, Term))
			{
				if (Pin->PinType.bIsReference)
				{
					CompilerContext.MessageLog.Error(*LOCTEXT("RefImplicitCast",
					                                          "引用参数 @@ 不支持 float/double 隐式转换，请连接相同精度的变量").
					                                 ToString(), Pin);

					bHasError = true;
				}

				Term = CastTerm;
			}

			if (Pin->PinType.bIsReference && !Term->IsTermWritable())
			{
				CompilerContext.MessageLog.Error(*LOCTEXT("RefReadOnly", "不能把只读变量传给引用参数 @@").ToString(), Pin);

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
