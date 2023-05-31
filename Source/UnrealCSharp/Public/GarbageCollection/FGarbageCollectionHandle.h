#pragma once

#include "TGarbageCollectionHandle.h"
#include "mono/utils/mono-forward.h"
using GarbageCollectionHandleType = MonoGCHandle;

using FGarbageCollectionHandle = TGarbageCollectionHandle<GarbageCollectionHandleType>;
