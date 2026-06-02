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
	const auto ManagedHandle = FReflectionRegistry::Get().GetClass(InScriptStruct)->NewWeakRefGCHandle(
		InManagedHandle, true);

<<<<<<< HEAD
	ManagedHandle2StructAddress.Add(ManagedHandle, {
		                                InScriptStruct,
		                                const_cast<void*>(InStruct),
		                                IsNeedFree
	                                });
=======
	StructAddress2GarbageCollectionHandle.Add(
		FStructAddressBase(InScriptStruct, const_cast<void*>(InStruct)), GarbageCollectionHandle);

	GarbageCollectionHandle2StructAddress.Add(GarbageCollectionHandle, {
		                                          InScriptStruct,
		                                          const_cast<void*>(InStruct),
		                                          IsNeedFree
	                                          });
>>>>>>> zjt9363/fix/struct-registry-and-remove-cleanup

	return true;
}
