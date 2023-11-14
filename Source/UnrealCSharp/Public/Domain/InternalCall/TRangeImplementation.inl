#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Binding/ScriptStruct/TScriptStruct.inl"

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AdjoinsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Adjoins(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ConjoinsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* X,
	const MonoObject* Y)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(X);

	const auto RangeY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Y);

	if (Range != nullptr && RangeX != nullptr && RangeY != nullptr)
	{
		return Range->Conjoins(*RangeX, *RangeY);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ContainsElementImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const V Element)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->Contains(Element);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ContainsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Contains(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ContiguousImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Contiguous(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetLowerBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<U, U>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = new U(Range->GetLowerBound());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<U>::Get(), OutRangeBound,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetLowerBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewLowerBound)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeBoundNewLowerBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, U>(
		NewLowerBound);

	if (Range != nullptr && RangeBoundNewLowerBound != nullptr)
	{
		return Range->SetLowerBound(*RangeBoundNewLowerBound);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetLowerBoundValueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const V NewLowerBoundValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->SetLowerBoundValue(NewLowerBoundValue);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetLowerBoundValueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->GetLowerBoundValue();
	}

	return V();
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetUpperBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<U, U>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = new U(Range->GetUpperBound());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<U>::Get(), OutRangeBound,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetUpperBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewUpperBound)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeBoundNewUpperBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, U>(
		NewUpperBound);

	if (Range != nullptr && RangeBoundNewUpperBound != nullptr)
	{
		return Range->SetUpperBound(*RangeBoundNewUpperBound);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetUpperBoundValueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const V NewUpperBoundValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		Range->SetUpperBoundValue(NewUpperBoundValue);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetUpperBoundValueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->GetUpperBoundValue();
	}

	return V();
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_HasLowerBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->HasLowerBound();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_HasUpperBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->HasUpperBound();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_IsDegenerateImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->IsDegenerate();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_IsEmptyImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	if (Range != nullptr)
	{
		return Range->IsEmpty();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_OverlapsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InGarbageCollectionHandle);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Overlaps(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_HullImplementation(const MonoObject* X, const MonoObject* Y,
                                                             MonoObject** OutValue)
{
	const auto RangeX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(X);

	const auto RangeY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Y);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::Hull(*RangeX, *RangeY));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_IntersectionImplementation(const MonoObject* X, const MonoObject* Y,
                                                                     MonoObject** OutValue)
{
	const auto RangeX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(X);

	const auto RangeY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Y);

	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::Intersection(*RangeX, *RangeY));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AllImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::All());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AtLeastImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::AtLeast(Value));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AtMostImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::AtMost(Value));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_EmptyImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::Empty());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ExclusiveImplementation(const V Min, const V Max, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::Exclusive(Min, Max));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GreaterThanImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::GreaterThan(Value));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_InclusiveImplementation(const V Min, const V Max, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::Inclusive(Min, Max));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_LessThanImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = new T(T::LessThan(Value));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), OutRange,
	                                                        NewMonoObject);
}
