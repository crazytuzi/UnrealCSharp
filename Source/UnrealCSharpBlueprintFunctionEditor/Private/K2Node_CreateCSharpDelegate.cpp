#include "K2Node_CreateCSharpDelegate.h"

#include "BlueprintActionFilter.h"
#include "CSharpBlueprintFunctionLibrary.h"
#include "CSharpDelegateProxy.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "Engine/MemberReference.h"
#include "GraphEditorSettings.h"
#include "KismetCompiledFunctionContext.h"
#include "KismetCompiler.h"
#include "KismetCompilerMisc.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/CompilerResultsLog.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "K2Node_CreateCSharpDelegate"

class FKCHandler_CreateCSharpDelegate final : public FNodeHandlingFunctor
{
public:
	using FNodeHandlingFunctor::FNodeHandlingFunctor;

	virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override
	{
		const auto DelegateNode = CastChecked<UK2Node_CreateCSharpDelegate>(Node);

		DelegateNode->RegisterTargetNetIfUnlinked(Context, DelegateNode->GetTargetPin());

		if (const auto DelegatePin = DelegateNode->GetDelegateOutPin())
		{
			const auto Signature = DelegateNode->GetConnectedDelegateSignature();

			if (Signature == nullptr)
			{
				CompilerContext.MessageLog.Error(*LOCTEXT("NoDelegateSignature",
				                                          "Unable to determine the delegate signature connected to @@, is the Event pin connected?").
				                                 ToString(), DelegateNode);

				return;
			}

			if (FString Reason; !DelegateNode->IsCompatibleWithDelegateSignature(Signature, &Reason))
			{
				CompilerContext.MessageLog.Error(*FString::Printf(TEXT("@@ %s"), *Reason), DelegateNode);

				return;
			}

			const auto Term = Context.CreateLocalTerminalFromPinAutoChooseScope(
				DelegatePin, Context.NetNameMap->MakeValidName(DelegatePin));

			FMemberReference::FillSimpleMemberReference<UFunction>(Signature, Term->Type.PinSubCategoryMemberReference);

			Context.NetMap.Add(DelegatePin, Term);
		}

		const auto ProxyTerm = Context.CreateLocalTerminal();

		ProxyTerm->Type.PinCategory = UEdGraphSchema_K2::PC_Object;

		ProxyTerm->Type.PinSubCategoryObject = UCSharpDelegateProxy::StaticClass();

		ProxyTerm->Name = Context.NetNameMap->MakeValidName(Node, TEXT("Proxy"));

		ProxyTerm->Source = Node;

		ProxyTerms.Add(Node, ProxyTerm);
	}

	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override
	{
		const auto DelegateNode = CastChecked<UK2Node_CreateCSharpDelegate>(Node);

		const auto LibraryFunction = UCSharpBlueprintFunctionLibrary::GetDelegateProxyFunction();

		const auto TargetPin = DelegateNode->GetTargetPin();

		const auto DelegatePin = DelegateNode->GetDelegateOutPin();

		const auto ProxyTerm = ProxyTerms.FindRef(Node);

		if (LibraryFunction == nullptr || TargetPin == nullptr || DelegatePin == nullptr || ProxyTerm == nullptr)
		{
			CompilerContext.MessageLog.Error(*LOCTEXT("Malformed", "@@ is malformed").ToString(), Node);

			return;
		}

		if (TargetPin->LinkedTo.Num() > 0 && TargetPin->LinkedTo[0] != nullptr &&
			TargetPin->LinkedTo[0]->PinType.PinCategory == UEdGraphSchema_K2::PC_Interface)
		{
			CompilerContext.MessageLog.Error(*LOCTEXT("InterfaceTarget",
			                                          "@@ cannot be connected to an interface pin directly, cast it to an object first").
			                                 ToString(), TargetPin);

			return;
		}

		const auto TargetTerm = Context.NetMap.Find(FEdGraphUtilities::GetNetFromPin(TargetPin));

		const auto DelegateTerm = Context.NetMap.Find(DelegatePin);

		if (TargetTerm == nullptr || DelegateTerm == nullptr)
		{
			CompilerContext.MessageLog.Error(*LOCTEXT("TermMissing", "Failed to resolve the terms of @@").ToString(),
			                                 Node);

			return;
		}

		auto& ProxyStatement = Context.AppendStatementForNode(Node);

		ProxyStatement.Type = KCST_CallFunction;

		ProxyStatement.FunctionToCall = LibraryFunction;

		ProxyStatement.FunctionContext = nullptr;

		ProxyStatement.LHS = ProxyTerm;

		ProxyStatement.RHS.Add(*TargetTerm);

		ProxyStatement.RHS.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Name,
		                                       DelegateNode->MemberName.ToString()));

		ProxyStatement.RHS.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Int,
		                                       LexToString(DelegateNode->ParamCount)));

		ProxyStatement.RHS.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Int,
		                                       LexToString(static_cast<int32>(DelegateNode->SignatureHash))));

		auto& BindStatement = Context.AppendStatementForNode(Node);

		BindStatement.Type = KCST_BindDelegate;

		BindStatement.LHS = *DelegateTerm;

		BindStatement.RHS.Add(MakeLiteralTerm(Context, Node, UEdGraphSchema_K2::PC_Name,
		                                      UCSharpDelegateProxy::GetInvokeFunctionName().ToString()));

		BindStatement.RHS.Add(ProxyTerm);
	}

private:
	static FBPTerminal* MakeLiteralTerm(FKismetFunctionContext& Context, UEdGraphNode* Node, const FName& InCategory,
	                                    const FString& InValue)
	{
		const auto Term = Context.CreateLocalTerminal(ETerminalSpecification::TS_Literal);

		Term->bIsLiteral = true;

		Term->Type.PinCategory = InCategory;

		Term->Name = InValue;

		Term->Source = Node;

		return Term;
	}

	TMap<UEdGraphNode*, FBPTerminal*> ProxyTerms;
};

void UK2Node_CreateCSharpDelegate::AllocateDefaultPins()
{
	RefreshFromReflection();

	CreateTargetPin();

	if (const auto DelegatePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Delegate, GetDelegateOutPinName()))
	{
		DelegatePin->PinFriendlyName = LOCTEXT("DelegateOutPin", "Event");
	}

	UK2Node::AllocateDefaultPins();
}

FText UK2Node_CreateCSharpDelegate::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
	const auto Name = FText::FromString(!DisplayName.IsEmpty() ? DisplayName : MemberName.ToString());

	if (TitleType == ENodeTitleType::FullTitle)
	{
		return FText::Format(LOCTEXT("FullTitle", "Create Event (C#)\n{0}"), Name);
	}

	return FText::Format(LOCTEXT("Title", "Create Event: {0}"), Name);
}

FSlateIcon UK2Node_CreateCSharpDelegate::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetNodeTitleColor();

	return FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.Delegate_16x");
}

FLinearColor UK2Node_CreateCSharpDelegate::GetNodeTitleColor() const
{
	return GetDefault<UGraphEditorSettings>()->PureFunctionCallNodeTitleColor;
}

bool UK2Node_CreateCSharpDelegate::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin,
                                                          FString& OutReason) const
{
	if (MyPin != nullptr && OtherPin != nullptr && MyPin->PinName == GetDelegateOutPinName() &&
		OtherPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Delegate)
	{
		if (const auto Signature = FMemberReference::ResolveSimpleMemberReference<UFunction>(
			OtherPin->PinType.PinSubCategoryMemberReference))
		{
			if (!IsCompatibleWithDelegateSignature(Signature, &OutReason))
			{
				return true;
			}
		}
	}

	return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
}

bool UK2Node_CreateCSharpDelegate::IsActionFilteredOut(FBlueprintActionFilter const& Filter)
{
	if (Super::IsActionFilteredOut(Filter))
	{
		return true;
	}

	for (const auto Pin : Filter.Context.Pins)
	{
		if (Pin == nullptr || Pin->PinType.PinCategory != UEdGraphSchema_K2::PC_Delegate)
		{
			continue;
		}

		if (const auto Signature = FMemberReference::ResolveSimpleMemberReference<UFunction>(
			Pin->PinType.PinSubCategoryMemberReference))
		{
			if (!IsCompatibleWithDelegateSignature(Signature))
			{
				return true;
			}
		}
	}

	return false;
}

void UK2Node_CreateCSharpDelegate::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const
{
	UK2Node::ValidateNodeDuringCompilation(MessageLog);

	if (OwnerClass == nullptr)
	{
		MessageLog.Error(*FText::Format(LOCTEXT("OwnerClassMissing",
		                                        "The owner class of C# member {0} referenced by @@ could not be loaded"),
		                                FText::FromName(MemberName)).ToString(), this);

		return;
	}

	auto bDomainReady = false;

	WithScriptDomain([&bDomainReady]
	{
		bDomainReady = true;
	});

	if (!bDomainReady)
	{
		MessageLog.Note(*LOCTEXT("DomainNotReady", "C# runtime is not ready, @@ is compiled with its cached signature").
		                ToString(), this);

		return;
	}

	FCSharpBlueprintMemberInfo Info;

	if (!ResolveMember(Info))
	{
		MessageLog.Error(*FText::Format(LOCTEXT("MemberMissing",
		                                        "Blueprint-callable method {1} was not found in C# class {0} (@@)"),
		                                GetOwnerClassDisplayName(), FText::FromName(MemberName)).ToString(), this);

		return;
	}

	const auto Signature = FCSharpBlueprintMemberLibrary::BuildSignature(Info, TEXT("K2Node_CreateCSharpDelegateSignature"));

	if (Signature == nullptr)
	{
		MessageLog.Error(*LOCTEXT("UnsupportedSignature", "The C# signature of @@ contains a type not supported by Blueprint").
		                 ToString(), this);

		return;
	}

	ON_SCOPE_EXIT
	{
		FCSharpBlueprintMemberLibrary::DestroySignature(Signature);
	};

	if (FCSharpBlueprintMemberLibrary::ComputeSignatureHash(Signature) != SignatureHash ||
		Info.GetParamCount() != ParamCount)
	{
		MessageLog.Error(*LOCTEXT("SignatureChanged",
		                          "@@ does not match the current C# signature, right-click the node and Refresh Nodes, then recompile").
		                 ToString(), this);
	}
}

void UK2Node_CreateCSharpDelegate::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);
}

FNodeHandlingFunctor* UK2Node_CreateCSharpDelegate::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return new FKCHandler_CreateCSharpDelegate(CompilerContext);
}

ECSharpBlueprintMemberKind UK2Node_CreateCSharpDelegate::GetMemberKind() const
{
	return ECSharpBlueprintMemberKind::Function;
}

bool UK2Node_CreateCSharpDelegate::HandlesMemberKind(const ECSharpBlueprintMemberKind InKind) const
{
	return InKind == ECSharpBlueprintMemberKind::Function;
}

void UK2Node_CreateCSharpDelegate::InitializeFromSpawnData(const FCSharpBlueprintMemberSpawnData& InData)
{
	Super::InitializeFromSpawnData(InData);

	bIsPure = true;
}

FString UK2Node_CreateCSharpDelegate::GetMenuNameForSpawnData(const FCSharpBlueprintMemberSpawnData& InData) const
{
	return FString::Printf(TEXT("Create Event: %s"), *InData.DisplayName);
}

UEdGraphPin* UK2Node_CreateCSharpDelegate::GetDelegateOutPin() const
{
	return FindPin(GetDelegateOutPinName(), EGPD_Output);
}

UFunction* UK2Node_CreateCSharpDelegate::GetConnectedDelegateSignature() const
{
	const auto DelegatePin = GetDelegateOutPin();

	if (DelegatePin == nullptr || DelegatePin->LinkedTo.IsEmpty() || DelegatePin->LinkedTo[0] == nullptr)
	{
		return nullptr;
	}

	const auto LinkedPin = FBlueprintEditorUtils::FindFirstCompilerRelevantLinkedPin(DelegatePin->LinkedTo[0]);

	if (LinkedPin == nullptr || LinkedPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Delegate)
	{
		return nullptr;
	}

	return FMemberReference::ResolveSimpleMemberReference<UFunction>(LinkedPin->PinType.PinSubCategoryMemberReference);
}

bool UK2Node_CreateCSharpDelegate::IsCompatibleWithDelegateSignature(const UFunction* InSignature,
                                                                     FString* OutReason) const
{
	if (InSignature == nullptr)
	{
		return true;
	}

	FCSharpBlueprintMemberInfo Info;

	if (!ResolveMember(Info))
	{
		return true;
	}

	const auto Signature = FCSharpBlueprintMemberLibrary::BuildSignature(Info, TEXT("K2Node_CreateCSharpDelegateSignature"));

	if (Signature == nullptr)
	{
		return true;
	}

	const auto bCompatible = Signature->IsSignatureCompatibleWith(InSignature);

	FCSharpBlueprintMemberLibrary::DestroySignature(Signature);

	if (!bCompatible && OutReason != nullptr)
	{
		*OutReason = FText::Format(LOCTEXT("IncompatibleSignature",
		                                   "C# method {0} does not match the delegate signature (Blueprint Float maps to C# double)"),
		                           FText::FromName(MemberName)).ToString();
	}

	return bCompatible;
}

FName UK2Node_CreateCSharpDelegate::GetDelegateOutPinName()
{
	static const FName PinName(TEXT("OutputDelegate"));

	return PinName;
}

#undef LOCTEXT_NAMESPACE
