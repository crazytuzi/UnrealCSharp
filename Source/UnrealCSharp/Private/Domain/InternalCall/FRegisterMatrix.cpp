#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterMatrix
{
	static FMatrix MultipliesImplementation(const FMatrix& In, const FMatrix::FReal Other)
	{
		return In * Other;
	}

	FRegisterMatrix()
	{
		TReflectionClassBuilder<FMatrix>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FMatrix, EForceInit))
			.Constructor(BINDING_CONSTRUCTOR(FMatrix, FPlane, FPlane, FPlane, FPlane),
			             {"InX", "InY", "InZ", "InW"})
			.Constructor(BINDING_CONSTRUCTOR(FMatrix, FVector, FVector, FVector, FVector),
			             {"InX", "InY", "InZ", "InW"})
			.Multiplies()
			.Plus()
			.Property("Identity", BINDING_PROPERTY(&FMatrix::Identity))
			.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
			.Function("SetIdentity", BINDING_FUNCTION(&FMatrix::SetIdentity))
			.Function("Equals", BINDING_FUNCTION(&FMatrix::Equals),
			          {"Other", "Tolerance"})
			.Function("TransformFVector4", BINDING_FUNCTION(&FMatrix::TransformFVector4),
			          {"P"})
			.Function("TransformPosition", BINDING_FUNCTION(&FMatrix::TransformPosition),
			          {"V"})
			.Function("InverseTransformPosition", BINDING_FUNCTION(&FMatrix::InverseTransformPosition),
			          {"V"})
			.Function("TransformVector", BINDING_FUNCTION(&FMatrix::TransformVector),
			          {"V"})
			.Function("InverseTransformVector", BINDING_FUNCTION(&FMatrix::InverseTransformVector),
			          {"V"})
			.Function("GetTransposed", BINDING_FUNCTION(&FMatrix::GetTransposed))
			.Function("Determinant", BINDING_FUNCTION(&FMatrix::Determinant))
			.Function("RotDeterminant", BINDING_FUNCTION(&FMatrix::RotDeterminant))
			.Function("InverseFast", BINDING_FUNCTION(&FMatrix::InverseFast))
			.Function("Inverse", BINDING_FUNCTION(&FMatrix::Inverse))
			.Function("TransposeAdjoint", BINDING_FUNCTION(&FMatrix::TransposeAdjoint))
			.Function("RemoveScaling", BINDING_FUNCTION(&FMatrix::RemoveScaling),
			          {"Tolerance"})
			.Function("GetMatrixWithoutScale", BINDING_FUNCTION(&FMatrix::GetMatrixWithoutScale),
			          {"Tolerance"})
			.Function("ExtractScaling", BINDING_FUNCTION(&FMatrix::ExtractScaling),
			          {"Tolerance"})
			.Function("GetScaleVector", BINDING_FUNCTION(&FMatrix::GetScaleVector),
			          {"Tolerance"})
			.Function("RemoveTranslation", BINDING_FUNCTION(&FMatrix::RemoveTranslation))
			.Function("ConcatTranslation", BINDING_FUNCTION(&FMatrix::ConcatTranslation))
			.Function("ContainsNaN", BINDING_FUNCTION(&FMatrix::ContainsNaN))
			.Function("ScaleTranslation", BINDING_FUNCTION(&FMatrix::ScaleTranslation),
			          {"InScale3D"})
			.Function("GetMinimumAxisScale", BINDING_FUNCTION(&FMatrix::GetMinimumAxisScale))
			.Function("GetMaximumAxisScale", BINDING_FUNCTION(&FMatrix::GetMaximumAxisScale))
			.Function("GetOrigin", BINDING_FUNCTION(&FMatrix::GetOrigin))
			.Function("GetScaledAxis", BINDING_FUNCTION(&FMatrix::GetScaledAxis),
			          {"Axis"})
			.Function("GetScaledAxes", BINDING_FUNCTION(&FMatrix::GetScaledAxes),
			          {"X", "Y", "Z"})
			.Function("GetUnitAxis", BINDING_FUNCTION(&FMatrix::GetUnitAxis),
			          {"Axis"})
			.Function("GetUnitAxes", BINDING_FUNCTION(&FMatrix::GetUnitAxes),
			          {"X", "Y", "Z"})
			.Function("SetAxis", BINDING_FUNCTION(&FMatrix::SetAxis),
			          {"i", "Axis"})
			.Function("SetOrigin", BINDING_FUNCTION(&FMatrix::SetOrigin),
			          {"NewOrigin"})
			.Function("SetAxes", BINDING_FUNCTION(&FMatrix::SetAxes),
			          {"Axis0", "Axis1", "Axis2", "Origin"})
			.Function("GetColumn", BINDING_FUNCTION(&FMatrix::GetColumn),
			          {"i"})
			.Function("GetColumn", BINDING_FUNCTION(&FMatrix::SetColumn),
			          {"i", "Value"})
			.Function("Rotator", BINDING_FUNCTION(&FMatrix::Rotator))
			.Function("ToQuat", BINDING_FUNCTION(&FMatrix::ToQuat))
			.Function("GetFrustumNearPlane", BINDING_FUNCTION(&FMatrix::GetFrustumNearPlane),
			          {"OuTPln"})
			.Function("GetFrustumFarPlane", BINDING_FUNCTION(&FMatrix::GetFrustumFarPlane),
			          {"OuTPln"})
			.Function("GetFrustumLeftPlane", BINDING_FUNCTION(&FMatrix::GetFrustumLeftPlane),
			          {"OuTPln"})
			.Function("GetFrustumRightPlane", BINDING_FUNCTION(&FMatrix::GetFrustumRightPlane),
			          {"OuTPln"})
			.Function("GetFrustumTopPlane", BINDING_FUNCTION(&FMatrix::GetFrustumTopPlane),
			          {"OuTPln"})
			.Function("GetFrustumBottomPlane", BINDING_FUNCTION(&FMatrix::GetFrustumBottomPlane),
			          {"OuTPln"})
			.Function("Mirror", BINDING_FUNCTION(&FMatrix::Mirror),
			          {"MirrorAxis", "FlipAxis"})
			.Function("ToString", BINDING_FUNCTION(&FMatrix::ToString))
			.Function("DebugPrint", BINDING_FUNCTION(&FMatrix::DebugPrint))
			.Function("ComputeHash", BINDING_FUNCTION(&FMatrix::ComputeHash))
			.Register();
	}
};

static FRegisterMatrix RegisterMatrix;
