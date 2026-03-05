#include "Reflection/FFieldReflection.h"
#include "Reflection/FClassReflection.h"

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

void FFieldReflection::SetValue(const FClassReflection* InClass, void* InValue) const
{
	FMonoDomain::Field_Static_Set_Value(InClass != nullptr ? InClass->GetVTable() : nullptr, Field, InValue);
}

MonoObject* FFieldReflection::GetValue(MonoObject* InMonoObject) const
{
	return FMonoDomain::Field_Get_Value_Object(Field, InMonoObject);
}
