#include "Domain/InternalCall/FTimespanImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

struct FRegisterTimespan
{
	FRegisterTimespan()
	{
		TScriptStructBuilder<FTimespan>(NAMESPACE_LIBRARY)
			.Function("Add", static_cast<void*>(FTimespanImplementation::Timespan_AddImplementation))
			.Function("Negated", static_cast<void*>(FTimespanImplementation::Timespan_NegatedImplementation))
			.Function("Subtract", static_cast<void*>(FTimespanImplementation::Timespan_SubtractImplementation))
			.Function("Multiply", static_cast<void*>(FTimespanImplementation::Timespan_MultiplyImplementation))
			.Function("Divide", static_cast<void*>(FTimespanImplementation::Timespan_DivideImplementation))
			.Function("Remainder", static_cast<void*>(FTimespanImplementation::Timespan_RemainderImplementation))
			.Function("Equality", static_cast<void*>(FTimespanImplementation::Timespan_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FTimespanImplementation::Timespan_InequalityImplementation))
			.Function("GreaterThan", static_cast<void*>(FTimespanImplementation::Timespan_GreaterThanImplementation))
			.Function("GreaterThanOrEqual",
			          static_cast<void*>(FTimespanImplementation::Timespan_GreaterThanOrEqualImplementation))
			.Function("LessThan", static_cast<void*>(FTimespanImplementation::Timespan_LessThanImplementation))
			.Function("LessThanOrEqual",
			          static_cast<void*>(FTimespanImplementation::Timespan_LessThanOrEqualImplementation))
			.Function("GetDays", static_cast<void*>(FTimespanImplementation::Timespan_GetDaysImplementation))
			.Function("GetDuration", static_cast<void*>(FTimespanImplementation::Timespan_GetDurationImplementation))
			.Function("GetFractionMicro",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetFractionMicroImplementation))
			.Function("GetFractionMilli",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetFractionMilliImplementation))
			.Function("GetFractionNano",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetFractionNanoImplementation))
			.Function("GetFractionTicks",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetFractionTicksImplementation))
			.Function("GetHours", static_cast<void*>(FTimespanImplementation::Timespan_GetHoursImplementation))
			.Function("GetMinutes", static_cast<void*>(FTimespanImplementation::Timespan_GetMinutesImplementation))
			.Function("GetSeconds", static_cast<void*>(FTimespanImplementation::Timespan_GetSecondsImplementation))
			.Function("GetTicks", static_cast<void*>(FTimespanImplementation::Timespan_GetTicksImplementation))
			.Function("GetTotalDays", static_cast<void*>(FTimespanImplementation::Timespan_GetTotalDaysImplementation))
			.Function("GetTotalHours",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetTotalHoursImplementation))
			.Function("GetTotalMicroseconds",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetTotalMicrosecondsImplementation))
			.Function("GetTotalMilliseconds",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetTotalMillisecondsImplementation))
			.Function("GetTotalMinutes",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetTotalMinutesImplementation))
			.Function("GetTotalSeconds",
			          static_cast<void*>(FTimespanImplementation::Timespan_GetTotalSecondsImplementation))
			.Function("IsZero", static_cast<void*>(FTimespanImplementation::Timespan_IsZeroImplementation))
			.Function("ToString", static_cast<void*>(FTimespanImplementation::Timespan_ToStringImplementation))
			.Function("FromDays", static_cast<void*>(FTimespanImplementation::Timespan_FromDaysImplementation))
			.Function("FromHours", static_cast<void*>(FTimespanImplementation::Timespan_FromHoursImplementation))
			.Function("FromMicroseconds",
			          static_cast<void*>(FTimespanImplementation::Timespan_FromMicrosecondsImplementation))
			.Function("FromMilliseconds",
			          static_cast<void*>(FTimespanImplementation::Timespan_FromMillisecondsImplementation))
			.Function("FromMinutes", static_cast<void*>(FTimespanImplementation::Timespan_FromMinutesImplementation))
			.Function("FromSeconds", static_cast<void*>(FTimespanImplementation::Timespan_FromSecondsImplementation))
			.Function("MaxValue", static_cast<void*>(FTimespanImplementation::Timespan_MaxValueImplementation))
			.Function("MinValue", static_cast<void*>(FTimespanImplementation::Timespan_MinValueImplementation))
			.Function("Parse", static_cast<void*>(FTimespanImplementation::Timespan_ParseImplementation))
			.Function("Ratio", static_cast<void*>(FTimespanImplementation::Timespan_RatioImplementation))
			.Function("Zero", static_cast<void*>(FTimespanImplementation::Timespan_ZeroImplementation))
			.Register();
	}
};

static FRegisterTimespan RegisterTimespan;

void FTimespanImplementation::Timespan_AddImplementation(const MonoObject* A, const MonoObject* B,
                                                         MonoObject** OutValue)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (TimespanA != nullptr && TimespanB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = TimespanA->operator+(*TimespanB);
	}
}

void FTimespanImplementation::Timespan_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->operator-();
	}
}

void FTimespanImplementation::Timespan_SubtractImplementation(const MonoObject* A, const MonoObject* B,
                                                              MonoObject** OutValue)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (TimespanA != nullptr && TimespanB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = TimespanA->operator-(*TimespanB);
	}
}

void FTimespanImplementation::Timespan_MultiplyImplementation(const MonoObject* InMonoObject, const double Scalar,
                                                              MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->operator*(Scalar);
	}
}

void FTimespanImplementation::Timespan_DivideImplementation(const MonoObject* InMonoObject, const double Scalar,
                                                            MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->operator/(Scalar);
	}
}

void FTimespanImplementation::Timespan_RemainderImplementation(const MonoObject* A, const MonoObject* B,
                                                               MonoObject** OutValue)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (TimespanA != nullptr && TimespanB != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = TimespanA->operator%(*TimespanB);
	}
}

bool FTimespanImplementation::Timespan_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator==(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator!=(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_GreaterThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator>(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator>=(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_LessThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator<(*TimespanB);
	}

	return false;
}

bool FTimespanImplementation::Timespan_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto TimespanA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(A);

	const auto TimespanB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(B);

	if (TimespanA != nullptr && TimespanB != nullptr)
	{
		return TimespanA->operator<=(*TimespanB);
	}

	return false;
}

int32 FTimespanImplementation::Timespan_GetDaysImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetDays();
	}

	return 0;
}

void FTimespanImplementation::Timespan_GetDurationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (Timespan != nullptr && OutTimespan != nullptr)
	{
		*OutTimespan = Timespan->GetDuration();
	}
}

int32 FTimespanImplementation::Timespan_GetFractionMicroImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionMicro();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetFractionMilliImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionMilli();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetFractionNanoImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionNano();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetFractionTicksImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetFractionTicks();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetHoursImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetHours();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetMinutesImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetMinutes();
	}

	return 0;
}

int32 FTimespanImplementation::Timespan_GetSecondsImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetSeconds();
	}

	return 0;
}

int64 FTimespanImplementation::Timespan_GetTicksImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTicks();
	}

	return 0;
}

double FTimespanImplementation::Timespan_GetTotalDaysImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalDays();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalHoursImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalHours();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalMicrosecondsImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalMicroseconds();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalMillisecondsImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalMilliseconds();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalMinutesImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalMinutes();
	}

	return 0.0;
}

double FTimespanImplementation::Timespan_GetTotalSecondsImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->GetTotalSeconds();
	}

	return 0.0;
}

bool FTimespanImplementation::Timespan_IsZeroImplementation(const MonoObject* InMonoObject)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		return Timespan->IsZero();
	}

	return false;
}

void FTimespanImplementation::Timespan_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Timespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(InMonoObject);

	if (Timespan != nullptr)
	{
		const auto ResultString = Timespan->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FTimespanImplementation::Timespan_FromDaysImplementation(const double Days, MonoObject** OutValue)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

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
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTimespan)),
		CLASS_SCRIPT_STRUCT_NAME(FTimespan));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTimespan = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTimespan>(NewMonoObject);

	if (OutTimespan != nullptr)
	{
		*OutTimespan = FTimespan::Zero();
	}
}
