#include "Reflection/FFieldReflection.h"
#include "Reflection/FClassReflection.h"
#include "Domain/Script/IScriptDomain.h"

FFieldReflection::FFieldReflection(const FString& InName, const IManagedHandle InManagedField) :
	FReflection(InName),
	ManagedField(InManagedField)
{
}

FFieldReflection::~FFieldReflection()
{
	if (IManagedHandleIsValid(ManagedField))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(ManagedField);
		}

		ManagedField = InvalidManagedHandle;
	}
}

void FFieldReflection::SetValue(const FClassReflection* InClass, void* InValue) const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ScriptDomain->SetFieldStaticValue(InClass->GetManagedClass(), Name, InValue);
	}
}
