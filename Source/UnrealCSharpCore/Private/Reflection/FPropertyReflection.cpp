#include "Reflection/FPropertyReflection.h"

FPropertyReflection::FPropertyReflection(const FString& InName, MonoReflectionProperty* InReflectionProperty):
FReflection(InName),
ReflectionProperty(InReflectionProperty)
{
	if (ReflectionProperty != nullptr)
	{
		Property = ReflectionProperty->property;
	}
}

MonoProperty* FPropertyReflection::GetProperty() const
{
	return Property;
}
