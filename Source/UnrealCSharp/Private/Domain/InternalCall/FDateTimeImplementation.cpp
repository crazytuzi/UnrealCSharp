﻿#include "Domain/InternalCall/FDateTimeImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterDateTime
{
	FRegisterDateTime()
	{
		TReflectionClassBuilder<FDateTime>(NAMESPACE_LIBRARY)
			.Function("AddTimespan", FDateTimeImplementation::DateTime_AddTimespanImplementation)
			.Function("AddDateTime", FDateTimeImplementation::DateTime_AddDateTimeImplementation)
			.Function("SubtractDateTime", FDateTimeImplementation::DateTime_SubtractDateTimeImplementation)
			.Function("SubtractTimespan", FDateTimeImplementation::DateTime_SubtractTimespanImplementation)
			.Function("Equality", FDateTimeImplementation::DateTime_EqualityImplementation)
			.Function("Inequality", FDateTimeImplementation::DateTime_InequalityImplementation)
			.Function("GreaterThan", FDateTimeImplementation::DateTime_GreaterThanImplementation)
			.Function("GreaterThanOrEqual", FDateTimeImplementation::DateTime_GreaterThanOrEqualImplementation)
			.Function("LessThan", FDateTimeImplementation::DateTime_LessThanImplementation)
			.Function("LessThanOrEqual", FDateTimeImplementation::DateTime_LessThanOrEqualImplementation)
			.Function("GetDatePart", FDateTimeImplementation::DateTime_GetDatePartImplementation)
			.Function("GetDateComponents", FDateTimeImplementation::DateTime_GetDateComponentsImplementation)
			.Function("GetDay", FDateTimeImplementation::DateTime_GetDayImplementation)
			.Function("GetDayOfYear", FDateTimeImplementation::DateTime_GetDayOfYearImplementation)
			.Function("GetHour", FDateTimeImplementation::DateTime_GetHourImplementation)
			.Function("GetHour12", FDateTimeImplementation::DateTime_GetHour12Implementation)
			.Function("GetJulianDay", FDateTimeImplementation::DateTime_GetJulianDayImplementation)
			.Function("GetModifiedJulianDay", FDateTimeImplementation::DateTime_GetModifiedJulianDayImplementation)
			.Function("GetMillisecond", FDateTimeImplementation::DateTime_GetMillisecondImplementation)
			.Function("GetMinute", FDateTimeImplementation::DateTime_GetMinuteImplementation)
			.Function("GetMonth", FDateTimeImplementation::DateTime_GetMonthImplementation)
			.Function("GetSecond", FDateTimeImplementation::DateTime_GetSecondImplementation)
			.Function("GetTicks", FDateTimeImplementation::DateTime_GetTicksImplementation)
			.Function("GetTimeOfDay", FDateTimeImplementation::DateTime_GetTimeOfDayImplementation)
			.Function("GetYear", FDateTimeImplementation::DateTime_GetYearImplementation)
			.Function("IsAfternoon", FDateTimeImplementation::DateTime_IsAfternoonImplementation)
			.Function("IsMorning", FDateTimeImplementation::DateTime_IsMorningImplementation)
			.Function("ToHttpDate", FDateTimeImplementation::DateTime_ToHttpDateImplementation)
			.Function("ToIso8601", FDateTimeImplementation::DateTime_ToIso8601Implementation)
			.Function("ToString", FDateTimeImplementation::DateTime_ToStringImplementation)
			.Function("ToUnixTimestamp", FDateTimeImplementation::DateTime_ToUnixTimestampImplementation)
			.Function("DaysInMonth", FDateTimeImplementation::DateTime_DaysInMonthImplementation)
			.Function("DaysInYear", FDateTimeImplementation::DateTime_DaysInYearImplementation)
			.Function("FromJulianDay", FDateTimeImplementation::DateTime_FromJulianDayImplementation)
			.Function("FromUnixTimestamp", FDateTimeImplementation::DateTime_FromUnixTimestampImplementation)
			.Function("IsLeapYear", FDateTimeImplementation::DateTime_IsLeapYearImplementation)
			.Function("MaxValue", FDateTimeImplementation::DateTime_MaxValueImplementation)
			.Function("MinValue", FDateTimeImplementation::DateTime_MinValueImplementation)
			.Function("Now", FDateTimeImplementation::DateTime_NowImplementation)
			.Function("Parse", FDateTimeImplementation::DateTime_ParseImplementation)
			.Function("ParseHttpDate", FDateTimeImplementation::DateTime_ParseHttpDateImplementation)
			.Function("Today", FDateTimeImplementation::DateTime_TodayImplementation)
			.Function("UtcNow", FDateTimeImplementation::DateTime_UtcNowImplementation)
			.Function("Validate", FDateTimeImplementation::DateTime_ValidateImplementation)
			.Register();
	}
};

static FRegisterDateTime RegisterDateTime;

void FDateTimeImplementation::DateTime_AddTimespanImplementation(const MonoObject* A, const MonoObject* B,
                                                                 MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (DateTime != nullptr && Timespan != nullptr && OutDateTime != nullptr)
	{
		*OutDateTime = DateTime->operator+(*Timespan);
	}
}

void FDateTimeImplementation::DateTime_AddDateTimeImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		DateTimeA->operator+(*DateTimeB);
	}
}

void FDateTimeImplementation::DateTime_SubtractDateTimeImplementation(const MonoObject* A, const MonoObject* B,
                                                                      MonoObject** OutValue)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();
	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (DateTimeA != nullptr && DateTimeB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = DateTimeA->operator-(*DateTimeB);
	}
}

void FDateTimeImplementation::DateTime_SubtractTimespanImplementation(const MonoObject* A, const MonoObject* B,
                                                                      MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (DateTime != nullptr && Timespan != nullptr && OutDateTime != nullptr)
	{
		*OutDateTime = DateTime->operator-(*Timespan);
	}
}

bool FDateTimeImplementation::DateTime_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		return DateTimeA->operator==(*DateTimeB);
	}

	return false;
}

bool FDateTimeImplementation::DateTime_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		return DateTimeA->operator!=(*DateTimeB);
	}

	return false;
}

bool FDateTimeImplementation::DateTime_GreaterThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		return DateTimeA->operator>(*DateTimeB);
	}

	return false;
}

bool FDateTimeImplementation::DateTime_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		return DateTimeA->operator>=(*DateTimeB);
	}

	return false;
}

bool FDateTimeImplementation::DateTime_LessThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		return DateTimeA->operator<(*DateTimeB);
	}

	return false;
}

bool FDateTimeImplementation::DateTime_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto DateTimeA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(A);

	const auto DateTimeB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(B);

	if (DateTimeA != nullptr && DateTimeB != nullptr)
	{
		return DateTimeA->operator<=(*DateTimeB);
	}

	return false;
}

void FDateTimeImplementation::DateTime_GetDatePartImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (DateTime != nullptr && OutDateTime != nullptr)
	{
		*OutDateTime = DateTime->GetDate();
	}
}

void FDateTimeImplementation::DateTime_GetDateComponentsImplementation(const MonoObject* InMonoObject, int32& OutYear,
                                                                       int32& OutMonth, int32& OutDay)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		DateTime->GetDate(OutYear, OutMonth, OutDay);
	}
}

int32 FDateTimeImplementation::DateTime_GetDayImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetDay();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_GetDayOfYearImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetDayOfYear();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_GetHourImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetHour();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_GetHour12Implementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetHour12();
	}

	return 0;
}

double FDateTimeImplementation::DateTime_GetJulianDayImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetJulianDay();
	}

	return 0.0;
}

double FDateTimeImplementation::DateTime_GetModifiedJulianDayImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetModifiedJulianDay();
	}

	return 0.0;
}

int32 FDateTimeImplementation::DateTime_GetMillisecondImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetMillisecond();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_GetMinuteImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetMinute();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_GetMonthImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetMonth();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_GetSecondImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetSecond();
	}

	return 0;
}

int64 FDateTimeImplementation::DateTime_GetTicksImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetTicks();
	}

	return 0;
}

void FDateTimeImplementation::DateTime_GetTimeOfDayImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FTimespan, FTimespan>::Get();
	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (DateTime != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = DateTime->GetTimeOfDay();
	}
}

int32 FDateTimeImplementation::DateTime_GetYearImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->GetYear();
	}

	return 0;
}

bool FDateTimeImplementation::DateTime_IsAfternoonImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->IsAfternoon();
	}

	return false;
}

bool FDateTimeImplementation::DateTime_IsMorningImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->IsMorning();
	}

	return false;
}

void FDateTimeImplementation::DateTime_ToHttpDateImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		const auto ResultString = DateTime->ToHttpDate();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FDateTimeImplementation::DateTime_ToIso8601Implementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		const auto ResultString = DateTime->ToIso8601();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FDateTimeImplementation::DateTime_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		const auto ResultString = DateTime->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

int64 FDateTimeImplementation::DateTime_ToUnixTimestampImplementation(const MonoObject* InMonoObject)
{
	const auto DateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(InMonoObject);

	if (DateTime != nullptr)
	{
		return DateTime->ToUnixTimestamp();
	}

	return 0;
}

int32 FDateTimeImplementation::DateTime_DaysInMonthImplementation(const int32 Year, const int32 Month)
{
	return FDateTime::DaysInMonth(Year, Month);
}

int32 FDateTimeImplementation::DateTime_DaysInYearImplementation(const int32 Year)
{
	return FDateTime::DaysInYear(Year);
}

void FDateTimeImplementation::DateTime_FromJulianDayImplementation(const double JulianDay, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::FromJulianDay(JulianDay);
	}
}

void FDateTimeImplementation::DateTime_FromUnixTimestampImplementation(const int64 UnixTime, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::FromUnixTimestamp(UnixTime);
	}
}

bool FDateTimeImplementation::DateTime_IsLeapYearImplementation(const int32 Year)
{
	return FDateTime::IsLeapYear(Year);
}

void FDateTimeImplementation::DateTime_MaxValueImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::MaxValue();
	}
}

void FDateTimeImplementation::DateTime_MinValueImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::MinValue();
	}
}

void FDateTimeImplementation::DateTime_NowImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::Now();
	}
}

bool FDateTimeImplementation::DateTime_ParseImplementation(MonoObject* DateTimeString, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		return FDateTime::Parse(
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(DateTimeString, nullptr))), *OutDateTime);
	}

	return false;
}

bool FDateTimeImplementation::DateTime_ParseHttpDateImplementation(MonoObject* HttpDate, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		return FDateTime::ParseHttpDate(
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(HttpDate, nullptr))), *OutDateTime);
	}

	return false;
}

void FDateTimeImplementation::DateTime_TodayImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::Today();
	}
}

void FDateTimeImplementation::DateTime_UtcNowImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FDateTime, FDateTime>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutDateTime = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FDateTime>(NewMonoObject);

	if (OutDateTime != nullptr)
	{
		*OutDateTime = FDateTime::UtcNow();
	}
}

bool FDateTimeImplementation::DateTime_ValidateImplementation(const int32 Year, const int32 Month, const int32 Day,
                                                              const int32 Hour, const int32 Minute, const int32 Second,
                                                              const int32 Millisecond)
{
	return FDateTime::Validate(Year, Month, Day, Hour, Minute, Second, Millisecond);;
}
