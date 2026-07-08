#include "Reflection/FMethodReflection.h"
#include "Reflection/FReflectionRegistry.h"
#include "Domain/Script/IScriptDomain.h"

FMethodReflection::FMethodReflection(const FString& InName, const int32 InParamCount,
                                     const IManagedHandle InManagedMethod,
                                     const bool InIsStatic, FClassReflection* InReturn,
                                     const TArray<FParamReflection*>& InParams,
                                     const TSet<FClassReflection*>& InAttributes,
                                     const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	FReflection(InName, InAttributes, InAttributeValues),
	ParamCount(InParamCount),
	ManagedMethod(InManagedMethod),
	bIsStatic(InIsStatic),
	Return(InReturn),
	Params(InParams)
{
	ManagedMethod = InManagedMethod;

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

	if (IManagedHandleIsValid(ManagedMethod))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(ManagedMethod);
		}

		ManagedMethod = InvalidManagedHandle;
	}
}

int32 FMethodReflection::GetParamCount() const
{
	return ParamCount;
}

IManagedHandle FMethodReflection::GetManagedMethod() const
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
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->Invoke(InManagedHandle, ManagedMethod, ParamCount, InParams);
	}

	return InvalidManagedHandle;
}
