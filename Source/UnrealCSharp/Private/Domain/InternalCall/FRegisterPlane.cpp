#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterPlane
{
	static FPlane::FReal BitOrImplementation(const FPlane& In, const FPlane& V)
	{
		return In | V;
	}

	static FPlane DividesImplementation(const FPlane& In, const FPlane::FReal Scale)
	{
		return In / Scale;
	}

	static FPlane MultipliesImplementation(const FPlane& In, const FPlane::FReal Scale)
	{
		return In * Scale;
	}

	static FPlane MultipliesImplementation(FPlane& In, const FPlane& V)
	{
		return In * V;
	}

	FRegisterPlane()
	{
		TReflectionClassBuilder<FPlane>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FPlane, const FVector4&),
			             {"V"})
			.Constructor(BINDING_CONSTRUCTOR(FPlane, FPlane::FReal, FPlane::FReal, FPlane::FReal, FPlane::FReal),
			             {"InX", "InY", "InZ", "InW"})
			.Constructor(BINDING_CONSTRUCTOR(FPlane, FVector, FPlane::FReal),
			             {"InNormal", "InW"})
			.Constructor(BINDING_CONSTRUCTOR(FPlane, FVector, const FVector&),
			             {"InBase", "InNormal"})
			.Constructor(BINDING_CONSTRUCTOR(FPlane, FVector, FVector, FVector),
			             {"A", "B", "C"})
			.Constructor(BINDING_CONSTRUCTOR(FPlane, EForceInit))
			.Plus()
			.Minus()
			.Function("operator |", FUNCTION_BIT_OR, BINDING_FUNCTION(&BitOrImplementation))
			.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation))
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FPlane(*)(const FPlane&, const FPlane::FReal), &MultipliesImplementation))
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FPlane(*)(FPlane&, const FPlane&), &MultipliesImplementation))
			.Function("IsValid", BINDING_FUNCTION(&FPlane::IsValid))
			.Function("GetOrigin", BINDING_FUNCTION(&FPlane::GetOrigin))
			.Function("GetNormal", BINDING_FUNCTION(&FPlane::GetNormal))
			.Function("PlaneDot",BINDING_FUNCTION(&FPlane::PlaneDot),
			          {"P"})
			.Function("Normalize", BINDING_FUNCTION(&FPlane::Normalize),
			          {"Tolerance"}, EFunctionInteract::New)
			.Function("Flip",BINDING_FUNCTION(&FPlane::Flip))
			.Function("TransformBy", BINDING_FUNCTION(&FPlane::TransformBy),
			          {"M"})
			.Function("TransformByUsingAdjointT", BINDING_FUNCTION(&FPlane::TransformByUsingAdjointT),
			          {"M", "DetM", "TA"})
			.Function("TranslateBy", BINDING_FUNCTION(&FPlane::TranslateBy),
			          {"V"})
			.Function("Equals", BINDING_FUNCTION(&FPlane::Equals),
			          {"V", "Tolerance"})
			.Register();
	}
};

static FRegisterPlane RegisterPlane;
