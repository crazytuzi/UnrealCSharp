#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterFrameTime
	{
		static FFrameTime MultipliesImplementation(const FFrameTime& In, const float Scalar)
		{
			return &In != nullptr ? In * Scalar : decltype(In * Scalar)();
		}

		static FFrameTime DividesImplementation(const FFrameTime& In, const float Scalar)
		{
			return &In != nullptr ? In / Scalar : decltype(In / Scalar)();
		}

		FRegisterFrameTime()
		{
			TBindingClassBuilder<FFrameTime>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FFrameTime, int32),
				             TArray<FString>{"InFrameNumber"})
				.Constructor(BINDING_CONSTRUCTOR(FFrameTime, FFrameNumber),
				             TArray<FString>{"InFrameNumber"})
				.Constructor(BINDING_CONSTRUCTOR(FFrameTime, FFrameNumber, float),
				             TArray<FString>{"InFrameNumber", "InSubFrame"})
				.Greater()
				.GreaterEqual()
				.Less()
				.LessEqual()
				.Plus()
				.Minus()
				.Modulus()
				.UnaryMinus()
				.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
				.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation))
				.Property("MaxSubframe", BINDING_READONLY_PROPERTY(&FFrameTime::MaxSubframe))
				.Function("GetFrame", BINDING_FUNCTION(&FFrameTime::GetFrame))
				.Function("GetSubFrame", BINDING_FUNCTION(&FFrameTime::GetSubFrame))
				.Function("FloorToFrame", BINDING_FUNCTION(&FFrameTime::FloorToFrame))
				.Function("CeilToFrame", BINDING_FUNCTION(&FFrameTime::CeilToFrame))
				.Function("RoundToFrame", BINDING_FUNCTION(&FFrameTime::RoundToFrame))
				.Function("AsDecimal", BINDING_FUNCTION(&FFrameTime::AsDecimal))
				.Function("FromDecimal", BINDING_FUNCTION(&FFrameTime::FromDecimal,
				                                          TArray<FString>{"InDecimalFrame"}));
		}
	};

	[[maybe_unused]] FRegisterFrameTime RegisterFrameTime;
}
