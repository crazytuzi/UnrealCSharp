#pragma once

#include "Domain/FDomain.h"

template <typename>
class TPropertyGetClass
{
};

template <>
class TPropertyGetClass<int32>
{
public:
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Int32_Class;
};

template <>
class TPropertyGetClass<float>
{
public:
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Single_Class;
};
