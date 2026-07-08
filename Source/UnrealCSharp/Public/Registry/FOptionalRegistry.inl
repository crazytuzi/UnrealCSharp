#pragma once

#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
template <auto IsMember>
auto FOptionalRegistry::AddReference(const FOptionalHelperValueMapping::FAddressType& InAddress,
                                     const FOptionalHelperValueMapping::ValueType& InValue,
                                     FClassReflection* InClass, const IManagedHandle InManagedHandle)
{
	if constexpr (IsMember)
	{
		Address2ManagedHandle.Add(InAddress, InManagedHandle);
	}

	ManagedHandle2Helper.Add(InManagedHandle, InValue);

	return true;
}
#endif
