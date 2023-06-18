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
