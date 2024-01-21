#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterQuat
{
	static FVector MultipliesImplementation(const FQuat& In, const FVector& Scalar)
	{
		return In * Scalar;
	}

	static FQuat MultipliesImplementation(const FQuat& In, const float Scale)
	{
		return In * Scale;
	}

	static FQuat MultipliesImplementation(const FQuat& In, const double Scale)
	{
		return In * Scale;
	}

	static FQuat DividesImplementation(const FQuat& In, const float Scale)
	{
		return In / Scale;
	}

	static FQuat DividesImplementation(const FQuat& In, const double Scale)
	{
		return In / Scale;
	}

	static FQuat::FReal BitOrImplementation(const FQuat& In, const FQuat& Q)
	{
		return In | Q;
	}

	FRegisterQuat()
	{
		TReflectionClassBuilder<FQuat>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FQuat, EForceInit))
			.Constructor(BINDING_CONSTRUCTOR(FQuat, FQuat::FReal, FQuat::FReal, FQuat::FReal, FQuat::FReal),
			             {"InX", "InY", "InZ", "InW"})
			.Constructor(BINDING_CONSTRUCTOR(FQuat, FQuat::FReal),
			             {"V"})
			.Constructor(BINDING_CONSTRUCTOR(FQuat, const FRotator&),
			             {"R"})
			.Constructor(BINDING_CONSTRUCTOR(FQuat, const FMatrix&),
			             {"M"})
			.Constructor(BINDING_CONSTRUCTOR(FQuat, FVector, FQuat::FReal),
			             {"Axis", "AngleRad"})
			.Plus()
			.Minus()
			.UnaryMinus()
			.Multiplies()
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FVector(*)(const FQuat&, const FVector&), &MultipliesImplementation))
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FQuat(*)(const FQuat&, const float), &MultipliesImplementation))
			.Function("operator *", FUNCTION_MULTIPLIES,
			          BINDING_OVERLOAD(FQuat(*)(const FQuat&, const double), &MultipliesImplementation))
			.Function("operator /", FUNCTION_DIVIDES,
			          BINDING_OVERLOAD(FQuat(*)(const FQuat&, const float), &DividesImplementation))
			.Function("operator /", FUNCTION_DIVIDES,
			          BINDING_OVERLOAD(FQuat(*)(const FQuat&, const double), &DividesImplementation))
			.Function("operator |", FUNCTION_BIT_OR, BINDING_FUNCTION(&BitOrImplementation))
			.Property("Identity", BINDING_READONLY_PROPERTY(&FQuat::Identity))
			.Function("MakeFromRotator", BINDING_FUNCTION(&FQuat::MakeFromRotator))
			.Function("Equals", BINDING_FUNCTION(&FQuat::Equals),
			          {"Q", "Tolerance"})
			.Function("IsIdentity", BINDING_FUNCTION(&FQuat::IsIdentity),
			          {"Tolerance"})
			.Function("Identical", BINDING_FUNCTION(&FQuat::Identical),
			          {"Q", "PortFlags"})
			.Function("MakeFromEuler", BINDING_FUNCTION(&FQuat::MakeFromEuler),
			          {"Euler"})
			.Function("Euler", BINDING_FUNCTION(&FQuat::Euler))
			.Function("Normalize", BINDING_FUNCTION(&FQuat::Normalize),
			          {"Tolerance"})
			.Function("GetNormalized", BINDING_FUNCTION(&FQuat::GetNormalized),
			          {"Tolerance"})
			.Function("IsNormalized", BINDING_FUNCTION(&FQuat::IsNormalized))
			.Function("Size", BINDING_FUNCTION(&FQuat::Size))
			.Function("SizeSquared", BINDING_FUNCTION(&FQuat::SizeSquared))
			.Function("GetAngle", BINDING_FUNCTION(&FQuat::GetAngle))
			.Function("ToAxisAndAngle", BINDING_OVERLOAD(void(FQuat::*)(FVector&, float&)const, &FQuat::ToAxisAndAngle),
			          {"Axis", "Angle"})
			.Function("ToAxisAndAngle",
			          BINDING_OVERLOAD(void(FQuat::*)(FVector&, double&)const, &FQuat::ToAxisAndAngle),
			          {"Axis", "Angle"})
			.Function("ToSwingTwist", BINDING_FUNCTION(&FQuat::ToSwingTwist),
			          {"InTwistAxis", "OutSwing", "OutTwist"})
			.Function("GetTwistAngle", BINDING_FUNCTION(&FQuat::GetTwistAngle),
			          {"TwistAxis"})
			.Function("RotateVector", BINDING_FUNCTION(&FQuat::RotateVector),
			          {"V"})
			.Function("UnrotateVector", BINDING_FUNCTION(&FQuat::UnrotateVector),
			          {"V"})
			.Function("Log", BINDING_FUNCTION(&FQuat::Log))
			.Function("Exp", BINDING_FUNCTION(&FQuat::Exp))
			.Function("Inverse", BINDING_FUNCTION(&FQuat::Inverse))
			.Function("EnforceShortestArcWith", BINDING_FUNCTION(&FQuat::EnforceShortestArcWith),
			          {"OtherQuat"})
			.Function("GetAxisX", BINDING_FUNCTION(&FQuat::GetAxisX))
			.Function("GetAxisY", BINDING_FUNCTION(&FQuat::GetAxisY))
			.Function("GetAxisZ", BINDING_FUNCTION(&FQuat::GetAxisZ))
			.Function("GetForwardVector", BINDING_FUNCTION(&FQuat::GetForwardVector))
			.Function("GetRightVector", BINDING_FUNCTION(&FQuat::GetRightVector))
			.Function("GetUpVector", BINDING_FUNCTION(&FQuat::GetUpVector))
			.Function("Vector", BINDING_FUNCTION(&FQuat::Vector))
			.Function("Rotator", BINDING_FUNCTION(&FQuat::Rotator))
			.Function("ToMatrix", BINDING_OVERLOAD(FMatrix(FQuat::*)()const, &FQuat::ToMatrix))
			.Function("ToMatrix", BINDING_OVERLOAD(void(FQuat::*)(FMatrix&)const, &FQuat::ToMatrix),
			          {"Mat"})
			.Function("GetRotationAxis", BINDING_FUNCTION(&FQuat::GetRotationAxis))
			.Function("AngularDistance", BINDING_FUNCTION(&FQuat::AngularDistance),
			          {"Q"})
			.Function("ContainsNaN", BINDING_FUNCTION(&FQuat::ContainsNaN))
			.Function("ToString", BINDING_FUNCTION(&FQuat::ToString),
			          {}, EFunctionInteract::New)
			.Function("InitFromString", BINDING_FUNCTION(&FQuat::InitFromString),
			          {"InSourceString"})
			.Function("FindBetween", BINDING_FUNCTION(&FQuat::FindBetween),
			          {"Vector1", "Vector2"})
			.Function("FindBetweenNormals", BINDING_FUNCTION(&FQuat::FindBetweenNormals),
			          {"Normal1", "Normal2"})
			.Function("FindBetweenVectors", BINDING_FUNCTION(&FQuat::FindBetweenVectors),
			          {"Vector1", "Vector2"})
			.Function("Error", BINDING_FUNCTION(&FQuat::Error),
			          {"Q1", "Q2"})
			.Function("ErrorAutoNormalize", BINDING_FUNCTION(&FQuat::ErrorAutoNormalize),
			          {"A", "B"})
			.Function("FastLerp", BINDING_FUNCTION(&FQuat::FastLerp),
			          {"A", "B", "Alpha"})
			.Function("FastBilerp", BINDING_FUNCTION(&FQuat::FastBilerp),
			          {"P00", "P10", "P01", "P11", "FracX", "FracY"})
			.Function("Slerp_NotNormalized", BINDING_FUNCTION(&FQuat::Slerp_NotNormalized),
			          {"Quat1", "Quat2", "Slerp"})
			.Function("Slerp", BINDING_FUNCTION(&FQuat::Slerp),
			          {"Quat1", "Quat2", "Slerp"})
			.Function("SlerpFullPath_NotNormalized", BINDING_FUNCTION(&FQuat::SlerpFullPath_NotNormalized),
			          {"quat1", "quat2", "Alpha"})
			.Function("SlerpFullPath", BINDING_FUNCTION(&FQuat::SlerpFullPath),
			          {"quat1", "quat2", "Alpha"})
			.Function("Squad", BINDING_FUNCTION(&FQuat::Squad),
			          {"quat1", "tang1", "quat2", "tang2", "Alpha"})
			.Function("SquadFullPath", BINDING_FUNCTION(&FQuat::SquadFullPath),
			          {"quat1", "tang1", "quat2", "tang2", "Alpha"})
			.Function("CalcTangents", BINDING_FUNCTION(&FQuat::CalcTangents),
			          {"PrevP", "P", "NextP", "Tension", "OutTan"})
			.Register();
	}
};

static FRegisterQuat RegisterQuat;
