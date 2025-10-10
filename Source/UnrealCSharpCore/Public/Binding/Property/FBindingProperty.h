#pragma once

#include "Binding/TypeInfo/FBindingTypeInfo.h"
#include "EBindingPropertyAccess.h"
#include "EPropertyInteract.h"

struct FBindingProperty : FBindingTypeInfo
{
	FBindingProperty(const FBindingTypeInfo& InTypeInfo, const FString& InName,
	                 const EBindingPropertyAccess& InPropertyAccess, const EPropertyInteract& InPropertyInteract):
		FBindingTypeInfo(InTypeInfo),
		Name(InName),
		PropertyAccess(InPropertyAccess),
		PropertyInteract(InPropertyInteract)
	{
	}

	const FString& GetPropertyName() const
	{
		return Name;
	}

	EBindingPropertyAccess GetPropertyAccess() const
	{
		return PropertyAccess;
	}

	EPropertyInteract GetPropertyInteract() const
	{
		return PropertyInteract;
	}

private:
	FString Name;

	EBindingPropertyAccess PropertyAccess;

	EPropertyInteract PropertyInteract;
};
