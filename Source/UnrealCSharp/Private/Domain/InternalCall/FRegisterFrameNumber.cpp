#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

#ifdef _MSC_VER
#pragma warning (push)

#pragma warning (disable: 5103)
#endif

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

static FRegisterFrameNumber RegisterFrameNumber;

#ifdef _MSC_VER
#pragma warning (pop)
#endif
