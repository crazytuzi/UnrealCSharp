#pragma once

#include "Binding/TypeInfo/FBindingTypeInfoRegister.h"
#include "EBindingPropertyAccess.h"
#include "FBindingProperty.h"

struct FBindingPropertyRegister : FBindingTypeInfoRegister
{
	FBindingPropertyRegister(const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction,
	                         const FString& InName,
	                         const EBindingPropertyAccess& InPropertyAccess,
	                         const TOptional<EPropertyInteract>& InPropertyInteract):
		FBindingTypeInfoRegister(InTypeInfoFunction),
		Name(InName),
		PropertyAccess(InPropertyAccess),
		PropertyInteract(InPropertyInteract)
	{
	}

	explicit operator FBindingProperty() const
	{
		return FBindingProperty(operator FBindingTypeInfo(), Name, PropertyAccess,
		                        PropertyInteract.Get(EPropertyInteract::None));
	}

private:
	FString Name;

	EBindingPropertyAccess PropertyAccess;

	TOptional<EPropertyInteract> PropertyInteract;
};
