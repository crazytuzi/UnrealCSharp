#include "Reflection/FPropertyReflection.h"
#include "Reflection/FReflectionRegistry.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"

FPropertyReflection::FPropertyReflection(const FString& InName,
                                         const IManagedReflectionProperty InManagedReflectionProperty,
                                         FClassReflection* InReflectionType,
                                         const TSet<FClassReflection*>& InAttributes,
                                         const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	FReflection(InName, InAttributes, InAttributeValues),
	ManagedReflectionProperty(InManagedReflectionProperty),
	ReflectionType(InReflectionType)
{
	bIsUProperty = Attributes.Contains(FReflectionRegistry::Get().GetUPropertyAttributeClass());
}

FPropertyReflection::~FPropertyReflection()
{
	if (IManagedIsValid(ManagedReflectionProperty))
	{
#if WITH_CORECLR
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(MANAGED_HANDLE_FROM_OBJECT(ManagedReflectionProperty));
		}
#endif

		ManagedReflectionProperty = INVALID_MANAGED;
	}
}

FClassReflection* FPropertyReflection::GetReflectionType() const
{
	return ReflectionType;
}

bool FPropertyReflection::IsUProperty() const
{
	return bIsUProperty;
}

void FPropertyReflection::SetValue(const IManagedHandle InManagedHandle, void** InParams) const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ScriptDomain->SetPropertyValue(InManagedHandle, Name, InParams);
	}
}

void* FPropertyReflection::GetValue(const IManagedHandle InManagedHandle, void** InParams) const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->GetPropertyValue(InManagedHandle, Name, InParams);
	}

	return nullptr;
}
