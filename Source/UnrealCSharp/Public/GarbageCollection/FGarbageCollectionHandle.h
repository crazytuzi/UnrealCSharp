#pragma once

#include "TGarbageCollectionHandle.inl"
#include "mono/utils/mono-forward.h"

using GarbageCollectionHandleType = MonoGCHandle;

using FGarbageCollectionHandle = TGarbageCollectionHandle<GarbageCollectionHandleType>;

inline uint32 GetTypeHash(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	return GetTypeHash(static_cast<GarbageCollectionHandleType>(InGarbageCollectionHandle));
}
