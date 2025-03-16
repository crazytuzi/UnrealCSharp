#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterFrameNumber
	{
		static FFrameNumber MultipliesImplementation(const FFrameNumber& In, const float Scalar)
		{
			return &In != nullptr ? In * Scalar : decltype(In * Scalar)();
		}

		static FFrameNumber DividesImplementation(const FFrameNumber& In, const float Scalar)
		{
			return &In != nullptr ? In / Scalar : decltype(In / Scalar)();
		}

		FRegisterFrameNumber()
		{
			TBindingClassBuilder<FFrameNumber>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FFrameNumber, int32),
				             TArray<FString>{"InValue"})
				.PreIncrement()
				.PreDecrement()
				.Less()
				.Greater()
				.LessEqual()
				.GreaterEqual()
				.Plus()
				.Minus()
				.Modulus()
				.UnaryMinus()
				.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
				.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation));
		}
	};

	[[maybe_unused]] FRegisterFrameNumber RegisterFrameNumber;
}
