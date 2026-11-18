#pragma once

#include "CoreMinimal.h"
#include "CSharpBlueprintMember.h"
#include "UObject/Object.h"
#include "CSharpDelegateProxy.generated.h"

UCLASS(Transient)
class UNREALCSHARPBLUEPRINTFUNCTION_API UCSharpDelegateProxy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Invoke();

	virtual void ProcessEvent(UFunction* Function, void* Parms) override;

public:
	static FName GetInvokeFunctionName();

	static UCSharpDelegateProxy* GetOrCreate(UObject* InTarget, ECSharpBlueprintMemberKind InKind,
	                                         const FName& InMemberName, int32 InParamCount, uint32 InSignatureHash);

	static void ResetRegistry();

public:
	TWeakObjectPtr<UObject> Target;

	ECSharpBlueprintMemberKind Kind = ECSharpBlueprintMemberKind::Function;

	FName MemberName;

	int32 ParamCount = 0;

	uint32 SignatureHash = 0;
};
