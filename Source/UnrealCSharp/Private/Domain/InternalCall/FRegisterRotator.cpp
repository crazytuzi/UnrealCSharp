#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterRotator
{
	static FRotator MultipliesImplementation(const FRotator& In, const int32 Scale)
	{
		return In * Scale;
	}

	static FRotator MultipliesImplementation(const FRotator& In, const float Scale)
	{
		return In * Scale;
	}

	static FRotator MultipliesImplementation(const FRotator& In, const double Scale)
	{
		return In * Scale;
	}

	FRegisterRotator()
	{
		TBindingClassBuilder<FRotator>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FRotator, FRotator::FReal),
			             {"InF"})
			.Constructor(BINDING_CONSTRUCTOR(FRotator, FRotator::FReal, FRotator::FReal, FRotator::FReal),
			             {"InPitch", "InYaw", "InRoll"})
			.Constructor(BINDING_CONSTRUCTOR(FRotator, EForceInit))
			.Constructor(BINDING_CONSTRUCTOR(FRotator, FQuat),
			             {"Quat"})
			.Plus()
			.Minus()
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FRotator(*)(const FRotator&, const int32), &MultipliesImplementation))
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FRotator(*)(const FRotator&, const float), &MultipliesImplementation))
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FRotator(*)(const FRotator&, const double), &MultipliesImplementation))
			.Function("IsNearlyZero", BINDING_FUNCTION(&FRotator::IsNearlyZero),
			          {"Tolerance"})
			.Function("IsZero", BINDING_FUNCTION(&FRotator::IsZero))
			.Function("Equals", BINDING_FUNCTION(&FRotator::IsNearlyZero),
			          {"R", "Tolerance"})
			.Function("Add", BINDING_FUNCTION(&FRotator::Add),
			          {"DeltaPitch", "DeltaYaw", "DeltaRoll"})
			.Function("GetInverse", BINDING_FUNCTION(&FRotator::GetInverse))
			.Function("GridSnap", BINDING_FUNCTION(&FRotator::GridSnap),
			          {"RotGrid"})
			.Function("Vector", BINDING_FUNCTION(&FRotator::Vector))
			.Function("Quaternion", BINDING_FUNCTION(&FRotator::Quaternion))
			.Function("Euler", BINDING_FUNCTION(&FRotator::Euler))
			.Function("RotateVector", BINDING_FUNCTION(&FRotator::RotateVector),
			          {"V"})
			.Function("UnrotateVector", BINDING_FUNCTION(&FRotator::UnrotateVector),
			          {"V"})
			.Function("Clamp", BINDING_FUNCTION(&FRotator::Clamp))
			.Function("GetNormalized", BINDING_FUNCTION(&FRotator::GetNormalized))
			.Function("GetDenormalized", BINDING_FUNCTION(&FRotator::GetDenormalized))
			.Function("GetComponentForAxis", BINDING_FUNCTION(&FRotator::GetComponentForAxis),
			          {"Axis"})
			.Function("SetComponentForAxis", BINDING_FUNCTION(&FRotator::GetComponentForAxis),
			          {"Axis", "Component"})
			.Function("Normalize", BINDING_FUNCTION(&FRotator::Normalize))
			.Function("GetWindingAndRemainder", BINDING_FUNCTION(&FRotator::GetWindingAndRemainder),
			          {"Winding", "Remainder"})
			.Function("GetManhattanDistance", BINDING_FUNCTION(&FRotator::GetManhattanDistance),
			          {"Rotator"})
			.Function("GetEquivalentRotator", BINDING_FUNCTION(&FRotator::GetEquivalentRotator))
			.Function("SetClosestToMe", BINDING_FUNCTION(&FRotator::SetClosestToMe),
			          {"MakeClosest"})
			.Function("ToString", BINDING_FUNCTION(&FRotator::ToString),
			          {}, EFunctionInteract::New)
			.Function("ToCompactString", BINDING_FUNCTION(&FRotator::ToCompactString))
			.Function("InitFromString", BINDING_FUNCTION(&FRotator::InitFromString),
			          {"InSourceString"})
			.Function("ContainsNaN", BINDING_FUNCTION(&FRotator::ContainsNaN))
			.Function("ClampAxis", BINDING_FUNCTION(&FRotator::ClampAxis),
			          {"Angle"})
			.Function("NormalizeAxis", BINDING_FUNCTION(&FRotator::NormalizeAxis),
			          {"Angle"})
			.Function("CompressAxisToByte", BINDING_FUNCTION(&FRotator::CompressAxisToByte),
			          {"Angle"})
			.Function("DecompressAxisFromByte", BINDING_FUNCTION(&FRotator::DecompressAxisFromByte),
			          {"Angle"})
			.Function("CompressAxisToShort", BINDING_FUNCTION(&FRotator::CompressAxisToShort),
			          {"Angle"})
			.Function("DecompressAxisFromShort", BINDING_FUNCTION(&FRotator::DecompressAxisFromShort),
			          {"Angle"})
			.Function("MakeFromEuler", BINDING_FUNCTION(&FRotator::MakeFromEuler),
			          {"Euler"})
			.Register();
	}
};

static FRegisterRotator RegisterRotator;
