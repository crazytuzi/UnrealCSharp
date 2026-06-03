#pragma once

#include "TMapping.inl"
#include "Domain/Script/IManagedHandle.h"

template <typename T>
class TManagedHandleMapping : public TMapping<IManagedHandle, T>
{
};
