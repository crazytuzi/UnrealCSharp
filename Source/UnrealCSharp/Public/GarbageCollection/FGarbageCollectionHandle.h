#pragma once

#include "TGarbageCollectionHandle.inl"
#include "mono/utils/mono-forward.h"

using GarbageCollectionHandleType = MonoGCHandle;

using FGarbageCollectionHandle = TGarbageCollectionHandle<GarbageCollectionHandleType>;
