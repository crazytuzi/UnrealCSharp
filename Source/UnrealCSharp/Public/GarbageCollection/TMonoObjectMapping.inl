#pragma once

#include "TMapping.inl"
#include "mono/metadata/object-forward.h"

template <typename T>
class TMonoObjectMapping : public TMapping<const MonoObject*, T>
{
};
