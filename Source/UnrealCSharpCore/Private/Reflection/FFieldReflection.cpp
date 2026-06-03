#include "Reflection/FFieldReflection.h"
#include "Reflection/FClassReflection.h"
#include "Domain/Script/IManagedTypes.h"
#include "Domain/Script/IScriptDomain.h"

FFieldReflection::FFieldReflection(const FString& InName, const IManagedReflectionField InManagedReflectionField):
	FReflection(InName),
	ManagedReflectionField(InManagedReflectionField)
{
}

FFieldReflection::~FFieldReflection()
{
	if (IManagedIsValid(ManagedReflectionField))
	{
#if WITH_CORECLR
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(MANAGED_HANDLE_FROM_OBJECT(ManagedReflectionField));
		}
#endif

		ManagedReflectionField = INVALID_MANAGED;
	}
}

void FFieldReflection::SetValue(const FClassReflection* InClass, void* InValue) const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ScriptDomain->SetFieldStaticValue(InClass->GetManagedClass(), Name, InValue);
	}
}
