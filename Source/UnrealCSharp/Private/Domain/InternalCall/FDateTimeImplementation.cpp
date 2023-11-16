#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Macro/NamespaceMacro.h"

BINDING_ENGINE_ENUM(EDayOfWeek)

BINDING_ENGINE_ENUM(EMonthOfYear)

struct FRegisterDayOfWeek
{
	FRegisterDayOfWeek()
	{
		TBindingEnumBuilder<EDayOfWeek>()
			.Enumerator("Monday", EDayOfWeek::Monday)
			.Enumerator("Tuesday", EDayOfWeek::Tuesday)
			.Enumerator("Wednesday", EDayOfWeek::Wednesday)
			.Enumerator("Thursday", EDayOfWeek::Thursday)
			.Enumerator("Friday", EDayOfWeek::Friday)
			.Enumerator("Saturday", EDayOfWeek::Saturday)
			.Enumerator("Sunday", EDayOfWeek::Sunday)
			.Register();
	}
};

static FRegisterDayOfWeek RegisterDayOfWeek;

struct FRegisterMonthOfYear
{
	FRegisterMonthOfYear()
	{
		TBindingEnumBuilder<EMonthOfYear>()
			.Enumerator("January", EMonthOfYear::January)
			.Enumerator("February", EMonthOfYear::February)
			.Enumerator("March", EMonthOfYear::March)
			.Enumerator("April", EMonthOfYear::April)
			.Enumerator("May", EMonthOfYear::May)
			.Enumerator("June", EMonthOfYear::June)
			.Enumerator("July", EMonthOfYear::July)
			.Enumerator("August", EMonthOfYear::August)
			.Enumerator("September", EMonthOfYear::September)
			.Enumerator("October", EMonthOfYear::October)
			.Enumerator("November", EMonthOfYear::November)
			.Enumerator("December", EMonthOfYear::December)
			.Register();
	}
};

static FRegisterMonthOfYear RegisterMonthOfYear;

struct FRegisterDateTime
{
	static FDateTime PlusImplementation(const FDateTime& In, const FTimespan& Other)
	{
		return In + Other;
	}

	static FDateTime& PlusImplementation(FDateTime& In, const FDateTime& Other)
	{
		return In + Other;
	}

	static FTimespan MinusImplementation(const FDateTime& In, const FDateTime& Other)
	{
		return In - Other;
	}

	static FDateTime MinusImplementation(const FDateTime& In, const FTimespan& Other)
	{
		return In - Other;
	}

	FRegisterDateTime()
	{
		TReflectionClassBuilder<FDateTime>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FDateTime, int64),
			             {"InTicks"})
			.Constructor(BINDING_CONSTRUCTOR(FDateTime, int32, int32, int32, int32, int32, int32, int32),
			             {"Year", "Month", "Day", "Hour", "Minute", "Second", "Millisecond"})
			.Greater()
			.GreaterEqual()
			.Less()
			.LessEqual()
			.Function("operator +", FUNCTION_PLUS,
			          BINDING_OVERLOAD(FDateTime(*)(const FDateTime&, const FTimespan&), &PlusImplementation))
			.Function("operator +", FUNCTION_PLUS,
			          BINDING_OVERLOAD(FDateTime&(*)(FDateTime&, const FDateTime&), &PlusImplementation))
			.Function("operator -", FUNCTION_MINUS,
			          BINDING_OVERLOAD(FTimespan(*)(const FDateTime&, const FDateTime&), &MinusImplementation))
			.Function("operator -", FUNCTION_MINUS,
			          BINDING_OVERLOAD(FDateTime(*)(const FDateTime&, const FTimespan&), &MinusImplementation))
			.Function("GetDate", BINDING_OVERLOAD(FDateTime(FDateTime::*)()const, &FDateTime::GetDate))
			.Function("GetDate", BINDING_OVERLOAD(void(FDateTime::*)(int32&, int32&, int32&)const, &FDateTime::GetDate),
			          {"OutYear", "OutMonth", "OutDay"})
			.Function("GetDay", BINDING_FUNCTION(&FDateTime::GetDay))
			.Function("GetDayOfWeek", BINDING_FUNCTION(&FDateTime::GetDayOfWeek))
			.Function("GetDayOfYear", BINDING_FUNCTION(&FDateTime::GetDayOfYear))
			.Function("GetHour", BINDING_FUNCTION(&FDateTime::GetHour))
			.Function("GetHour12", BINDING_FUNCTION(&FDateTime::GetHour12))
			.Function("GetJulianDay", BINDING_FUNCTION(&FDateTime::GetJulianDay))
			.Function("GetModifiedJulianDay", BINDING_FUNCTION(&FDateTime::GetModifiedJulianDay))
			.Function("GetMillisecond", BINDING_FUNCTION(&FDateTime::GetMillisecond))
			.Function("GetMinute", BINDING_FUNCTION(&FDateTime::GetMinute))
			.Function("GetMonth", BINDING_FUNCTION(&FDateTime::GetMonth))
			.Function("GetMonthOfYear", BINDING_FUNCTION(&FDateTime::GetMonthOfYear))
			.Function("GetSecond", BINDING_FUNCTION(&FDateTime::GetSecond))
			.Function("GetTicks", BINDING_FUNCTION(&FDateTime::GetTicks))
			.Function("GetTimeOfDay", BINDING_FUNCTION(&FDateTime::GetTimeOfDay))
			.Function("GetYear", BINDING_FUNCTION(&FDateTime::GetYear))
			.Function("IsAfternoon", BINDING_FUNCTION(&FDateTime::IsAfternoon))
			.Function("IsMorning", BINDING_FUNCTION(&FDateTime::IsMorning))
			.Function("ToHttpDate", BINDING_FUNCTION(&FDateTime::ToHttpDate))
			.Function("ToIso8601", BINDING_FUNCTION(&FDateTime::ToIso8601))
			.Function("ToString", BINDING_OVERLOAD(FString(FDateTime::*)()const, &FDateTime::ToString))
			.Function("ToUnixTimestamp", BINDING_FUNCTION(&FDateTime::ToUnixTimestamp))
			.Function("DaysInMonth", BINDING_FUNCTION(&FDateTime::DaysInMonth),
			          {"Year", "Month"})
			.Function("DaysInYear", BINDING_FUNCTION(&FDateTime::DaysInYear),
			          {"Year"})
			.Function("FromJulianDay", BINDING_FUNCTION(&FDateTime::FromJulianDay),
			          {"JulianDay"})
			.Function("FromUnixTimestamp", BINDING_FUNCTION(&FDateTime::FromUnixTimestamp),
			          {"UnixTime"})
			.Function("IsLeapYear", BINDING_FUNCTION(&FDateTime::IsLeapYear),
			          {"Year"})
			.Function("MaxValue", BINDING_FUNCTION(&FDateTime::MaxValue))
			.Function("MinValue", BINDING_FUNCTION(&FDateTime::MinValue))
			.Function("Now", BINDING_FUNCTION(&FDateTime::Now))
			.Function("Parse", BINDING_FUNCTION(&FDateTime::Parse),
			          {"DateTimeString", "OutDateTime"})
			.Function("ParseHttpDate", BINDING_FUNCTION(&FDateTime::ParseHttpDate),
			          {"HttpDate", "OutDateTime"})
			.Function("Today", BINDING_FUNCTION(&FDateTime::Today))
			.Function("UtcNow", BINDING_FUNCTION(&FDateTime::UtcNow))
			.Function("Validate", BINDING_FUNCTION(&FDateTime::Validate),
			          {"Year", "Month", "Day", "Hour", "Minute", "Second", "Millisecond"})
			.Register();
	}
};

static FRegisterDateTime RegisterDateTime;
