#pragma once

#include "TAccessPrivate.inl"

template <class T, typename T::Type Value>
struct TAccessPrivateStub
{
	struct FAccessPrivateStub
	{
		FAccessPrivateStub()
		{
			TAccessPrivate<T>::Value = Value;
		}
	};

	static inline FAccessPrivateStub AccessPrivateStub;
};
