#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterTransform
	{
		static FTransform MultipliesImplementation(const FTransform& In, const FQuat& Other)
		{
			return &In != nullptr && (&Other != nullptr) ? In * Other : decltype(In * Other)();
		}

		FRegisterTransform()
		{
			TBindingClassBuilder<FTransform>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FTransform, FVector),
				             TArray<FString>{"InTranslation"})
				.Constructor(BINDING_CONSTRUCTOR(FTransform, FRotator),
				             TArray<FString>{"InRotation"})
				.Constructor(BINDING_CONSTRUCTOR(FTransform, FQuat, FVector, FVector),
				             TArray<FString>{"InRotation", "InTranslation", "InScale3D"})
				.Constructor(BINDING_CONSTRUCTOR(FTransform, FRotator, FVector, FVector),
				             TArray<FString>{"InRotation", "InTranslation", "InScale3D"})
				.Constructor(BINDING_CONSTRUCTOR(FTransform, FMatrix),
				             TArray<FString>{"InMatrix"})
				.Constructor(BINDING_CONSTRUCTOR(FTransform, FVector, FVector, FVector, FVector),
				             TArray<FString>{"InX", "InY", "InZ", "InTranslation"})
				.Plus()
				.Multiplies()
				.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
				.Property("Identity", BINDING_READONLY_PROPERTY(&FTransform::Identity))
				.Function("DebugPrint", BINDING_FUNCTION(&FTransform::DebugPrint))
				.Function("ToHumanReadableString", BINDING_FUNCTION(&FTransform::ToHumanReadableString))
				.Function("ToString", BINDING_FUNCTION(&FTransform::ToString,
				                                       EFunctionInteract::New))
				.Function("InitFromString", BINDING_FUNCTION(&FTransform::InitFromString,
				                                             TArray<FString>{"InSourceString"}))
				.Function("ToMatrixWithScale", BINDING_FUNCTION(&FTransform::ToMatrixWithScale))
				.Function("ToInverseMatrixWithScale", BINDING_FUNCTION(&FTransform::ToInverseMatrixWithScale))
				.Function("Inverse", BINDING_FUNCTION(&FTransform::Inverse))
				.Function("ToMatrixNoScale", BINDING_FUNCTION(&FTransform::ToMatrixNoScale))
				.Function("Blend", BINDING_FUNCTION(&FTransform::Blend,
				                                    TArray<FString>{"Atom1", "Atom2", "Alpha"}))
				.Function("BlendWith", BINDING_FUNCTION(&FTransform::BlendWith,
				                                        TArray<FString>{"OtherAtom", "Alpha"}))
				.Function("AnyHasNegativeScale", BINDING_FUNCTION(&FTransform::AnyHasNegativeScale,
				                                                  TArray<FString>{"InScale3D", "InOtherScale3D"}))
				.Function("ScaleTranslation",
				          BINDING_OVERLOAD(void(FTransform::*)(const FVector&), &FTransform::ScaleTranslation,
				                           TArray<FString>{"InScale3D"}))
				.Function("ScaleTranslation",
				          BINDING_OVERLOAD(void(FTransform::*)(const FTransform::FReal&), &FTransform::ScaleTranslation,
				                           TArray<FString>{"Scale"}))
				.Function("RemoveScaling", BINDING_FUNCTION(&FTransform::RemoveScaling,
				                                            TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("GetMaximumAxisScale", BINDING_FUNCTION(&FTransform::GetMaximumAxisScale))
				.Function("GetMinimumAxisScale", BINDING_FUNCTION(&FTransform::GetMinimumAxisScale))
				.Function("GetRelativeTransform", BINDING_FUNCTION(&FTransform::GetRelativeTransform,
				                                                   TArray<FString>{"Other"}))
				.Function("GetRelativeTransformReverse", BINDING_FUNCTION(&FTransform::GetRelativeTransformReverse,
				                                                          TArray<FString>{"Other"}))
				.Function("SetToRelativeTransform", BINDING_FUNCTION(&FTransform::SetToRelativeTransform,
				                                                     TArray<FString>{"ParentTransform"}))
				.Function("TransformFVector4", BINDING_FUNCTION(&FTransform::TransformFVector4,
				                                                TArray<FString>{"V"}))
				.Function("TransformFVector4NoScale", BINDING_FUNCTION(&FTransform::TransformFVector4NoScale,
				                                                       TArray<FString>{"V"}))
				.Function("TransformPosition", BINDING_FUNCTION(&FTransform::TransformPosition,
				                                                TArray<FString>{"V"}))
				.Function("TransformPositionNoScale", BINDING_FUNCTION(&FTransform::TransformPositionNoScale,
				                                                       TArray<FString>{"V"}))
				.Function("InverseTransformPosition", BINDING_FUNCTION(&FTransform::InverseTransformPosition,
				                                                       TArray<FString>{"V"}))
				.Function("InverseTransformPositionNoScale", BINDING_FUNCTION(
					          &FTransform::InverseTransformPositionNoScale,
					          TArray<FString>{"V"}))
				.Function("TransformVector", BINDING_FUNCTION(&FTransform::TransformVector,
				                                              TArray<FString>{"V"}))
				.Function("TransformVectorNoScale", BINDING_FUNCTION(&FTransform::TransformVectorNoScale,
				                                                     TArray<FString>{"V"}))
				.Function("InverseTransformVector", BINDING_FUNCTION(&FTransform::InverseTransformVector,
				                                                     TArray<FString>{"V"}))
				.Function("InverseTransformVectorNoScale", BINDING_FUNCTION(&FTransform::InverseTransformVectorNoScale,
				                                                            TArray<FString>{"V"}))
				.Function("TransformRotation", BINDING_FUNCTION(&FTransform::TransformRotation,
				                                                TArray<FString>{"Q"}))
				.Function("InverseTransformRotation", BINDING_FUNCTION(&FTransform::InverseTransformRotation,
				                                                       TArray<FString>{"Q"}))
				.Function("GetScaled",
				          BINDING_OVERLOAD(FTransform(FTransform::*)(FTransform::FReal)const, &FTransform::GetScaled,
				                           TArray<FString>{"Scale"}))
				.Function("GetScaled", BINDING_OVERLOAD(FTransform(FTransform::*)(FVector)const, &FTransform::GetScaled,
				                                        TArray<FString>{"Scale"}))
				.Function("GetScaledAxis", BINDING_FUNCTION(&FTransform::GetScaledAxis,
				                                            TArray<FString>{"InAxis"}))
				.Function("GetUnitAxis", BINDING_FUNCTION(&FTransform::GetUnitAxis,
				                                          TArray<FString>{"InAxis"}))
				.Function("Mirror", BINDING_FUNCTION(&FTransform::Mirror,
				                                     TArray<FString>{"MirrorAxis", "FlipAxis"}))
				.Function("GetSafeScaleReciprocal",
				          BINDING_OVERLOAD(FVector(*)(const FVector&, FTransform::FReal),
				                           &FTransform::GetSafeScaleReciprocal,
				                           TArray<FString>{"InScale", "Tolerance"}, SMALL_NUMBER))
				.Function("GetLocation", BINDING_FUNCTION(&FTransform::GetLocation))
				.Function("Rotator", BINDING_FUNCTION(&FTransform::Rotator))
				.Function("GetDeterminant", BINDING_FUNCTION(&FTransform::GetDeterminant))
				.Function("SetLocation", BINDING_FUNCTION(&FTransform::SetLocation,
				                                          TArray<FString>{"Origin"}))
				.Function("ContainsNaN", BINDING_FUNCTION(&FTransform::ContainsNaN))
				.Function("IsValid", BINDING_FUNCTION(&FTransform::IsValid))
				.Function("AreRotationsEqual", BINDING_FUNCTION(&FTransform::AreRotationsEqual,
				                                                TArray<FString>{"A", "B", "Tolerance"},
				                                                KINDA_SMALL_NUMBER))
				.Function("AreTranslationsEqual", BINDING_FUNCTION(&FTransform::AreTranslationsEqual,
				                                                   TArray<FString>{"A", "B", "Tolerance"},
				                                                   KINDA_SMALL_NUMBER))
				.Function("AreScale3DsEqual", BINDING_FUNCTION(&FTransform::AreScale3DsEqual,
				                                               TArray<FString>{"A", "B", "Tolerance"},
				                                               KINDA_SMALL_NUMBER))
				.Function("RotationEquals", BINDING_FUNCTION(&FTransform::RotationEquals,
				                                             TArray<FString>{"Other", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("TranslationEquals", BINDING_FUNCTION(&FTransform::TranslationEquals,
				                                                TArray<FString>{"Other", "Tolerance"},
				                                                KINDA_SMALL_NUMBER))
				.Function("Scale3DEquals", BINDING_FUNCTION(&FTransform::Scale3DEquals,
				                                            TArray<FString>{"Other", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Equals", BINDING_FUNCTION(&FTransform::Equals,
				                                     TArray<FString>{"Other", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Identical", BINDING_FUNCTION(&FTransform::Identical,
				                                        TArray<FString>{"Other", "PortFlags"}))
				.Function("EqualsNoScale", BINDING_FUNCTION(&FTransform::EqualsNoScale,
				                                            TArray<FString>{"Other", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Multiply", BINDING_FUNCTION(&FTransform::Multiply,
				                                       TArray<FString>{"OutTransform", "A", "B"}))
				.Function("SetComponents", BINDING_FUNCTION(&FTransform::SetComponents,
				                                            TArray<FString>{"InRotation", "InTranslation",
				                                            "InScale3D"}))
				.Function("SetIdentity", BINDING_FUNCTION(&FTransform::SetIdentity))
				.Function("SetIdentityZeroScale", BINDING_FUNCTION(&FTransform::SetIdentityZeroScale))
				.Function("MultiplyScale3D", BINDING_FUNCTION(&FTransform::MultiplyScale3D,
				                                              TArray<FString>{"Scale3DMultiplier"}))
				.Function("SetTranslation", BINDING_FUNCTION(&FTransform::SetTranslation,
				                                             TArray<FString>{"NewTranslation"}))
				.Function("CopyTranslation", BINDING_FUNCTION(&FTransform::CopyTranslation,
				                                              TArray<FString>{"Other"}))
				.Function("ConcatenateRotation", BINDING_FUNCTION(&FTransform::ConcatenateRotation,
				                                                  TArray<FString>{"DeltaRotation"}))
				.Function("AddToTranslation", BINDING_FUNCTION(&FTransform::AddToTranslation,
				                                               TArray<FString>{"DeltaTranslation"}))
				.Function("AddTranslations", BINDING_FUNCTION(&FTransform::AddTranslations,
				                                              TArray<FString>{"A", "B"}))
				.Function("SubtractTranslations", BINDING_FUNCTION(&FTransform::SubtractTranslations,
				                                                   TArray<FString>{"A", "B"}))
				.Function("SetRotation", BINDING_FUNCTION(&FTransform::SetRotation,
				                                          TArray<FString>{"NewRotation"}))
				.Function("CopyRotation", BINDING_FUNCTION(&FTransform::CopyRotation,
				                                           TArray<FString>{"Other"}))
				.Function("SetScale3D", BINDING_FUNCTION(&FTransform::SetScale3D,
				                                         TArray<FString>{"NewScale3D"}))
				.Function("CopyScale3D", BINDING_FUNCTION(&FTransform::CopyScale3D,
				                                          TArray<FString>{"Other"}))
				.Function("SetTranslationAndScale3D", BINDING_FUNCTION(&FTransform::SetTranslationAndScale3D,
				                                                       TArray<FString>{"NewTranslation", "NewScale3D"}))
				.Function("Accumulate", BINDING_OVERLOAD(void(FTransform::*)(const FTransform&),
				                                         &FTransform::Accumulate,
				                                         TArray<FString>{"SourceAtom"}))
				.Function("NormalizeRotation", BINDING_FUNCTION(&FTransform::NormalizeRotation))
				.Function("IsRotationNormalized", BINDING_FUNCTION(&FTransform::IsRotationNormalized))
				.Function("GetRotation", BINDING_FUNCTION(&FTransform::GetRotation))
				.Function("GetTranslation", BINDING_FUNCTION(&FTransform::GetTranslation))
				.Function("GetScale3D", BINDING_FUNCTION(&FTransform::GetScale3D))
				.Function("CopyRotationPart", BINDING_FUNCTION(&FTransform::CopyRotationPart,
				                                               TArray<FString>{"SrcBA"}))
				.Function("CopyTranslationAndScale3D", BINDING_FUNCTION(&FTransform::CopyTranslationAndScale3D,
				                                                        TArray<FString>{"SrcBA"}))
				.Function("SetFromMatrix", BINDING_FUNCTION(&FTransform::SetFromMatrix,
				                                            TArray<FString>{"InMatrix"}));
		}
	};

	[[maybe_unused]] FRegisterTransform RegisterTransform;
}
