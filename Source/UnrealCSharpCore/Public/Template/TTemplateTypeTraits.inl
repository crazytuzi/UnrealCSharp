#pragma once

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
	template <auto Index>
	using Type = std::tuple_element_t<Index, std::tuple<T...>>;
};
