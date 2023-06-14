#pragma once

#include "Domain/FDomain.h"

template <typename T>
struct TPropertyGetClass
{
};

template <>
struct TPropertyGetClass<int32>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Int32_Class;
};

template <>
struct TPropertyGetClass<float>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Single_Class;
};
