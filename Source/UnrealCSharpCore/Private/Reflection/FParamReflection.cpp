#include "Reflection/FParamReflection.h"
#include "Reflection/FReflectionRegistry.h"

FParamReflection::FParamReflection(const FString& InName, const bool InIsRef, MonoReflectionType* InReflectionType):
	FReflection(InName),
	bIsRef(InIsRef),
	ReflectionType(InReflectionType)
{
}

bool FParamReflection::IsRef() const
{
	return bIsRef;
}

FClassReflection* FParamReflection::GetReflectionType() const
{
	return FReflectionRegistry::Get().GetClass(ReflectionType);
}
