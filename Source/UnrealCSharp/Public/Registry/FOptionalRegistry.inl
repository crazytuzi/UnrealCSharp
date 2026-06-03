#pragma once

#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
template <auto IsMember>
auto FOptionalRegistry::AddReference(const FOptionalHelperValueMapping::FAddressType& InAddress,
                                     const FOptionalHelperValueMapping::ValueType& InValue,
                                     FClassReflection* InClass, const IManagedHandle InManagedHandle)
{
	const auto ManagedHandle = InClass->NewWeakRefGCHandle(InManagedHandle, true);

	if constexpr (IsMember)
	{
		Address2ManagedHandle.Add(InAddress, ManagedHandle);
	}

	ManagedHandle2Helper.Add(ManagedHandle, InValue);

	return true;
}
#endif
