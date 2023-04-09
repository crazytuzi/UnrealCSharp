#pragma once

bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
{
	return A.Owner == B.Owner && A.Address == B.Address;
}

uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
{
	return HashCombineFast(GetTypeHash(InStructAddressBase.Owner), GetTypeHash(InStructAddressBase.Address));
}
