#pragma once

#include "Domain/FDomain.h"

template <typename T>
struct TPropertyGetClass
{
};

template <>
struct TPropertyGetClass<uint8>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Byte_Class;
};

template <>
struct TPropertyGetClass<uint16>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_UInt16_Class;
};

template <>
struct TPropertyGetClass<uint32>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_UInt32_Class;
};

template <>
struct TPropertyGetClass<uint64>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_UInt64_Class;
};

template <>
struct TPropertyGetClass<int8>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_SByte_Class;
};

template <>
struct TPropertyGetClass<int16>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Int16_Class;
};

template <>
struct TPropertyGetClass<int32>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Int32_Class;
};

template <>
struct TPropertyGetClass<int64>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Int64_Class;
};

template <>
struct TPropertyGetClass<bool>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Boolean_Class;
};

template <>
struct TPropertyGetClass<float>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Single_Class;
};

template <>
struct TPropertyGetClass<double>
{
	static inline MonoClass*(FDomain::*GetClass)() const = &FDomain::Get_Double_Class;
};
