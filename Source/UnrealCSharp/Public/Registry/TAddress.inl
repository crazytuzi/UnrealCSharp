#pragma once

template <typename T, template<typename...> class IsType>
struct TAddress
{
	typedef T Type;

	template <typename U>
	struct TIsType
	{
		enum { value = IsType<U>::Value };
	};

	TAddress(void* InAddress, Type* InValue):
		Address(InAddress),
		Value(InValue)
	{
	}

	void* Address;

	Type* Value;
};
