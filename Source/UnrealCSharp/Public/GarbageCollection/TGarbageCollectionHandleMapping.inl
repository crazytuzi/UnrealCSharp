#pragma once

#include "TMapping.inl"
#include "FGarbageCollectionHandle.h"

template <typename T>
class TGarbageCollectionHandleMapping : public TMapping<FGarbageCollectionHandle, T>
{
};
