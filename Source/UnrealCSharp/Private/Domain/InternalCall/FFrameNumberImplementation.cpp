﻿#include "Domain/InternalCall/FFrameNumberImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterFrameNumber
{
	FRegisterFrameNumber()
	{
		TReflectionClassBuilder<FFrameNumber>(NAMESPACE_LIBRARY)
			.Function("Increment", FFrameNumberImplementation::FrameNumber_IncrementImplementation)
			.Function("Decrement", FFrameNumberImplementation::FrameNumber_DecrementImplementation)
			.Function("Equality", FFrameNumberImplementation::FrameNumber_EqualityImplementation)
			.Function("Inequality", FFrameNumberImplementation::FrameNumber_InequalityImplementation)
			.Function("LessThan", FFrameNumberImplementation::FrameNumber_LessThanImplementation)
			.Function("GreaterThan", FFrameNumberImplementation::FrameNumber_GreaterThanImplementation)
			.Function("LessThanOrEqual", FFrameNumberImplementation::FrameNumber_LessThanOrEqualImplementation)
			.Function("GreaterThanOrEqual", FFrameNumberImplementation::FrameNumber_GreaterThanOrEqualImplementation)
			.Function("Add", FFrameNumberImplementation::FrameNumber_AddImplementation)
			.Function("Subtract", FFrameNumberImplementation::FrameNumber_SubtractImplementation)
			.Function("Remainder", FFrameNumberImplementation::FrameNumber_RemainderImplementation)
			.Function("Negated", FFrameNumberImplementation::FrameNumber_NegatedImplementation)
			.Function("Multiply", FFrameNumberImplementation::FrameNumber_MultiplyImplementation)
			.Function("Divide", FFrameNumberImplementation::FrameNumber_DivideImplementation)
			.Register();
	}
};

static FRegisterFrameNumber RegisterFrameNumber;

void FFrameNumberImplementation::FrameNumber_IncrementImplementation(const MonoObject* InMonoObject)
{
	const auto FrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameNumber>(InMonoObject);

	if (FrameNumber != nullptr)
	{
		FrameNumber->operator++();
	}
}

void FFrameNumberImplementation::FrameNumber_DecrementImplementation(const MonoObject* InMonoObject)
{
	const auto FrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameNumber>(InMonoObject);

	if (FrameNumber != nullptr)
	{
		FrameNumber->operator--();
	}
}

bool FFrameNumberImplementation::FrameNumber_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr)
	{
		return operator==(*FrameNumberA, *FrameNumberB);
	}

	return false;
}

bool FFrameNumberImplementation::FrameNumber_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr)
	{
		return operator!=(*FrameNumberA, *FrameNumberB);
	}

	return false;
}

bool FFrameNumberImplementation::FrameNumber_LessThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr)
	{
		return operator<(*FrameNumberA, *FrameNumberB);
	}

	return false;
}

bool FFrameNumberImplementation::FrameNumber_GreaterThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr)
	{
		return operator>(*FrameNumberA, *FrameNumberB);
	}

	return false;
}

bool FFrameNumberImplementation::FrameNumber_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr)
	{
		return operator<=(*FrameNumberA, *FrameNumberB);
	}

	return false;
}

bool FFrameNumberImplementation::FrameNumber_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr)
	{
		return operator>=(*FrameNumberA, *FrameNumberB);
	}

	return false;
}

void FFrameNumberImplementation::FrameNumber_AddImplementation(const MonoObject* A, const MonoObject* B,
                                                               MonoObject** OutValue)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = operator+(*FrameNumberA, *FrameNumberB);
	}
}

void FFrameNumberImplementation::FrameNumber_SubtractImplementation(const MonoObject* A, const MonoObject* B,
                                                                    MonoObject** OutValue)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = operator-(*FrameNumberA, *FrameNumberB);
	}
}

void FFrameNumberImplementation::FrameNumber_RemainderImplementation(const MonoObject* A, const MonoObject* B,
                                                                     MonoObject** OutValue)
{
	const auto FrameNumberA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(A);

	const auto FrameNumberB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(B);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameNumberA != nullptr && FrameNumberB != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = operator%(*FrameNumberA, *FrameNumberB);
	}
}

void FFrameNumberImplementation::FrameNumber_NegatedImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto FrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameNumber>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameNumber != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = operator-(*FrameNumber);
	}
}

void FFrameNumberImplementation::FrameNumber_MultiplyImplementation(const MonoObject* InMonoObject, const float Scalar,
                                                                    MonoObject** OutValue)
{
	const auto FrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameNumber>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameNumber != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = operator*(*FrameNumber, Scalar);
	}
}

void FFrameNumberImplementation::FrameNumber_DivideImplementation(const MonoObject* InMonoObject, const float Scalar,
                                                                  MonoObject** OutValue)
{
	const auto FrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameNumber>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameNumber != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = operator/(*FrameNumber, Scalar);
	}
}
