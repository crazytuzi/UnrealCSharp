#include "Reflection/FFieldReflection.h"

FFieldReflection::FFieldReflection(const FString& InName, MonoReflectionField* InReflectionField):
FReflection(InName),
ReflectionField(InReflectionField)
{
	if (ReflectionField != nullptr)
	{
		Field = ReflectionField->field;
	}
}

MonoClassField* FFieldReflection::GetField() const
{
	return Field;
}
