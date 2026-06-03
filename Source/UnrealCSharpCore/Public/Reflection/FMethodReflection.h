#pragma once

#include "FReflection.h"
#include "FParamReflection.h"
#include "Domain/Script/IManagedTypes.h"

class FClassReflection;

class UNREALCSHARPCORE_API FMethodReflection : public FReflection
{
public:
	FMethodReflection(const FString& InName, int32 InParamCount,
	                  const IManagedReflectionMethod InManagedReflectionMethod,
	                  bool InIsStatic, FClassReflection* InReturn, const TArray<FParamReflection*>& InParams,
	                  const TSet<FClassReflection*>& InAttributes,
	                  const TMap<FClassReflection*, TArray<FString>>& InAttributeValues);

	~FMethodReflection();

public:
	int32 GetParamCount() const;

	IManagedMethod GetManagedMethod() const;

	bool IsOverride() const;

	bool IsUFunction() const;

	bool IsStatic() const;

	FClassReflection* GetReturn() const;

	const TArray<FParamReflection*>& GetParams() const;

public:
	IManagedHandle Runtime_Invoke(const IManagedHandle InManagedHandle = InvalidManagedHandle,
	                              void** InParams = nullptr) const;

#if WITH_MONO
	IManagedObject Runtime_Invoke_Array(const IManagedHandle InManagedHandle, const IManagedArray InParams) const;

	void* Method_Get_Unmanaged_Thunk() const;
#endif

private:
	int32 ParamCount{};

	IManagedReflectionMethod ManagedReflectionMethod{INVALID_MANAGED};

	IManagedMethod ManagedMethod{INVALID_MANAGED};

	bool bIsOverride{};

	bool bIsUFunction{};

	bool bIsStatic{};

	FClassReflection* Return{};

	TArray<FParamReflection*> Params;
};
