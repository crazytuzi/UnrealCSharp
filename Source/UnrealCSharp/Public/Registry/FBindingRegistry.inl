#pragma once

bool operator==(const FBindingAddress& A, const FBindingAddress& B)
{
	return A.Address == B.Address;
}

uint32 GetTypeHash(const FBindingAddress& InBindingAddress)
{
	return GetTypeHash(InBindingAddress.Address);
}
