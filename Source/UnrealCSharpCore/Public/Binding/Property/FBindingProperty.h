#pragma once

#include "Binding/TypeInfo/FBindingTypeInfo.h"

enum class EBindingPropertyAccess
{
	None = 0b00,
	OnlyRead = 0b01,
	OnlyWrite = 0b10,
	ReadAndWrite = OnlyRead | OnlyWrite
};

struct FBindingProperty : FBindingTypeInfo
{
	FBindingProperty() = default;

	FBindingProperty(FTypeInfo* InTypeInfo, const FString& InName, const EBindingPropertyAccess& InAccess):
		FBindingTypeInfo{InTypeInfo},
		Name(InName),
		Access(InAccess)
	{
	}

	FString GetPropertyName() const
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
