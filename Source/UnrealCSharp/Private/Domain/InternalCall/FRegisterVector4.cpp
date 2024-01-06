#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterVector4
{
	FRegisterVector4()
	{
		TReflectionClassBuilder<FVector4>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FVector4, const FVector&),
			             {"InVector"})
			.Constructor(BINDING_CONSTRUCTOR(FVector4, const FLinearColor&),
			             {"InColor"})
			.Constructor(BINDING_CONSTRUCTOR(FVector4, const FLinearColor&, FVector4::FReal),
			             {"InColor", "InOverrideW"})
			.Constructor(BINDING_CONSTRUCTOR(FVector4, FVector4::FReal, FVector4::FReal, FVector4::FReal,
			                                 FVector4::FReal)			             ,
			             {"InX", "InY", "InZ", "InW"})
			.Constructor(BINDING_CONSTRUCTOR(FVector4, FVector2D, FVector2D),
			             {"InXY", "InZW"})
			.Constructor(BINDING_CONSTRUCTOR(FVector4, EForceInit))
			.Subscript(BINDING_SUBSCRIPT(FVector4, FVector4::FReal, int32),
			           {"ComponentIndex"})
			.UnaryMinus()
			.Plus()
			.Minus()
			.Multiplies()
			.Divides()
			.BitXor()
			.Function("Zero", BINDING_FUNCTION(&FVector4::Zero))
			.Function("One", BINDING_FUNCTION(&FVector4::One))
			.Function("Component",
			          BINDING_OVERLOAD(const FVector4::FReal&(FVector4::*)(int32)const, &FVector4::Component),
			          {"Index"})
			.Function("Equals", BINDING_FUNCTION(&FVector4::Equals),
			          {"V", "Tolerance"})
			.Function("IsUnit3", BINDING_FUNCTION(&FVector4::IsUnit3),
			          {"LengthSquaredTolerance"})
			.Function("ToString", BINDING_FUNCTION(&FVector4::ToString))
			.Function("InitFromString", BINDING_FUNCTION(&FVector4::InitFromString),
			          {"InSourceString"})
			.Function("GetSafeNormal", BINDING_FUNCTION(&FVector4::GetSafeNormal),
			          {"Tolerance"})
			.Function("GetUnsafeNormal3", BINDING_FUNCTION(&FVector4::GetUnsafeNormal3))
			.Function("ToOrientationRotator", BINDING_FUNCTION(&FVector4::ToOrientationRotator))
			.Function("ToOrientationQuat", BINDING_FUNCTION(&FVector4::ToOrientationQuat))
			.Function("Rotation", BINDING_FUNCTION(&FVector4::Rotation))
			.Function("Set", BINDING_FUNCTION(&FVector4::Set),
			          {"InX", "InY", "InZ", "InW"})
			.Function("Size3", BINDING_FUNCTION(&FVector4::Size3))
			.Function("SizeSquared3", BINDING_FUNCTION(&FVector4::SizeSquared3))
			.Function("Size", BINDING_FUNCTION(&FVector4::Size))
			.Function("SizeSquared", BINDING_FUNCTION(&FVector4::SizeSquared))
			.Function("ContainsNaN", BINDING_FUNCTION(&FVector4::ContainsNaN))
			.Function("IsNearlyZero3", BINDING_FUNCTION(&FVector4::IsNearlyZero3),
			          {"Tolerance"})
			.Function("Reflect3", BINDING_FUNCTION(&FVector4::Reflect3),
			          {"Normal"})
			.Function("FindBestAxisVectors3", BINDING_FUNCTION(&FVector4::FindBestAxisVectors3),
			          {"Axis1", "Axis2"})
			.Register();
	}
};

static FRegisterVector4 RegisterVector4;
