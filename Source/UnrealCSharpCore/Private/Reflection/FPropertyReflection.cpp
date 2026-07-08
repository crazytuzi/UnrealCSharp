#include "Reflection/FPropertyReflection.h"
#include "Reflection/FReflectionRegistry.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"

FPropertyReflection::FPropertyReflection(const FString& InName,
                                         const IManagedHandle InManagedProperty,
                                         FClassReflection* InReflectionType,
                                         const TSet<FClassReflection*>& InAttributes,
                                         const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	FReflection(InName, InAttributes, InAttributeValues),
	ManagedProperty(InManagedProperty),
	ReflectionType(InReflectionType)
{
	bIsUProperty = Attributes.Contains(FReflectionRegistry::Get().GetUPropertyAttributeClass());
}

FPropertyReflection::~FPropertyReflection()
{
	if (IManagedHandleIsValid(ManagedProperty))
	{
#if WITH_CORECLR
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(ManagedProperty);
		}
#endif

		ManagedProperty = InvalidManagedHandle;
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
