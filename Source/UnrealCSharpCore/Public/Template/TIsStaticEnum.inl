#pragma once

template <typename T>
struct TIsStaticEnum
{
	template <typename U>
	static std::true_type Test(decltype(StaticEnum<U>())*);

	template <typename U>
	static std::false_type Test(...);

	enum { Value = std::is_same_v<decltype(Test<T>(nullptr)), std::true_type> };
};
