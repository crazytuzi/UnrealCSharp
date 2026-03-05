#include "Reflection/FPropertyReflection.h"
#include "Reflection/FReflectionRegistry.h"

FPropertyReflection::FPropertyReflection(const FString& InName, MonoReflectionProperty* InReflectionProperty,
                                         MonoReflectionType* InReflectionType,
                                         const TSet<FClassReflection*>& InAttributes,
                                         const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	FReflection(InName, InAttributes, InAttributeValues),
	ReflectionProperty(InReflectionProperty)
{
	if (ReflectionProperty != nullptr)
	{
		Property = ReflectionProperty->property;

		ReflectionType = InReflectionType;
	}

	bIsUProperty = Attributes.Contains(FReflectionRegistry::Get().GetUPropertyAttributeClass());
}

MonoReflectionProperty* FPropertyReflection::GetReflectionProperty() const
{
	return ReflectionProperty;
}

MonoProperty* FPropertyReflection::GetProperty() const
{
	return Property;
}

FClassReflection* FPropertyReflection::GetReflectionType() const
{
	return FReflectionRegistry::Get().GetClass(ReflectionType);
}

bool FPropertyReflection::IsUProperty() const
{
	return bIsUProperty;
}

void FPropertyReflection::SetValue(void* InMonoObject, void** InParams, MonoObject** InExc) const
{
	FMonoDomain::Property_Set_Value(Property, InMonoObject, InParams, InExc);
}

MonoObject* FPropertyReflection::GetValue(void* InMonoObject, void** InParams, MonoObject** InExc) const
{
	return FMonoDomain::Property_Get_Value(Property, InMonoObject, InParams, InExc);
}
