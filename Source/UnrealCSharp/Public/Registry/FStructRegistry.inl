#pragma once

#include "UEVersion.h"

bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
{
	return A.ScriptStruct == B.ScriptStruct && A.Address == B.Address;
}

uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
{
#if UE_HASH_COMBINE_FAST
	return HashCombineFast(GetTypeHash(InStructAddressBase.ScriptStruct), GetTypeHash(InStructAddressBase.Address));
#else
	return HashCombine(GetTypeHash(InStructAddressBase.ScriptStruct), GetTypeHash(InStructAddressBase.Address));
#endif
}
