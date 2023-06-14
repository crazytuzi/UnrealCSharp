#pragma once

#include "FBindingTypeInfo.h"

enum class EBindingPropertyAccess
{
	None = 0b00,
	OnlyRead = 0b01,
	OnlyWrite = 0b10,
	ReadAndWrite = OnlyRead | OnlyWrite
};

struct FBindingProperty : FBindingTypeInfo
{
	FString Name;

	EBindingPropertyAccess Access;

	FBindingProperty() = default;

	FBindingProperty(FTypeInfo* InTypeInfo, const FString& InName, const EBindingPropertyAccess& InAccess):
		FBindingTypeInfo{InTypeInfo}, Name(InName), Access(InAccess)
	{
	}
};
