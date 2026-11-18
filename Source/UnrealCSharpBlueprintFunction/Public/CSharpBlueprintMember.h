#pragma once

#include "CoreMinimal.h"

class FClassReflection;
class FMethodReflection;
class FPropertyReflection;
class FReflection;

enum class ECSharpBlueprintMemberKind : uint8
{
	Function,
	PropertyGet,
	PropertySet
};

struct UNREALCSHARPBLUEPRINTFUNCTION_API FCSharpBlueprintMemberInfo
{
	ECSharpBlueprintMemberKind Kind = ECSharpBlueprintMemberKind::Function;

	FClassReflection* ClassReflection = nullptr;

	UClass* OwnerClass = nullptr;

	FMethodReflection* Method = nullptr;

	FPropertyReflection* Property = nullptr;

	bool IsValid() const;

	const FReflection* GetReflection() const;

	FString GetMemberName() const;

	int32 GetParamCount() const;
};

class UNREALCSHARPBLUEPRINTFUNCTION_API FCSharpBlueprintMemberLibrary
{
public:
	static bool IsScriptDomainReady();

	static bool IsRuntimeActive();

public:
	static bool IsBlueprintCallable(const FMethodReflection* InMethod);

	static bool IsBlueprintPure(const FMethodReflection* InMethod);

	static bool IsBlueprintReadable(const FPropertyReflection* InProperty);

	static bool IsBlueprintWritable(const FPropertyReflection* InProperty);

public:
	static FClassReflection* GetOverrideClassReflection(UClass* InClass);

	static UClass* FindOwnerClass(const FClassReflection* InClassReflection);

	static void ForEachOverrideClass(const TFunctionRef<void(FClassReflection*)>& InFunction);

	static void ForEachBlueprintMember(FClassReflection* InClassReflection, UClass* InOwnerClass,
	                                   const TFunctionRef<void(const FCSharpBlueprintMemberInfo&)>& InFunction);

	static bool Resolve(UClass* InClass, ECSharpBlueprintMemberKind InKind, const FName& InName, int32 InParamCount,
	                    FCSharpBlueprintMemberInfo& OutInfo);

	static bool ResolveDeclared(FClassReflection* InClassReflection, UClass* InOwnerClass,
	                            ECSharpBlueprintMemberKind InKind, const FName& InName, int32 InParamCount,
	                            FCSharpBlueprintMemberInfo& OutInfo);

public:
	static FString GetDisplayName(const FCSharpBlueprintMemberInfo& InInfo);

	static FString GetCategory(const FCSharpBlueprintMemberInfo& InInfo);

	static FString GetToolTip(const FCSharpBlueprintMemberInfo& InInfo);

public:
	static UFunction* BuildSignature(const FCSharpBlueprintMemberInfo& InInfo, const FName& InBaseName);

	static void DestroySignature(UFunction* InFunction);

	static uint32 ComputeSignatureHash(const UFunction* InFunction);

	static TUniquePtr<FMethodReflection> MakeAccessorMethod(const FCSharpBlueprintMemberInfo& InInfo);
};
