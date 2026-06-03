#include "Reflection/FMethodReflection.h"
#include "Reflection/FReflectionRegistry.h"
#include "Domain/Mono/FMonoDomain.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"

FMethodReflection::FMethodReflection(const FString& InName, const int32 InParamCount,
                                     const IManagedReflectionMethod InManagedReflectionMethod,
                                     const bool InIsStatic, FClassReflection* InReturn,
                                     const TArray<FParamReflection*>& InParams,
                                     const TSet<FClassReflection*>& InAttributes,
                                     const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	FReflection(InName, InAttributes, InAttributeValues),
	ParamCount(InParamCount),
	ManagedReflectionMethod(InManagedReflectionMethod),
	bIsStatic(InIsStatic),
	Return(InReturn),
	Params(InParams)
{
#if WITH_MONO
	if (IManagedIsValid(ManagedReflectionMethod))
	{
		ManagedMethod = ManagedReflectionMethod->method;
	}
#else
	ManagedMethod = IManagedHandleToIManagedMethod(MANAGED_HANDLE_FROM_OBJECT(InManagedReflectionMethod));
#endif

	bIsUFunction = HasAttribute(FReflectionRegistry::Get().GetUFunctionAttributeClass());

	bIsOverride = bIsUFunction || HasAttribute(FReflectionRegistry::Get().GetOverrideAttributeClass());
}

FMethodReflection::~FMethodReflection()
{
	for (const auto Param : Params)
	{
		delete Param;
	}

	Params.Empty();

#if WITH_CORECLR
	if (IManagedIsValid(ManagedReflectionMethod))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(MANAGED_HANDLE_FROM_OBJECT(ManagedReflectionMethod));
		}

		ManagedReflectionMethod = INVALID_MANAGED;
	}
#endif
}

int32 FMethodReflection::GetParamCount() const
{
	return ParamCount;
}

IManagedMethod FMethodReflection::GetManagedMethod() const
{
	return ManagedMethod;
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
	return Params;
}

IManagedHandle FMethodReflection::Runtime_Invoke(const IManagedHandle InManagedHandle, void** InParams) const
{
	const auto ScriptDomain = IScriptDomain::Get();

	return ScriptDomain != nullptr
		       ? ScriptDomain->Invoke(InManagedHandle, ManagedMethod, ParamCount, InParams)
		       : InvalidManagedHandle;
}

#if WITH_MONO
IManagedObject FMethodReflection::Runtime_Invoke_Array(const IManagedHandle InManagedHandle,
                                                       const IManagedArray InParams) const
{
	return FMonoDomain::Runtime_Invoke_Array(ManagedMethod, IManagedHandleToIManagedObject(InManagedHandle), InParams);
}

void* FMethodReflection::Method_Get_Unmanaged_Thunk() const
{
	return FMonoDomain::Method_Get_Unmanaged_Thunk(ManagedMethod);
}
#endif
