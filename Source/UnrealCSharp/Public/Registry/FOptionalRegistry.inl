#pragma once

#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
template <auto IsMember>
auto FOptionalRegistry::AddReference(const FOptionalHelperValueMapping::FAddressType& InAddress,
                                     const FOptionalHelperValueMapping::ValueType& InValue, MonoClass* InMonoClass, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoClass, InMonoObject, true);

	if constexpr (IsMember)
	{
		OptionalAddress2GarbageCollectionHandle.Add(InAddress, GarbageCollectionHandle);
	}

	OptionalGarbageCollectionHandle2Helper.Add(GarbageCollectionHandle, InValue);

	return true;
}
#endif
