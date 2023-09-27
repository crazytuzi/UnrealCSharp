#pragma once

template <typename T>
struct TAddress
{
	typedef T Type;

	TAddress(void* InAddress, Type InValue):
		Address(InAddress),
		Value(InValue)
	{
	}

	void* Address;

	Type Value;
};

template <typename T, template<typename...> class IsType>
struct TTypeAddress : TAddress<T>
{
	template <typename U>
	struct TIsType
	{
		enum { value = IsType<U>::Value };
	};

	using TAddress<T>::TAddress;
};
