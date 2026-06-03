#include "Reflection/FParamReflection.h"

FParamReflection::FParamReflection(const FString& InName, const bool InIsRef, FClassReflection* InReflectionType):
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
	return ReflectionType;
}
