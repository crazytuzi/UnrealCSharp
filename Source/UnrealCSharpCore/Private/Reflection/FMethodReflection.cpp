#include "Reflection/FMethodReflection.h"

FMethodReflection::FMethodReflection(const FString& InName, const bool InIsOverride, const int32 InParamCount, MonoReflectionMethod* InReflectionMethod):
FReflection(InName),
bIsOverride(InIsOverride),
ParamCount(InParamCount),
ReflectionMethod(InReflectionMethod)
{
	if (ReflectionMethod != nullptr)
	{
		Method = ReflectionMethod->method;
	}
}

bool FMethodReflection::IsOverride() const
{
	return bIsOverride;
}

int32 FMethodReflection::GetParamCount() const
{
	return ParamCount;
}

MonoMethod* FMethodReflection::GetMethod() const
{
	return Method;
}
