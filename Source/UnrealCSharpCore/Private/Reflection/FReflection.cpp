#include "Reflection/FReflection.h"

FReflection::FReflection(const FString& InName):
Name(InName)
{
}

const FString& FReflection::GetName()
{
	return Name;
}
