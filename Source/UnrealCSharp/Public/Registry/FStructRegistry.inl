#pragma once

bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
{
	return A.Value == B.Value && A.Address == B.Address;
}

uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
{
	return HashCombineFast(GetTypeHash(InStructAddressBase.Value), GetTypeHash(InStructAddressBase.Address));
}

template <auto IsNeedFree>
auto FStructRegistry::AddReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2StructAddress.Add(GarbageCollectionHandle, {
		                                          InScriptStruct,
		                                          const_cast<void*>(InStruct),
		                                          IsNeedFree
	                                          });

	return true;
}
