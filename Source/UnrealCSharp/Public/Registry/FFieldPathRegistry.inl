#pragma once

template <auto IsNeedFree, auto IsMember>
auto FFieldPathRegistry::AddReference(FClassReflection* InClass, const IManagedHandle InManagedHandle,
                                      FFieldPath* InValue)
{
	if constexpr (IsMember)
	{
		Address2ManagedHandle.Add(InValue, InManagedHandle);
	}

	ManagedHandle2Value.Add(InManagedHandle, FFieldPathAddress(InValue, IsNeedFree));

	return true;
}
