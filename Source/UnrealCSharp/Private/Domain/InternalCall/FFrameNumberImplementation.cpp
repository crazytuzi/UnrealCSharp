﻿#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterFrameNumber
{
	static FFrameNumber MultipliesImplementation(const FFrameNumber& In, const float Scalar)
	{
		return In * Scalar;
	}

	static FFrameNumber DividesImplementation(const FFrameNumber& In, const float Scalar)
	{
		return In / Scalar;
	}

	FRegisterFrameNumber()
	{
		TReflectionClassBuilder<FFrameNumber>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FFrameNumber, int32),
			             {"InValue"})
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
			.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation))
			.Register();
	}
};

static FRegisterFrameNumber RegisterFrameNumber;
