#pragma once

#include "Reflection/FReflectionRegistry.h"

bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
{
	return A.Value == B.Value && A.Address == B.Address;
}

uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
{
	return HashCombineFast(GetTypeHash(InStructAddressBase.Value), GetTypeHash(InStructAddressBase.Address));
}

template <auto IsNeedFree>
auto FStructRegistry::AddReference(UScriptStruct* InScriptStruct, const void* InStruct,
                                   const IManagedHandle InManagedHandle)
{
	StructAddress2ManagedHandle.Add(
		FStructAddressBase(InScriptStruct, const_cast<void*>(InStruct)), InManagedHandle);

	ManagedHandle2StructAddress.Add(InManagedHandle, {
		                                InScriptStruct,
		                                const_cast<void*>(InStruct),
		                                IsNeedFree
	                                });

	return true;
}
