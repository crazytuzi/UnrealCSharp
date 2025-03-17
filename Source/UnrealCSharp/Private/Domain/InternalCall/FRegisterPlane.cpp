#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "FRegisterForceInit.h"

namespace
{
	struct FRegisterPlane
	{
		static FPlane::FReal BitOrImplementation(const FPlane& In, const FPlane& V)
		{
			return &In != nullptr && (&V != nullptr) ? In | V : decltype(In | V)();
		}

		static FPlane DividesImplementation(const FPlane& In, const FPlane::FReal Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		static FPlane MultipliesImplementation(const FPlane& In, const FPlane::FReal Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FPlane MultipliesImplementation(FPlane& In, const FPlane& V)
		{
			return &In != nullptr && (&V != nullptr) ? In * V : decltype(In * V)();
		}

		FRegisterPlane()
		{
			TBindingClassBuilder<FPlane>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FPlane, const FVector4&),
				             TArray<FString>{"V"})
				.Constructor(BINDING_CONSTRUCTOR(FPlane, FPlane::FReal, FPlane::FReal, FPlane::FReal, FPlane::FReal),
				             TArray<FString>{"InX", "InY", "InZ", "InW"})
				.Constructor(BINDING_CONSTRUCTOR(FPlane, FVector, FPlane::FReal),
				             TArray<FString>{"InNormal", "InW"})
				.Constructor(BINDING_CONSTRUCTOR(FPlane, FVector, const FVector&),
				             TArray<FString>{"InBase", "InNormal"})
				.Constructor(BINDING_CONSTRUCTOR(FPlane, FVector, FVector, FVector),
				             TArray<FString>{"A", "B", "C"})
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
				.Function("PlaneDot",BINDING_FUNCTION(&FPlane::PlaneDot,
				                                      TArray<FString>{"P"}))
				.Function("Normalize", BINDING_FUNCTION(&FPlane::Normalize,
				                                        TArray<FString>{"Tolerance"}, EFunctionInteract::New,
				                                        SMALL_NUMBER))
				.Function("Flip",BINDING_FUNCTION(&FPlane::Flip))
				.Function("TransformBy", BINDING_FUNCTION(&FPlane::TransformBy,
				                                          TArray<FString>{"M"}))
				.Function("TransformByUsingAdjointT", BINDING_FUNCTION(&FPlane::TransformByUsingAdjointT,
				                                                       TArray<FString>{"M", "DetM", "TA"}))
				.Function("TranslateBy", BINDING_FUNCTION(&FPlane::TranslateBy,
				                                          TArray<FString>{"V"}))
				.Function("Equals", BINDING_FUNCTION(&FPlane::Equals,
				                                     TArray<FString>{"V", "Tolerance"}, KINDA_SMALL_NUMBER));
		}
	};

	[[maybe_unused]] FRegisterPlane RegisterPlane;
}
