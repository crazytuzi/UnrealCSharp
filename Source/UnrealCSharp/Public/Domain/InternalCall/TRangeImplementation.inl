#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Binding/ScriptStruct/TScriptStruct.inl"

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto RangeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	if (RangeA != nullptr && RangeB != nullptr)
	{
		return RangeA->operator==(*RangeB);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto RangeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(A);

	const auto RangeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(B);

	if (RangeA != nullptr && RangeB != nullptr)
	{
		return RangeA->operator!=(*RangeB);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AdjoinsImplementation(const MonoObject* InMonoObject, const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Adjoins(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ConjoinsImplementation(const MonoObject* InMonoObject, const MonoObject* X,
                                                                 const MonoObject* Y)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto RangeX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(X);

	const auto RangeY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Y);

	if (Range != nullptr && RangeX != nullptr && RangeY != nullptr)
	{
		return Range->Conjoins(*RangeX, *RangeY);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ContainsElementImplementation(const MonoObject* InMonoObject, const V Element)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->Contains(Element);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ContainsImplementation(const MonoObject* InMonoObject,
                                                                 const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Contains(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ContiguousImplementation(const MonoObject* InMonoObject,
                                                                   const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto RangeOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(Other);

	if (Range != nullptr && RangeOther != nullptr)
	{
		return Range->Contiguous(*RangeOther);
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetLowerBoundImplementation(const MonoObject* InMonoObject,
                                                                      MonoObject** OutValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<U, U>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, U>(NewMonoObject);

	if (Range != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = Range->GetLowerBound();
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetLowerBoundImplementation(const MonoObject* InMonoObject,
                                                                      const MonoObject* NewLowerBound)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto RangeBoundNewLowerBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, U>(
		NewLowerBound);

	if (Range != nullptr && RangeBoundNewLowerBound != nullptr)
	{
		return Range->SetLowerBound(*RangeBoundNewLowerBound);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetLowerBoundValueImplementation(
	const MonoObject* InMonoObject, const V NewLowerBoundValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->SetLowerBoundValue(NewLowerBoundValue);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetLowerBoundValueImplementation(const MonoObject* InMonoObject)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->GetLowerBoundValue();
	}

	return V();
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetUpperBoundImplementation(const MonoObject* InMonoObject,
                                                                      MonoObject** OutValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<U, U>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRangeBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, U>(NewMonoObject);

	if (Range != nullptr && OutRangeBound != nullptr)
	{
		*OutRangeBound = Range->GetUpperBound();
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetUpperBoundImplementation(const MonoObject* InMonoObject,
                                                                      const MonoObject* NewUpperBound)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	const auto RangeBoundNewUpperBound = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, U>(
		NewUpperBound);

	if (Range != nullptr && RangeBoundNewUpperBound != nullptr)
	{
		return Range->SetUpperBound(*RangeBoundNewUpperBound);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_SetUpperBoundValueImplementation(
	const MonoObject* InMonoObject, const V NewUpperBoundValue)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		Range->SetUpperBoundValue(NewUpperBoundValue);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GetUpperBoundValueImplementation(const MonoObject* InMonoObject)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->GetUpperBoundValue();
	}

	return V();
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_HasLowerBoundImplementation(const MonoObject* InMonoObject)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->HasLowerBound();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_HasUpperBoundImplementation(const MonoObject* InMonoObject)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->HasUpperBound();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_IsDegenerateImplementation(const MonoObject* InMonoObject)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->IsDegenerate();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_IsEmptyImplementation(const MonoObject* InMonoObject)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

	if (Range != nullptr)
	{
		return Range->IsEmpty();
	}

	return false;
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_OverlapsImplementation(const MonoObject* InMonoObject,
                                                                 const MonoObject* Other)
{
	const auto Range = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(InMonoObject);

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

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeX != nullptr && RangeY != nullptr && OutRange != nullptr)
	{
		*OutRange = T::Hull(*RangeX, *RangeY);
	}
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

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (RangeX != nullptr && RangeY != nullptr && OutRange != nullptr)
	{
		*OutRange = T::Intersection(*RangeX, *RangeY);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AllImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::All();
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AtLeastImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::AtLeast(Value);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_AtMostImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::AtMost(Value);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_EmptyImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::Empty();
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_ExclusiveImplementation(const V Min, const V Max, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::Exclusive(Min, Max);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_GreaterThanImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::GreaterThan(Value);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_InclusiveImplementation(const V Min, const V Max, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::Inclusive(Min, Max);
	}
}

template <typename T, typename U, typename V>
auto TRangeImplementation<T, U, V>::Range_LessThanImplementation(const V Value, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<T, T>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRange = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, T>(NewMonoObject);

	if (OutRange != nullptr)
	{
		*OutRange = T::LessThan(Value);
	}
}
