#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "FRegisterForceInit.h"

namespace
{
	struct FRegisterMatrix
	{
		static FMatrix MultipliesImplementation(const FMatrix& In, const FMatrix::FReal Other)
		{
			return &In != nullptr ? In * Other : decltype(In * Other)();
		}

		FRegisterMatrix()
		{
			TBindingClassBuilder<FMatrix>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FMatrix, EForceInit))
				.Constructor(BINDING_CONSTRUCTOR(FMatrix, FPlane, FPlane, FPlane, FPlane),
				             TArray<FString>{"InX", "InY", "InZ", "InW"})
				.Constructor(BINDING_CONSTRUCTOR(FMatrix, FVector, FVector, FVector, FVector),
				             TArray<FString>{"InX", "InY", "InZ", "InW"})
				.Multiplies()
				.Plus()
				.Property("Identity", BINDING_READONLY_PROPERTY(&FMatrix::Identity))
				.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
				.Function("SetIdentity", BINDING_FUNCTION(&FMatrix::SetIdentity))
				.Function("Equals", BINDING_FUNCTION(&FMatrix::Equals,
				                                     TArray<FString>{"Other", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("TransformFVector4", BINDING_FUNCTION(&FMatrix::TransformFVector4,
				                                                TArray<FString>{"P"}))
				.Function("TransformPosition", BINDING_FUNCTION(&FMatrix::TransformPosition,
				                                                TArray<FString>{"V"}))
				.Function("InverseTransformPosition", BINDING_FUNCTION(&FMatrix::InverseTransformPosition,
				                                                       TArray<FString>{"V"}))
				.Function("TransformVector", BINDING_FUNCTION(&FMatrix::TransformVector,
				                                              TArray<FString>{"V"}))
				.Function("InverseTransformVector", BINDING_FUNCTION(&FMatrix::InverseTransformVector,
				                                                     TArray<FString>{"V"}))
				.Function("GetTransposed", BINDING_FUNCTION(&FMatrix::GetTransposed))
				.Function("Determinant", BINDING_FUNCTION(&FMatrix::Determinant))
				.Function("RotDeterminant", BINDING_FUNCTION(&FMatrix::RotDeterminant))
				.Function("InverseFast", BINDING_FUNCTION(&FMatrix::InverseFast))
				.Function("Inverse", BINDING_FUNCTION(&FMatrix::Inverse))
				.Function("TransposeAdjoint", BINDING_FUNCTION(&FMatrix::TransposeAdjoint))
				.Function("RemoveScaling", BINDING_FUNCTION(&FMatrix::RemoveScaling,
				                                            TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("GetMatrixWithoutScale", BINDING_FUNCTION(&FMatrix::GetMatrixWithoutScale,
				                                                    TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("ExtractScaling", BINDING_FUNCTION(&FMatrix::ExtractScaling,
				                                             TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("GetScaleVector", BINDING_FUNCTION(&FMatrix::GetScaleVector,
				                                             TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("RemoveTranslation", BINDING_FUNCTION(&FMatrix::RemoveTranslation))
				.Function("ConcatTranslation", BINDING_FUNCTION(&FMatrix::ConcatTranslation))
				.Function("ContainsNaN", BINDING_FUNCTION(&FMatrix::ContainsNaN))
				.Function("ScaleTranslation", BINDING_FUNCTION(&FMatrix::ScaleTranslation,
				                                               TArray<FString>{"InScale3D"}))
				.Function("GetMinimumAxisScale", BINDING_FUNCTION(&FMatrix::GetMinimumAxisScale))
				.Function("GetMaximumAxisScale", BINDING_FUNCTION(&FMatrix::GetMaximumAxisScale))
				.Function("GetOrigin", BINDING_FUNCTION(&FMatrix::GetOrigin))
				.Function("GetScaledAxis", BINDING_FUNCTION(&FMatrix::GetScaledAxis,
				                                            TArray<FString>{"Axis"}))
				.Function("GetScaledAxes", BINDING_FUNCTION(&FMatrix::GetScaledAxes,
				                                            TArray<FString>{"X", "Y", "Z"}))
				.Function("GetUnitAxis", BINDING_FUNCTION(&FMatrix::GetUnitAxis,
				                                          TArray<FString>{"Axis"}))
				.Function("GetUnitAxes", BINDING_FUNCTION(&FMatrix::GetUnitAxes,
				                                          TArray<FString>{"X", "Y", "Z"}))
				.Function("SetAxis", BINDING_FUNCTION(&FMatrix::SetAxis,
				                                      TArray<FString>{"i", "Axis"}))
				.Function("SetOrigin", BINDING_FUNCTION(&FMatrix::SetOrigin,
				                                        TArray<FString>{"NewOrigin"}))
				.Function("SetAxes", BINDING_FUNCTION(&FMatrix::SetAxes,
				                                      TArray<FString>{"Axis0", "Axis1", "Axis2", "Origin"}))
				.Function("GetColumn", BINDING_FUNCTION(&FMatrix::GetColumn,
				                                        TArray<FString>{"i"}))
				.Function("GetColumn", BINDING_FUNCTION(&FMatrix::SetColumn,
				                                        TArray<FString>{"i", "Value"}))
				.Function("Rotator", BINDING_FUNCTION(&FMatrix::Rotator))
				.Function("ToQuat", BINDING_FUNCTION(&FMatrix::ToQuat))
				.Function("GetFrustumNearPlane", BINDING_FUNCTION(&FMatrix::GetFrustumNearPlane,
				                                                  TArray<FString>{"OuTPln"}))
				.Function("GetFrustumFarPlane", BINDING_FUNCTION(&FMatrix::GetFrustumFarPlane,
				                                                 TArray<FString>{"OuTPln"}))
				.Function("GetFrustumLeftPlane", BINDING_FUNCTION(&FMatrix::GetFrustumLeftPlane,
				                                                  TArray<FString>{"OuTPln"}))
				.Function("GetFrustumRightPlane", BINDING_FUNCTION(&FMatrix::GetFrustumRightPlane,
				                                                   TArray<FString>{"OuTPln"}))
				.Function("GetFrustumTopPlane", BINDING_FUNCTION(&FMatrix::GetFrustumTopPlane,
				                                                 TArray<FString>{"OuTPln"}))
				.Function("GetFrustumBottomPlane", BINDING_FUNCTION(&FMatrix::GetFrustumBottomPlane,
				                                                    TArray<FString>{"OuTPln"}))
				.Function("Mirror", BINDING_FUNCTION(&FMatrix::Mirror,
				                                     TArray<FString>{"MirrorAxis", "FlipAxis"}))
				.Function("ToString", BINDING_FUNCTION(&FMatrix::ToString,
				                                       EFunctionInteract::New))
				.Function("DebugPrint", BINDING_FUNCTION(&FMatrix::DebugPrint))
				.Function("ComputeHash", BINDING_FUNCTION(&FMatrix::ComputeHash));
		}
	};

	[[maybe_unused]] FRegisterMatrix RegisterMatrix;
}
