#pragma once

template <typename T>
struct TValue
{
	typedef T Type;

	explicit TValue(Type InValue):
		Value(InValue)
	{
	}

	Type Value;
};

template <typename T, typename R = void*>
struct TAddressValue : TValue<T>
{
	typedef R FAddressType;

	explicit TAddressValue(typename TValue<T>::Type InValue, FAddressType InAddress):
		TValue<T>(InValue),
		Address(InAddress)
	{
	}

	FAddressType Address;
};
