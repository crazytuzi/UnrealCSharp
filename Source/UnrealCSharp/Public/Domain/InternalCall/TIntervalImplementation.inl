#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Binding/ScriptStruct/TScriptStruct.inl"

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_SizeImplementation(const MonoObject* InMonoObject)
{
	const auto Interval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Interval != nullptr)
	{
		return Interval->Size();
	}

	return U();
}

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto Interval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Interval != nullptr)
	{
		return Interval->IsValid();
	}

	return false;
}

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_ContainsImplementation(const MonoObject* InMonoObject, const U Element)
{
	const auto Interval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Interval != nullptr)
	{
		return Interval->Contains(Element);
	}

	return false;
}

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_ExpandImplementation(const MonoObject* InMonoObject, const U ExpandAmount)
{
	const auto Interval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Interval != nullptr)
	{
		return Interval->Expand(ExpandAmount);
	}
}

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_IncludeImplementation(const MonoObject* InMonoObject, const U X)
{
	const auto Interval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Interval != nullptr)
	{
		return Interval->Include(X);
	}
}

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_InterpolateImplementation(const MonoObject* InMonoObject,
                                                                       const float Alpha)
{
	const auto Interval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Interval != nullptr)
	{
		return Interval->Interpolate(Alpha);
	}

	return U();
}

template <typename T, typename U>
auto TIntervalImplementation<T, U>::Interval_IntersectImplementation(const MonoObject* A, const MonoObject* B,
                                                                     MonoObject** OutValue)
{
	const auto IntervalA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto IntervalB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutInterval = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (IntervalA != nullptr && IntervalB != nullptr && OutInterval != nullptr)
	{
		*OutInterval = Intersect(*IntervalA, *IntervalB);
	}
}
