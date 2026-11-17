#pragma once

#include "CoreMinimal.h"
#include "CSharpBlueprintMember.h"
#include "Reflection/Function/FManagedFunctionDescriptor.h"

/**
 * 蓝图变参调用 → C# 成员的运行时描述符。
 * 持有一个仅用于封送的签名 UFunction（Transient 包，不属于任何 UClass）。
 */
class FCSharpBlueprintCallDescriptor final : public FManagedFunctionDescriptor
{
public:
	typedef FManagedFunctionDescriptor Super;

public:
	FCSharpBlueprintCallDescriptor(const FCSharpBlueprintMemberInfo& InInfo, UFunction* InSignature,
	                               TUniquePtr<FMethodReflection>&& InAccessorMethod);

	virtual ~FCSharpBlueprintCallDescriptor() override;

public:
	/** 读取 Stack 上的变参、调用 C#、回写输出。返回后 Stack.Code 停在 EX_EndFunctionParms。 */
	void Call(UObject* InTarget, FFrame& InStack);

	/** 不调用 C#，只把 Stack 上剩余的变参安全地消费到 EX_EndFunctionParms。 */
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
	/** 找不到或 C# 未就绪返回 nullptr；负结果也会缓存，直到 Reset。 */
	FCSharpBlueprintCallDescriptor* Resolve(UClass* InClass, ECSharpBlueprintMemberKind InKind, const FName& InName,
	                                        int32 InParamCount);

	void Reset();

private:
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
};
