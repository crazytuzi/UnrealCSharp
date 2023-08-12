#pragma once

#include "Environment/FCSharpEnvironment.h"

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_EqualityImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B)
{
	const auto RangeBoundA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeBoundB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	if (RangeBoundA != nullptr && RangeBoundB != nullptr)
	{
		return RangeBoundA->operator==(*RangeBoundB);
	}

	return false;
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_InequalityImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto RangeBoundA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeBoundB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	if (RangeBoundA != nullptr && RangeBoundB != nullptr)
	{
		return RangeBoundA->operator!=(*RangeBoundB);
	}

	return false;
}

template <typename T, typename U>
U TRangeBoundImplementation<T, U>::RangeBound_GetValueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	if (RangeBound != nullptr)
	{
		return RangeBound->GetValue();
	}

	return U();
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_SetValueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const U NewValue)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	if (RangeBound != nullptr)
	{
		return RangeBound->SetValue(NewValue);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_IsClosedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	if (RangeBound != nullptr)
	{
		return RangeBound->IsClosed();
	}

	return false;
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_IsExclusiveImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	if (RangeBound != nullptr)
	{
		return RangeBound->IsExclusive();
	}

	return false;
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_IsInclusiveImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	if (RangeBound != nullptr)
	{
		return RangeBound->IsInclusive();
	}

	return false;
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_IsOpenImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	if (RangeBound != nullptr)
	{
		return RangeBound->IsOpen();
	}

	return false;
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_ExclusiveImplementation(const U Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRangeBound != nullptr)
	{
		*OutRangeBound = T::Exclusive(Value);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_InclusiveImplementation(const U Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRangeBound != nullptr)
	{
		*OutRangeBound = T::Inclusive(Value);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_OpenImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRangeBound != nullptr)
	{
		*OutRangeBound = T::Open();
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_FlipInclusionImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto RangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, T>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeBound != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = T::FlipInclusion(*RangeBound);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_MaxLowerImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B,
                                                                        MonoObject** OutValue)
{
	const auto RangeBoundA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeBoundB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeBoundA != nullptr && RangeBoundB != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = T::MaxLower(*RangeBoundA, *RangeBoundB);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_MaxUpperImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B,
                                                                        MonoObject** OutValue)
{
	const auto RangeBoundA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeBoundB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeBoundA != nullptr && RangeBoundB != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = T::MaxUpper(*RangeBoundA, *RangeBoundB);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_MinLowerImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B,
                                                                        MonoObject** OutValue)
{
	const auto RangeBoundA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeBoundB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeBoundA != nullptr && RangeBoundB != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = T::MinLower(*RangeBoundA, *RangeBoundB);
	}
}

template <typename T, typename U>
auto TRangeBoundImplementation<T, U>::RangeBound_MinUpperImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B,
                                                                        MonoObject** OutValue)
{
	const auto RangeBoundA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeBoundB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeBoundA != nullptr && RangeBoundB != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = T::MinUpper(*RangeBoundA, *RangeBoundB);
	}
}
