#pragma once

#include "Template/TIsTEnumAsByte.inl"

template <typename T>
struct TIsPrimitive
{
	enum
	{
		Value = std::is_same_v<std::decay_t<T>, bool> ||
		std::is_same_v<std::decay_t<T>, int8> ||
		std::is_same_v<std::decay_t<T>, int16> ||
		std::is_same_v<std::decay_t<T>, int32> ||
		std::is_same_v<std::decay_t<T>, int64> ||
		std::is_same_v<std::decay_t<T>, uint8> ||
		std::is_same_v<std::decay_t<T>, uint16> ||
		std::is_same_v<std::decay_t<T>, uint32> ||
		std::is_same_v<std::decay_t<T>, uint64> ||
		std::is_same_v<std::decay_t<T>, float> ||
		std::is_same_v<std::decay_t<T>, double> ||
		TIsEnum<std::decay_t<T>>::Value ||
		TIsEnumClass<std::decay_t<T>>::Value ||
		TIsTEnumAsByte<std::decay_t<T>>::Value
	};
};
