#pragma once

#include "CoreMinimal.h"
#include "CSharpBlueprintMember.h"
#include "Reflection/Function/FManagedFunctionDescriptor.h"

class FCSharpBlueprintCallDescriptor final : public FManagedFunctionDescriptor
{
public:
	typedef FManagedFunctionDescriptor Super;

public:
	FCSharpBlueprintCallDescriptor(const FCSharpBlueprintMemberInfo& InInfo, UFunction* InSignature,
	                               TUniquePtr<FMethodReflection>&& InAccessorMethod);

	virtual ~FCSharpBlueprintCallDescriptor() override;

public:
	void Call(UObject* InTarget, FFrame& InStack);

	void CallWithParams(UObject* InTarget, void* InParams);

	static void SkipParams(FFrame& InStack);

	UFunction* GetSignature() const;

	uint32 GetSignatureHash() const;

private:
	UFunction* Signature;

	uint32 SignatureHash;

	const FMethodReflection* Method;

	TUniquePtr<FMethodReflection> AccessorMethod;
};

class FCSharpBlueprintCallCache
{
public:
	static FCSharpBlueprintCallCache& Get();

public:
	FCSharpBlueprintCallDescriptor* Resolve(UClass* InClass, ECSharpBlueprintMemberKind InKind, const FName& InName,
	                                        int32 InParamCount);

	void Reset();

private:
	void Prune();

	struct FKey
	{
		TWeakObjectPtr<UClass> Class;

		ECSharpBlueprintMemberKind Kind;

		FName Name;

		int32 ParamCount;

		bool operator==(const FKey& InOther) const
		{
			return Class == InOther.Class && Kind == InOther.Kind && Name == InOther.Name &&
				ParamCount == InOther.ParamCount;
		}

		friend uint32 GetTypeHash(const FKey& InKey)
		{
			return HashCombine(HashCombine(GetTypeHash(InKey.Class), GetTypeHash(InKey.Name)),
			                   HashCombine(static_cast<uint32>(InKey.Kind), static_cast<uint32>(InKey.ParamCount)));
		}
	};

	TMap<FKey, TUniquePtr<FCSharpBlueprintCallDescriptor>> Descriptors;

	FDelegateHandle PostGarbageCollectHandle;
};
