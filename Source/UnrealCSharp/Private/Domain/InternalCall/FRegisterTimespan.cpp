#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterTimespan
	{
		static FTimespan MultipliesImplementation(const FTimespan& In, const double Scalar)
		{
			return &In != nullptr ? In * Scalar : decltype(In * Scalar)();
		}

		static FTimespan DividesImplementation(const FTimespan& In, const double Scalar)
		{
			return &In != nullptr ? In / Scalar : decltype(In / Scalar)();
		}

		FRegisterTimespan()
		{
			TBindingClassBuilder<FTimespan>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FTimespan, int64),
				             TArray<FString>{"InTicks"})
				.Constructor(BINDING_CONSTRUCTOR(FTimespan, int32, int32, int32),
				             TArray<FString>{"Hours", "Minutes", "Seconds"})
				.Constructor(BINDING_CONSTRUCTOR(FTimespan, int32, int32, int32, int32),
				             TArray<FString>{"Days", "Hours", "Minutes", "Seconds"})
				.Constructor(BINDING_CONSTRUCTOR(FTimespan, int32, int32, int32, int32, int32),
				             TArray<FString>{"Days", "Hours", "Minutes", "Seconds", "FractionNano"})
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
				.Function("ToString", BINDING_OVERLOAD(FString(FTimespan::*)()const, &FTimespan::ToString,
				                                       EFunctionInteract::New))
				.Function("FromDays", BINDING_FUNCTION(&FTimespan::FromDays,
				                                       TArray<FString>{"Days"}))
				.Function("FromHours", BINDING_FUNCTION(&FTimespan::FromHours,
				                                        TArray<FString>{"Hours"}))
				.Function("FromMicroseconds", BINDING_FUNCTION(&FTimespan::FromMicroseconds,
				                                               TArray<FString>{"Microseconds"}))
				.Function("FromMilliseconds", BINDING_FUNCTION(&FTimespan::FromMilliseconds,
				                                               TArray<FString>{"Milliseconds"}))
				.Function("FromMinutes", BINDING_FUNCTION(&FTimespan::FromMinutes,
				                                          TArray<FString>{"Minutes"}))
				.Function("FromSeconds", BINDING_FUNCTION(&FTimespan::FromSeconds,
				                                          TArray<FString>{"Seconds"}))
				.Function("MaxValue", BINDING_FUNCTION(&FTimespan::MaxValue))
				.Function("MinValue", BINDING_FUNCTION(&FTimespan::MinValue))
				.Function("Parse", BINDING_FUNCTION(&FTimespan::Parse,
				                                    TArray<FString>{"TimespanString", "OutTimespan"}))
				.Function("Ratio", BINDING_FUNCTION(&FTimespan::Ratio,
				                                    TArray<FString>{"Dividend", "Divisor"}))
				.Function("Zero", BINDING_FUNCTION(&FTimespan::Zero));
		}
	};

	[[maybe_unused]] FRegisterTimespan RegisterTimespan;
}
