#pragma once

#include "Binding/TypeInfo/FBindingTypeInfoRegister.h"
#include "EBindingPropertyAccess.h"
#include "FBindingProperty.h"

struct FBindingPropertyRegister : FBindingTypeInfoRegister
{
	FBindingPropertyRegister(const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction,
	                         const FString& InName,
	                         const EBindingPropertyAccess& InAccess):
		FBindingTypeInfoRegister(InTypeInfoFunction),
		Name(InName),
		Access(InAccess)
	{
	}

	explicit operator FBindingProperty() const
	{
		return FBindingProperty(operator FBindingTypeInfo(), Name, Access);
	}

private:
	FString Name;

	EBindingPropertyAccess Access;
};
