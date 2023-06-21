#pragma once

template <typename T>
struct TIsUStruct
{
	template <typename U>
	static std::true_type Test(decltype(&U::StaticStruct));

	template <typename U>
	static std::false_type Test(...);

	enum { Value = std::is_same_v<decltype(Test<T>(0)), std::true_type> };
};
