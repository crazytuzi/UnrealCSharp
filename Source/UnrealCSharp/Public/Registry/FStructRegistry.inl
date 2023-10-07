#pragma once

#include "UEVersion.h"

bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
{
	return A.Value == B.Value && A.Address == B.Address;
}

uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
{
#if UE_HASH_COMBINE_FAST
	return HashCombineFast(GetTypeHash(InStructAddressBase.Value), GetTypeHash(InStructAddressBase.Address));
#else
	return HashCombine(GetTypeHash(InStructAddressBase.Value), GetTypeHash(InStructAddressBase.Address));
#endif
}
