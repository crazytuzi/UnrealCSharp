#pragma once

#include "UEVersion.h"

template <typename T>
struct TTemplateTypeTraits
{
};

template <template<typename T> class Class, typename T>
struct TTemplateTypeTraits<Class<T>>
{
	using Type = T;
};

template <template<typename... T> class Class, typename... T>
struct TTemplateTypeTraits<Class<T...>>
{
#if STD_CPP_17
	template <auto Index>
#else
	template <SIZE_T Index>
#endif
	using Type = typename TTupleElement<Index, TTuple<T...>>::Type;
};
