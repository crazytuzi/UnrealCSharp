#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "FRegisterForceInit.h"
#include "UEVersion.h"

namespace
{
	struct FRegisterVector2D
	{
		static FVector2D MultipliesImplementation(const FVector2D& In, const FVector2D::FReal Scalar)
		{
			return &In != nullptr ? In * Scalar : decltype(In * Scalar)();
		}

		static FVector2D MultipliesImplementation(const int32 Scale, const FVector2D& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector2D MultipliesImplementation(const float Scale, const FVector2D& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector2D MultipliesImplementation(const double Scale, const FVector2D& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector2D DividesImplementation(const FVector2D& In, const FVector2D::FReal Scalar)
		{
			return &In != nullptr ? In / Scalar : decltype(In / Scalar)();
		}

		static FVector2D PlusImplementation(const FVector2D& In, const FVector2D::FReal A)
		{
			return &In != nullptr && (&A != nullptr) ? In + A : decltype(In + A)();
		}

		static FVector2D MinusImplementation(const FVector2D& In, const FVector2D::FReal A)
		{
			return &In != nullptr && (&A != nullptr) ? In - A : decltype(In - A)();
		}

		static FVector2D::FReal BitOrImplementation(const FVector2D& In, const FVector2D& V)
		{
			return &In != nullptr && (&V != nullptr) ? In | V : decltype(In | V)();
		}

		static FVector2D::FReal BitXorImplementation(const FVector2D& In, const FVector2D& V)
		{
			return &In != nullptr && (&V != nullptr) ? In ^ V : decltype(In ^ V)();
		}

		FRegisterVector2D()
		{
			TBindingClassBuilder<FVector2D>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FVector2D, FVector2D::FReal, FVector2D::FReal),
				             TArray<FString>{"InX", "InY"})
				.Constructor(BINDING_CONSTRUCTOR(FVector2D, FVector2D::FReal),
				             TArray<FString>{"InF"})
				.Constructor(BINDING_CONSTRUCTOR(FVector2D, FIntPoint),
				             TArray<FString>{"InPos"})
				.Constructor(BINDING_CONSTRUCTOR(FVector2D, EForceInit))
				.Constructor(BINDING_CONSTRUCTOR(FVector2D, const FVector&),
				             TArray<FString>{"V"})
				.Constructor(BINDING_CONSTRUCTOR(FVector2D, const FVector4&),
				             TArray<FString>{"V"})
				.Plus()
				.Minus()
				.Multiplies()
				.Divides()
#if UE_VECTOR2_LESS
				.Less()
#endif
#if UE_VECTOR2_GREATER
				.Greater()
#endif
#if UE_VECTOR2_LESS_EQUAL
				.LessEqual()
#endif
#if UE_VECTOR2_GREATER_EQUAL
				.GreaterEqual()
#endif
				.UnaryMinus()
				.Subscript(BINDING_SUBSCRIPT(FVector2D, FVector2D::FReal, int32,
				                             TArray<FString>{"Index"}))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector2D(*)(const FVector2D&, const FVector2D::FReal),
				                           &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector2D(*)(const int32, const FVector2D&), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector2D(*)(const float, const FVector2D&), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector2D(*)(const double, const FVector2D&), &MultipliesImplementation))
				.Function("operator /", FUNCTION_DIVIDES, BINDING_FUNCTION(&DividesImplementation))
				.Function("operator +", FUNCTION_PLUS, BINDING_FUNCTION(&PlusImplementation))
				.Function("operator -", FUNCTION_MINUS, BINDING_FUNCTION(&MinusImplementation))
				.Function("operator |", FUNCTION_BIT_OR, BINDING_FUNCTION(&BitOrImplementation))
				.Function("operator ^", FUNCTION_BIT_XOR, BINDING_FUNCTION(&BitXorImplementation))
				.Property("ZeroVector", BINDING_READONLY_PROPERTY(&FVector2D::ZeroVector))
				.Property("UnitVector", BINDING_READONLY_PROPERTY(&FVector2D::UnitVector))
				.Property("Unit45Deg", BINDING_READONLY_PROPERTY(&FVector2D::Unit45Deg))
				.Function("Zero", BINDING_FUNCTION(&FVector2D::Zero))
				.Function("One", BINDING_FUNCTION(&FVector2D::One))
				.Function("UnitX", BINDING_FUNCTION(&FVector2D::UnitX))
				.Function("UnitY", BINDING_FUNCTION(&FVector2D::UnitY))
#if UE_VECTOR2_COMPONENT_WISE_ALL_LESS_THAN
				.Function("ComponentwiseAllLessThan", BINDING_FUNCTION(&FVector2D::ComponentwiseAllLessThan))
#endif
#if UE_VECTOR2_COMPONENT_WISE_ALL_GREATER_THAN
				.Function("ComponentwiseAllGreaterThan", BINDING_FUNCTION(&FVector2D::ComponentwiseAllGreaterThan))
#endif
#if UE_VECTOR2_COMPONENT_WISE_ALL_LESS_OR_EQUAL
				.Function("ComponentwiseAllLessOrEqual", BINDING_FUNCTION(&FVector2D::ComponentwiseAllLessOrEqual))
#endif
#if UE_VECTOR2_COMPONENT_WISE_ALL_GREATER_OR_EQUAL
				.Function("ComponentwiseAllGreaterOrEqual", BINDING_FUNCTION(&FVector2D::ComponentwiseAllGreaterOrEqual))
#endif
				.Function("Component", BINDING_OVERLOAD(FVector2D::FReal(FVector2D::*)(int32)const,
				                                        &FVector2D::Component,
				                                        TArray<FString>{"Index"}))
				.Function("DotProduct", BINDING_FUNCTION(&FVector2D::DotProduct,
				                                         TArray<FString>{"A", "B"}))
				.Function("DistSquared", BINDING_FUNCTION(&FVector2D::DistSquared,
				                                          TArray<FString>{"V1", "V2"}))
				.Function("Distance", BINDING_FUNCTION(&FVector2D::Distance,
				                                       TArray<FString>{"V1", "V2"}))
				.Function("CrossProduct", BINDING_FUNCTION(&FVector2D::CrossProduct,
				                                           TArray<FString>{"A", "B"}))
				.Function("Max", BINDING_FUNCTION(&FVector2D::Max,
				                                  TArray<FString>{"A", "B"}))
				.Function("Min", BINDING_FUNCTION(&FVector2D::Min,
				                                  TArray<FString>{"A", "B"}))
				.Function("Equals", BINDING_FUNCTION(&FVector2D::Equals,
				                                     TArray<FString>{"V", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Set", BINDING_FUNCTION(&FVector2D::Set,
				                                  TArray<FString>{"InX", "InY"}))
				.Function("GetMax", BINDING_FUNCTION(&FVector2D::GetMax))
				.Function("GetAbsMax", BINDING_FUNCTION(&FVector2D::GetAbsMax))
				.Function("GetMin", BINDING_FUNCTION(&FVector2D::GetMin))
				.Function("Size", BINDING_FUNCTION(&FVector2D::Size))
				.Function("Length", BINDING_FUNCTION(&FVector2D::Length))
				.Function("SizeSquared", BINDING_FUNCTION(&FVector2D::SizeSquared))
				.Function("SquaredLength", BINDING_FUNCTION(&FVector2D::SquaredLength))
				.Function("Dot", BINDING_FUNCTION(&FVector2D::Dot,
				                                  TArray<FString>{"V2"}))
				.Function("GetRotated", BINDING_FUNCTION(&FVector2D::GetRotated,
				                                         TArray<FString>{"AngleDeg"}))
				.Function("GetSafeNormal", BINDING_FUNCTION(&FVector2D::GetSafeNormal,
				                                            TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("Normalize", BINDING_FUNCTION(&FVector2D::Normalize,
				                                        TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("IsNearlyZero", BINDING_FUNCTION(&FVector2D::IsNearlyZero,
				                                           TArray<FString>{"Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("ToDirectionAndLength",
				          BINDING_OVERLOAD(void(FVector2D::*)(FVector2D&, double&)const,
				                           &FVector2D::ToDirectionAndLength,
				                           TArray<FString>{"OutDir", "OutLength"}))
				.Function("ToDirectionAndLength",
				          BINDING_OVERLOAD(void(FVector2D::*)(FVector2D&, float&)const,
				                           &FVector2D::ToDirectionAndLength,
				                           TArray<FString>{"OutDir", "OutLength"}))
				.Function("IsZero", BINDING_FUNCTION(&FVector2D::IsZero))
				.Function("IntPoint", BINDING_FUNCTION(&FVector2D::IntPoint))
				.Function("RoundToVector", BINDING_FUNCTION(&FVector2D::RoundToVector))
				.Function("ClampAxes", BINDING_FUNCTION(&FVector2D::ClampAxes,
				                                        TArray<FString>{"MinAxisVal", "MaxAxisVal"}))
				.Function("GetSignVector", BINDING_FUNCTION(&FVector2D::GetSignVector))
				.Function("GetAbs", BINDING_FUNCTION(&FVector2D::GetAbs))
				.Function("ToString", BINDING_FUNCTION(&FVector2D::ToString,
				                                       EFunctionInteract::New))
				.Function("InitFromString", BINDING_FUNCTION(&FVector2D::InitFromString,
				                                             TArray<FString>{"InSourceString"}))
				.Function("ContainsNaN", BINDING_FUNCTION(&FVector2D::ContainsNaN))
				.Function("SphericalToUnitCartesian", BINDING_FUNCTION(&FVector2D::SphericalToUnitCartesian));
		}
	};

	[[maybe_unused]] FRegisterVector2D RegisterVector2D;
}
