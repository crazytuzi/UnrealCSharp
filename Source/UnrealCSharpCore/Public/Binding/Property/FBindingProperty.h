#pragma once

#include "Binding/TypeInfo/FBindingTypeInfo.h"
#include "EBindingPropertyAccess.h"

struct FBindingProperty : FBindingTypeInfo
{
	FBindingProperty(const FBindingTypeInfo& InTypeInfo, const FString& InName, const EBindingPropertyAccess& InAccess):
		FBindingTypeInfo(InTypeInfo),
		Name(InName),
		Access(InAccess)
	{
	}

	const FString& GetPropertyName() const
	{
		return Name;
	}

	EBindingPropertyAccess GetAccess() const
	{
		return Access;
	}

private:
	FString Name;

	EBindingPropertyAccess Access;
};
