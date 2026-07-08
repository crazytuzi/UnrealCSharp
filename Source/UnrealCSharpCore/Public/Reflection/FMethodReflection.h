#pragma once

#include "FReflection.h"
#include "FParamReflection.h"
#include "Domain/Script/IManagedHandle.h"

class FClassReflection;

class UNREALCSHARPCORE_API FMethodReflection : public FReflection
{
public:
	FMethodReflection(const FString& InName, int32 InParamCount,
	                  const IManagedHandle InManagedMethod,
	                  bool InIsStatic, FClassReflection* InReturn, const TArray<FParamReflection*>& InParams,
	                  const TSet<FClassReflection*>& InAttributes,
	                  const TMap<FClassReflection*, TArray<FString>>& InAttributeValues);

	~FMethodReflection();

public:
	int32 GetParamCount() const;

	IManagedHandle GetManagedMethod() const;

	bool IsOverride() const;

	bool IsUFunction() const;

	bool IsStatic() const;

	FClassReflection* GetReturn() const;

	const TArray<FParamReflection*>& GetParams() const;

public:
	IManagedHandle Runtime_Invoke(const IManagedHandle InManagedHandle = InvalidManagedHandle,
	                              void** InParams = nullptr) const;

private:
	int32 ParamCount{};

	IManagedHandle ManagedMethod{InvalidManagedHandle};

	bool bIsOverride{};

	bool bIsUFunction{};

	bool bIsStatic{};

	FClassReflection* Return{};

	TArray<FParamReflection*> Params;
};
