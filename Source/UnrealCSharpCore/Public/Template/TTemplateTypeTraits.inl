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
	template <size_t Index>
#endif
	using Type = std::tuple_element_t<Index, std::tuple<T...>>;
};
