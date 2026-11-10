#pragma once

template <typename T>
struct TFunctionPointer
{
	explicit TFunctionPointer(const T& InFunction)
	{
		if constexpr (std::is_null_pointer_v<T>)
		{
			Value = nullptr;
		}
		else
		{
			Value = const_cast<void*>(reinterpret_cast<const void*>(InFunction));
		}
	}

	void* Value;
};
