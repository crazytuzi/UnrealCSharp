#pragma once

template <class T>
struct TAccessPrivate
{
	static inline typename T::Type Value;
};
