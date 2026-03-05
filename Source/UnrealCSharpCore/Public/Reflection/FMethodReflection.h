#pragma once

#include "FReflection.h"
#include "FParamReflection.h"
#include "Domain/FMonoDomain.h"

class FClassReflection;

class UNREALCSHARPCORE_API FMethodReflection : public FReflection
{
public:
	FMethodReflection(const FString& InName, int32 InParamCount, MonoReflectionMethod* InReflectionMethod,
	                  bool InIsStatic, FClassReflection* InReturn, const TArray<FParamReflection*>& InParams,
	                  const TSet<FClassReflection*>& InAttributes,
	                  const TMap<FClassReflection*, TArray<FString>>& InAttributeValues
	);

	~FMethodReflection();

public:
	int32 GetParamCount() const;

	MonoReflectionMethod* GetReflectionMethod() const;

	MonoMethod* GetMethod() const;

	bool IsOverride() const;

	bool IsUFunction() const;

	bool IsStatic() const;

	FClassReflection* GetReturn() const;

	const TArray<FParamReflection*>& GetParams() const;

public:
	MonoObject* Runtime_Invoke(void* InMonoObject = nullptr, void** InParams = nullptr) const;

	MonoObject* Runtime_Invoke_Array(void* InMonoObject, MonoArray* InParams) const;

	void* Method_Get_Unmanaged_Thunk() const;

private:
	int32 ParamCount{};

	MonoReflectionMethod* ReflectionMethod{};

	MonoMethod* Method{};

	bool bIsOverride{};

	bool bIsUFunction{};

	bool bIsStatic{};

	FClassReflection* Return{};

	TArray<FParamReflection*> ParamReflections;
};
