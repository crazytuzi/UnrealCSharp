#pragma once

bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
{
	return A.Value == B.Value && A.Address == B.Address;
}

uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
{
	return HashCombineFast(GetTypeHash(InStructAddressBase.Value), GetTypeHash(InStructAddressBase.Address));
}
