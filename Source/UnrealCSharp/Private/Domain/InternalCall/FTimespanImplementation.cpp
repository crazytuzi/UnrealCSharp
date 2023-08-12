#include "Domain/InternalCall/FTimespanImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterTimespan
{
	FRegisterTimespan()
	{
		TReflectionClassBuilder<FTimespan>(NAMESPACE_LIBRARY)
			.Function("Add", FTimespanImplementation::Timespan_AddImplementation)
			.Function("Negated", FTimespanImplementation::Timespan_NegatedImplementation)
			.Function("Subtract", FTimespanImplementation::Timespan_SubtractImplementation)
			.Function("Multiply", FTimespanImplementation::Timespan_MultiplyImplementation)
			.Function("Divide", FTimespanImplementation::Timespan_DivideImplementation)
			.Function("Remainder", FTimespanImplementation::Timespan_RemainderImplementation)
			.Function("Equality", FTimespanImplementation::Timespan_EqualityImplementation)
			.Function("Inequality", FTimespanImplementation::Timespan_InequalityImplementation)
			.Function("GreaterThan", FTimespanImplementation::Timespan_GreaterThanImplementation)
			.Function("GreaterThanOrEqual", FTimespanImplementation::Timespan_GreaterThanOrEqualImplementation)
			.Function("LessThan", FTimespanImplementation::Timespan_LessThanImplementation)
			.Function("LessThanOrEqual", FTimespanImplementation::Timespan_LessThanOrEqualImplementation)
			.Function("GetDays", FTimespanImplementation::Timespan_GetDaysImplementation)
			.Function("GetDuration", FTimespanImplementation::Timespan_GetDurationImplementation)
			.Function("GetFractionMicro", FTimespanImplementation::Timespan_GetFractionMicroImplementation)
			.Function("GetFractionMilli", FTimespanImplementation::Timespan_GetFractionMilliImplementation)
			.Function("GetFractionNano", FTimespanImplementation::Timespan_GetFractionNanoImplementation)
			.Function("GetFractionTicks", FTimespanImplementation::Timespan_GetFractionTicksImplementation)
			.Function("GetHours", FTimespanImplementation::Timespan_GetHoursImplementation)
			.Function("GetMinutes", FTimespanImplementation::Timespan_GetMinutesImplementation)
			.Function("GetSeconds", FTimespanImplementation::Timespan_GetSecondsImplementation)
			.Function("GetTicks", FTimespanImplementation::Timespan_GetTicksImplementation)
			.Function("GetTotalDays", FTimespanImplementation::Timespan_GetTotalDaysImplementation)
			.Function("GetTotalHours", FTimespanImplementation::Timespan_GetTotalHoursImplementation)
			.Function("GetTotalMicroseconds", FTimespanImplementation::Timespan_GetTotalMicrosecondsImplementation)
			.Function("GetTotalMilliseconds", FTimespanImplementation::Timespan_GetTotalMillisecondsImplementation)
			.Function("GetTotalMinutes", FTimespanImplementation::Timespan_GetTotalMinutesImplementation)
			.Function("GetTotalSeconds", FTimespanImplementation::Timespan_GetTotalSecondsImplementation)
			.Function("IsZero", FTimespanImplementation::Timespan_IsZeroImplementation)
			.Function("ToString", FTimespanImplementation::Timespan_ToStringImplementation)
			.Function("FromDays", FTimespanImplementation::Timespan_FromDaysImplementation)
			.Function("FromHours", FTimespanImplementation::Timespan_FromHoursImplementation)
			.Function("FromMicroseconds", FTimespanImplementation::Timespan_FromMicrosecondsImplementation)
			.Function("FromMilliseconds", FTimespanImplementation::Timespan_FromMillisecondsImplementation)
			.Function("FromMinutes", FTimespanImplementation::Timespan_FromMinutesImplementation)
			.Function("FromSeconds", FTimespanImplementation::Timespan_FromSecondsImplementation)
			.Function("MaxValue", FTimespanImplementation::Timespan_MaxValueImplementation)
			.Function("MinValue", FTimespanImplementation::Timespan_MinValueImplementation)
			.Function("Parse", FTimespanImplementation::Timespan_ParseImplementation)
			.Function("Ratio", FTimespanImplementation::Timespan_RatioImplementation)
			.Function("Zero", FTimespanImplementation::Timespan_ZeroImplementation)
			.Register();
	}
};

static FRegisterTimespan RegisterTimespan;

void FTimespanImplementation::Timespan_AddImplementation(const FGarbageCollectionHandle A,
                                                         const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (TimespanA != nullptr && TimespanB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = TimespanA->operator+(*TimespanB);
	}
}

void FTimespanImplementation::Timespan_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->operator-();
	}
}

void FTimespanImplementation::Timespan_SubtractImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (TimespanA != nullptr && TimespanB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = TimespanA->operator-(*TimespanB);
	}
}

void FTimespanImplementation::Timespan_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const double Scalar, MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->operator*(Scalar);
	}
}

void FTimespanImplementation::Timespan_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const double Scalar, MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->operator/(Scalar);
	}
}

void FTimespanImplementation::Timespan_RemainderImplementation(const FGarbageCollectionHandle A,
                                                               const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (TimespanA != nullptr && TimespanB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = TimespanA->operator%(*TimespanB);
	}
}

bool FTimespanImplementation::Timespan_EqualityImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator==(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_InequalityImplementation(const FGarbageCollectionHandle A,
                                                                const FGarbageCollectionHandle B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator!=(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_GreaterThanImplementation(const FGarbageCollectionHandle A,
                                                                 const FGarbageCollectionHandle B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator>(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_GreaterThanOrEqualImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator>=(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_LessThanImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator<(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
                                                                     const FGarbageCollectionHandle B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator<=(*TimespanB);
	}

	return false;
}

int32 FTimespanImplementation::Timespan_GetDaysImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetDays();
	}

	return 0;
}

void FTimespanImplementation::Timespan_GetDurationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->GetDuration();
	}
}

int32 FTimespanImplementation::Timespan_GetFractionMicroImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionMicro();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetFractionMilliImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionMilli();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetFractionNanoImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionNano();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetFractionTicksImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionTicks();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetHoursImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetHours();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetMinutesImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetMinutes();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetSecondsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetSeconds();
	}

	return 0;
}

int64 FTimespanImplementation::Timespan_GetTicksImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTicks();
	}

	return 0;
}

double FTimespanImplementation::Timespan_GetTotalDaysImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalDays();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalHoursImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalHours();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalMicrosecondsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalMicroseconds();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalMillisecondsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalMilliseconds();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalMinutesImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalMinutes();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalSecondsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalSeconds();
	}

	return 0.0;
}

bool FTimespanImplementation::Timespan_IsZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		return Timespan->IsZero();
	}

	return false;
}

void FTimespanImplementation::Timespan_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(
		InGarbageCollectionHandle);

	if (Timespan != nullptr)
	{
		const auto ResultString = Timespan->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FTimespanImplementation::Timespan_FromDaysImplementation(const double Days, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::FromDays(Days);
	}
}

void FTimespanImplementation::Timespan_FromHoursImplementation(const double Hours, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::FromHours(Hours);
	}
}

void FTimespanImplementation::Timespan_FromMicrosecondsImplementation(const double Microseconds, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::FromMicroseconds(Microseconds);
	}
}

void FTimespanImplementation::Timespan_FromMillisecondsImplementation(const double Milliseconds, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::FromMilliseconds(Milliseconds);
	}
}

void FTimespanImplementation::Timespan_FromMinutesImplementation(const double Minutes, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::FromMinutes(Minutes);
	}
}

void FTimespanImplementation::Timespan_FromSecondsImplementation(const double Seconds, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::FromSeconds(Seconds);
	}
}

void FTimespanImplementation::Timespan_MaxValueImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::MaxValue();
	}
}

void FTimespanImplementation::Timespan_MinValueImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::MinValue();
	}
}

bool FTimespanImplementation::Timespan_ParseImplementation(MonoObject* TimespanString, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		return FTimespan::Parse(
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(TimespanString, nullptr))), *OutTimespan);
	}

	return false;
}

double FTimespanImplementation::Timespan_RatioImplementation(const MonoObject* Dividend, const MonoObject* Divisor)
{
	const auto TimespanDividend = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(Dividend);

	const auto TimespanDivisor = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(Divisor);

	if (TimespanDividend != nullptr && TimespanDivisor != nullptr)
	{
		return FTimespan::Ratio(*TimespanDividend, *TimespanDivisor);
	}

	return 0.0;
}

void FTimespanImplementation::Timespan_ZeroImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::Zero();
	}
}
