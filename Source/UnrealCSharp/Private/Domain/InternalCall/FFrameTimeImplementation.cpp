#include "Domain/InternalCall/FFrameTimeImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterFrameTime
{
	FRegisterFrameTime()
	{
		TReflectionClassBuilder<FFrameTime>(NAMESPACE_LIBRARY)
			.Function("GetFrame", FFrameTimeImplementation::FrameTime_GetFrameImplementation)
			.Function("GetSubFrame", FFrameTimeImplementation::FrameTime_GetSubFrameImplementation)
			.Function("FloorToFrame", FFrameTimeImplementation::FrameTime_FloorToFrameImplementation)
			.Function("CeilToFrame", FFrameTimeImplementation::FrameTime_CeilToFrameImplementation)
			.Function("RoundToFrame", FFrameTimeImplementation::FrameTime_RoundToFrameImplementation)
			.Function("AsDecimal", FFrameTimeImplementation::FrameTime_AsDecimalImplementation)
			.Function("FromDecimal", FFrameTimeImplementation::FrameTime_FromDecimalImplementation)
			.Function("Equality", FFrameTimeImplementation::FrameTime_EqualityImplementation)
			.Function("Inequality", FFrameTimeImplementation::FrameTime_InequalityImplementation)
			.Function("GreaterThan", FFrameTimeImplementation::FrameTime_GreaterThanImplementation)
			.Function("GreaterThanOrEqual", FFrameTimeImplementation::FrameTime_GreaterThanOrEqualImplementation)
			.Function("LessThan", FFrameTimeImplementation::FrameTime_LessThanImplementation)
			.Function("LessThanOrEqual", FFrameTimeImplementation::FrameTime_LessThanOrEqualImplementation)
			.Function("Add", FFrameTimeImplementation::FrameTime_AddImplementation)
			.Function("Subtract", FFrameTimeImplementation::FrameTime_SubtractImplementation)
			.Function("Remainder", FFrameTimeImplementation::FrameTime_RemainderImplementation)
			.Function("Negated", FFrameTimeImplementation::FrameTime_NegatedImplementation)
			.Function("Multiply", FFrameTimeImplementation::FrameTime_MultiplyImplementation)
			.Function("Divide", FFrameTimeImplementation::FrameTime_DivideImplementation)
			.Register();
	}
};

static FRegisterFrameTime RegisterFrameTime;

void FFrameTimeImplementation::FrameTime_GetFrameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameTime != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = FrameTime->GetFrame();
	}
}

float FFrameTimeImplementation::FrameTime_GetSubFrameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	if (FrameTime != nullptr)
	{
		return FrameTime->GetSubFrame();
	}

	return 0.f;
}

void FFrameTimeImplementation::FrameTime_FloorToFrameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameTime != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = FrameTime->FloorToFrame();
	}
}

void FFrameTimeImplementation::FrameTime_CeilToFrameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameTime != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = FrameTime->CeilToFrame();
	}
}

void FFrameTimeImplementation::FrameTime_RoundToFrameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameNumber, FFrameNumber>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameNumber = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameNumber>(
		NewMonoObject);

	if (FrameTime != nullptr && OutFrameNumber != nullptr)
	{
		*OutFrameNumber = FrameTime->RoundToFrame();
	}
}

double FFrameTimeImplementation::FrameTime_AsDecimalImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	if (FrameTime != nullptr)
	{
		return FrameTime->AsDecimal();
	}

	return 0.0;
}

void FFrameTimeImplementation::FrameTime_FromDecimalImplementation(const double InDecimalFrame, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (OutFrameTime != nullptr)
	{
		*OutFrameTime = FFrameTime::FromDecimal(InDecimalFrame);
	}
}

bool FFrameTimeImplementation::FrameTime_EqualityImplementation(const FGarbageCollectionHandle A,
                                                                const FGarbageCollectionHandle B)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr)
	{
		return operator==(*FrameTimeA, *FrameTimeB);
	}

	return false;
}

bool FFrameTimeImplementation::FrameTime_InequalityImplementation(const FGarbageCollectionHandle A,
                                                                  const FGarbageCollectionHandle B)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr)
	{
		return operator!=(*FrameTimeA, *FrameTimeB);
	}

	return false;
}

bool FFrameTimeImplementation::FrameTime_GreaterThanImplementation(const FGarbageCollectionHandle A,
                                                                   const FGarbageCollectionHandle B)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr)
	{
		return operator>(*FrameTimeA, *FrameTimeB);
	}

	return false;
}

bool FFrameTimeImplementation::FrameTime_GreaterThanOrEqualImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr)
	{
		return operator>=(*FrameTimeA, *FrameTimeB);
	}

	return false;
}

bool FFrameTimeImplementation::FrameTime_LessThanImplementation(const FGarbageCollectionHandle A,
                                                                const FGarbageCollectionHandle B)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr)
	{
		return operator<(*FrameTimeA, *FrameTimeB);
	}

	return false;
}

bool FFrameTimeImplementation::FrameTime_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
                                                                       const FGarbageCollectionHandle B)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr)
	{
		return operator<=(*FrameTimeA, *FrameTimeB);
	}

	return false;
}

void FFrameTimeImplementation::FrameTime_AddImplementation(const FGarbageCollectionHandle A,
                                                           const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr && OutFrameTime != nullptr)
	{
		*OutFrameTime = operator+(*FrameTimeA, *FrameTimeB);
	}
}

void FFrameTimeImplementation::FrameTime_SubtractImplementation(const FGarbageCollectionHandle A,
                                                                const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr && OutFrameTime != nullptr)
	{
		*OutFrameTime = operator-(*FrameTimeA, *FrameTimeB);
	}
}

void FFrameTimeImplementation::FrameTime_RemainderImplementation(const FGarbageCollectionHandle A,
                                                                 const FGarbageCollectionHandle B,
                                                                 MonoObject** OutValue)
{
	const auto FrameTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(A);

	const auto FrameTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(B);

	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (FrameTimeA != nullptr && FrameTimeB != nullptr && OutFrameTime != nullptr)
	{
		*OutFrameTime = operator%(*FrameTimeA, *FrameTimeB);
	}
}

void FFrameTimeImplementation::FrameTime_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (FrameTime != nullptr && OutFrameTime != nullptr)
	{
		*OutFrameTime = operator-(*FrameTime);
	}
}

void FFrameTimeImplementation::FrameTime_MultiplyImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float Scalar, MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (FrameTime != nullptr && OutFrameTime != nullptr)
	{
		*OutFrameTime = operator*(*FrameTime, Scalar);
	}
}

void FFrameTimeImplementation::FrameTime_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const float Scalar, MonoObject** OutValue)
{
	const auto FrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FFrameTime>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FFrameTime, FFrameTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutFrameTime = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FFrameTime>(NewMonoObject);

	if (FrameTime != nullptr && OutFrameTime != nullptr)
	{
		*OutFrameTime = operator/(*FrameTime, Scalar);
	}
}
