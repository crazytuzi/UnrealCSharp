#include "Reflection/FMethodReflection.h"
#include "Reflection/FReflectionRegistry.h"

FMethodReflection::FMethodReflection(const FString& InName, const int32 InParamCount,
                                     MonoReflectionMethod* InReflectionMethod,
                                     const bool InIsStatic, FClassReflection* InReturn,
                                     const TArray<FParamReflection*>& InParamReflections,
                                     const TSet<FClassReflection*>& InAttributes,
                                     const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	FReflection(InName, InAttributes, InAttributeValues),
	ParamCount(InParamCount),
	ReflectionMethod(InReflectionMethod),
	bIsStatic(InIsStatic),
	Return(InReturn),
	ParamReflections(InParamReflections)
{
	if (ReflectionMethod != nullptr)
	{
		Method = ReflectionMethod->method;
	}

	bIsUFunction = HasAttribute(FReflectionRegistry::Get().GetUFunctionAttributeClass());

	bIsOverride = bIsUFunction || HasAttribute(FReflectionRegistry::Get().GetOverrideAttributeClass());
}

FMethodReflection::~FMethodReflection()
{
	for (const auto Param : ParamReflections)
	{
		delete Param;
	}

	ParamReflections.Empty();
}

int32 FMethodReflection::GetParamCount() const
{
	return ParamCount;
}

MonoReflectionMethod* FMethodReflection::GetReflectionMethod() const
{
	return ReflectionMethod;
}

MonoMethod* FMethodReflection::GetMethod() const
{
	return Method;
}

bool FMethodReflection::IsOverride() const
{
	return bIsOverride;
}

bool FMethodReflection::IsUFunction() const
{
	return bIsUFunction;
}

bool FMethodReflection::IsStatic() const
{
	return bIsStatic;
}

FClassReflection* FMethodReflection::GetReturn() const
{
	return Return;
}

const TArray<FParamReflection*>& FMethodReflection::GetParams() const
{
	return ParamReflections;
}

MonoObject* FMethodReflection::Runtime_Invoke(void* InMonoObject, void** InParams) const
{
	return FMonoDomain::Runtime_Invoke(Method, InMonoObject, InParams);
}

MonoObject* FMethodReflection::Runtime_Invoke_Array(void* InMonoObject, MonoArray* InParams) const
{
	return FMonoDomain::Runtime_Invoke_Array(Method, InMonoObject, InParams);
}

void* FMethodReflection::Method_Get_Unmanaged_Thunk() const
{
	return FMonoDomain::Method_Get_Unmanaged_Thunk(Method);
}
