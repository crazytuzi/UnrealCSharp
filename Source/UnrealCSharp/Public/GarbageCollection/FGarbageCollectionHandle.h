#pragma once

#include "TGarbageCollectionHandle.h"

using GarbageCollectionHandleType = MonoGCHandle;

using FGarbageCollectionHandle = TGarbageCollectionHandle<GarbageCollectionHandleType>;
