#pragma once

#include "TPropertyDescriptor.inl"

template <typename T>
class TCompoundPropertyDescriptor : public TPropertyDescriptor<T, false>
{
public:
	using TPropertyDescriptor<T, false>::TPropertyDescriptor;
};
