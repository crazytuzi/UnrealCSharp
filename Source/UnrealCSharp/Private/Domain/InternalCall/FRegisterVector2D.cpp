#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterVector2D
{
	static FVector2D MultipliesImplementation(const FVector2D& In, const FVector2D::FReal Scalar)
	{
		return In * Scalar;
	}

	static FVector2D DividesImplementation(const FVector2D& In, const FVector2D::FReal Scalar)
	{
		return In / Scalar;
	}

	static FVector2D PlusImplementation(const FVector2D& In, const FVector2D::FReal A)
	{
		return In + A;
	}

	static FVector2D MinusImplementation(const FVector2D& In, const FVector2D::FReal A)
	{
		return In - A;
	}

	static FVector2D::FReal BitOrImplementation(const FVector2D& In, const FVector2D& V)
	{
		return In | V;
	}

	static FVector2D::FReal BitXorImplementation(const FVector2D& In, const FVector2D& V)
	{
		return In ^ V;
	}

	FRegisterVector2D()
	{
		TBindingClassBuilder<FVector2D>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FVector2D, FVector2D::FReal, FVector2D::FReal),
			             {"InX", "InY"})
			.Constructor(BINDING_CONSTRUCTOR(FVector2D, FVector2D::FReal),
			             {"InF"})
			.Constructor(BINDING_CONSTRUCTOR(FVector2D, FIntPoint),
			             {"InPos"})
			.Constructor(BINDING_CONSTRUCTOR(FVector2D, EForceInit))
			.Constructor(BINDING_CONSTRUCTOR(FVector2D, const FVector&),
			             {"V"})
			.Constructor(BINDING_CONSTRUCTOR(FVector2D, const FVector4&),
			             {"V"})
			.Plus()
			.Minus()
			.Multiplies()
			.Divides()
			.Less()
			.Greater()
			.LessEqual()
			.GreaterEqual()
			.UnaryMinus()
			.Subscript(BINDING_SUBSCRIPT(FVector2D, FVector2D::FReal, int32),
			           {"Index"})
			.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
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
			.Function("Component", BINDING_OVERLOAD(FVector2D::FReal(FVector2D::*)(int32)const, &FVector2D::Component),
			          {"Index"})
			.Function("DotProduct", BINDING_FUNCTION(&FVector2D::DotProduct),
			          {"A", "B"})
			.Function("DistSquared", BINDING_FUNCTION(&FVector2D::DistSquared),
			          {"V1", "V2"})
			.Function("Distance", BINDING_FUNCTION(&FVector2D::Distance),
			          {"V1", "V2"})
			.Function("CrossProduct", BINDING_FUNCTION(&FVector2D::CrossProduct),
			          {"A", "B"})
			.Function("Max", BINDING_FUNCTION(&FVector2D::Max),
			          {"A", "B"})
			.Function("Min", BINDING_FUNCTION(&FVector2D::Min),
			          {"A", "B"})
			.Function("Equals", BINDING_FUNCTION(&FVector2D::Equals),
			          {"V", "Tolerance"})
			.Function("Set", BINDING_FUNCTION(&FVector2D::Set),
			          {"InX", "InY"})
			.Function("GetMax", BINDING_FUNCTION(&FVector2D::GetMax))
			.Function("GetAbsMax", BINDING_FUNCTION(&FVector2D::GetAbsMax))
			.Function("GetMin", BINDING_FUNCTION(&FVector2D::GetMin))
			.Function("Size", BINDING_FUNCTION(&FVector2D::Size))
			.Function("Length", BINDING_FUNCTION(&FVector2D::Length))
			.Function("SizeSquared", BINDING_FUNCTION(&FVector2D::SizeSquared))
			.Function("SquaredLength", BINDING_FUNCTION(&FVector2D::SquaredLength))
			.Function("Dot", BINDING_FUNCTION(&FVector2D::Dot),
			          {"V2"})
			.Function("GetRotated", BINDING_FUNCTION(&FVector2D::GetRotated),
			          {"AngleDeg"})
			.Function("GetSafeNormal", BINDING_FUNCTION(&FVector2D::GetSafeNormal),
			          {"Tolerance"})
			.Function("Normalize", BINDING_FUNCTION(&FVector2D::Normalize),
			          {"Tolerance"})
			.Function("IsNearlyZero", BINDING_FUNCTION(&FVector2D::IsNearlyZero),
			          {"Tolerance"})
			.Function("ToDirectionAndLength",
			          BINDING_OVERLOAD(void(FVector2D::*)(FVector2D&, double&)const, &FVector2D::ToDirectionAndLength),
			          {"OutDir", "OutLength"})
			.Function("ToDirectionAndLength",
			          BINDING_OVERLOAD(void(FVector2D::*)(FVector2D&, float&)const, &FVector2D::ToDirectionAndLength),
			          {"OutDir", "OutLength"})
			.Function("IsZero", BINDING_FUNCTION(&FVector2D::IsZero))
			.Function("IntPoint", BINDING_FUNCTION(&FVector2D::IntPoint))
			.Function("RoundToVector", BINDING_FUNCTION(&FVector2D::RoundToVector))
			.Function("ClampAxes", BINDING_FUNCTION(&FVector2D::ClampAxes),
			          {"MinAxisVal", "MaxAxisVal"})
			.Function("GetSignVector", BINDING_FUNCTION(&FVector2D::GetSignVector))
			.Function("GetAbs", BINDING_FUNCTION(&FVector2D::GetAbs))
			.Function("ToString", BINDING_FUNCTION(&FVector2D::ToString),
			          {}, EFunctionInteract::New)
			.Function("InitFromString", BINDING_FUNCTION(&FVector2D::InitFromString),
			          {"InSourceString"})
			.Function("ContainsNaN", BINDING_FUNCTION(&FVector2D::ContainsNaN))
			.Function("SphericalToUnitCartesian", BINDING_FUNCTION(&FVector2D::SphericalToUnitCartesian))
			.Register();
	}
};

static FRegisterVector2D RegisterVector2D;
