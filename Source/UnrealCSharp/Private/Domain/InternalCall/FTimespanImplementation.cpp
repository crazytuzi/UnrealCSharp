﻿#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterTimespan
{
	static FTimespan MultipliesImplementation(const FTimespan& In, const double Scalar)
	{
		return In * Scalar;
	}

	static FTimespan DividesImplementation(const FTimespan& In, const double Scalar)
	{
		return In / Scalar;
	}

	FRegisterTimespan()
	{
		TReflectionClassBuilder<FTimespan>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FTimespan, int64),
			             {"InTicks"})
			.Constructor(BINDING_CONSTRUCTOR(FTimespan, int32, int32, int32),
			             {"Hours", "Minutes", "Seconds"})
			.Constructor(BINDING_CONSTRUCTOR(FTimespan, int32, int32, int32, int32),
			             {"Days", "Hours", "Minutes", "Seconds"})
			.Constructor(BINDING_CONSTRUCTOR(FTimespan, int32, int32, int32, int32, int32),
			             {"Days", "Hours", "Minutes", "Seconds", "FractionNano"})
			.Plus()
			.UnaryMinus()
			.Minus()
			.Modulus()
			.Greater()
			.GreaterEqual()
			.Less()
			.LessEqual()
			.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
			.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation))
			.Function("GetDays", BINDING_FUNCTION(&FTimespan::GetDays))
			.Function("GetDuration", BINDING_FUNCTION(&FTimespan::GetDuration))
			.Function("GetFractionMicro", BINDING_FUNCTION(&FTimespan::GetFractionMicro))
			.Function("GetFractionMilli", BINDING_FUNCTION(&FTimespan::GetFractionMilli))
			.Function("GetFractionNano", BINDING_FUNCTION(&FTimespan::GetFractionNano))
			.Function("GetFractionTicks", BINDING_FUNCTION(&FTimespan::GetFractionTicks))
			.Function("GetHours", BINDING_FUNCTION(&FTimespan::GetHours))
			.Function("GetMinutes", BINDING_FUNCTION(&FTimespan::GetMinutes))
			.Function("GetSeconds", BINDING_FUNCTION(&FTimespan::GetSeconds))
			.Function("GetTicks", BINDING_FUNCTION(&FTimespan::GetTicks))
			.Function("GetTotalDays", BINDING_FUNCTION(&FTimespan::GetTotalDays))
			.Function("GetTotalHours", BINDING_FUNCTION(&FTimespan::GetTotalHours))
			.Function("GetTotalMicroseconds", BINDING_FUNCTION(&FTimespan::GetTotalMicroseconds))
			.Function("GetTotalMilliseconds", BINDING_FUNCTION(&FTimespan::GetTotalMilliseconds))
			.Function("GetTotalMinutes", BINDING_FUNCTION(&FTimespan::GetTotalMinutes))
			.Function("GetTotalSeconds", BINDING_FUNCTION(&FTimespan::GetTotalSeconds))
			.Function("IsZero", BINDING_FUNCTION(&FTimespan::IsZero))
			.Function("ToString", BINDING_OVERLOAD(FString(FTimespan::*)()const, &FTimespan::ToString))
			.Function("FromDays", BINDING_FUNCTION(&FTimespan::FromDays),
			          {"Days"})
			.Function("FromHours", BINDING_FUNCTION(&FTimespan::FromHours),
			          {"Hours"})
			.Function("FromMicroseconds", BINDING_FUNCTION(&FTimespan::FromMicroseconds),
			          {"Microseconds"})
			.Function("FromMilliseconds", BINDING_FUNCTION(&FTimespan::FromMilliseconds),
			          {"Milliseconds"})
			.Function("FromMinutes", BINDING_FUNCTION(&FTimespan::FromMinutes),
			          {"Minutes"})
			.Function("FromSeconds", BINDING_FUNCTION(&FTimespan::FromSeconds),
			          {"Seconds"})
			.Function("MaxValue", BINDING_FUNCTION(&FTimespan::MaxValue))
			.Function("MinValue", BINDING_FUNCTION(&FTimespan::MinValue))
			.Function("Parse", BINDING_FUNCTION(&FTimespan::Parse),
			          {"TimespanString", "OutTimespan"})
			.Function("Ratio", BINDING_FUNCTION(&FTimespan::Ratio),
			          {"Dividend", "Divisor"})
			.Function("Zero", BINDING_FUNCTION(&FTimespan::Zero))
			.Register();
	}
};

static FRegisterTimespan RegisterTimespan;
