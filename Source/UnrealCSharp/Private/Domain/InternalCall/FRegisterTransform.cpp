#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterTransform
{
	static FTransform MultipliesImplementation(const FTransform& In, const FQuat& Other)
	{
		return In * Other;
	}

	FRegisterTransform()
	{
		TBindingClassBuilder<FTransform>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FTransform, FVector),
			             {"InTranslation"})
			.Constructor(BINDING_CONSTRUCTOR(FTransform, FRotator),
			             {"InRotation"})
			.Constructor(BINDING_CONSTRUCTOR(FTransform, FQuat, FVector, FVector),
			             {"InRotation", "InTranslation", "InScale3D"})
			.Constructor(BINDING_CONSTRUCTOR(FTransform, FRotator, FVector, FVector),
			             {"InRotation", "InTranslation", "InScale3D"})
			.Constructor(BINDING_CONSTRUCTOR(FTransform, FMatrix),
			             {"InMatrix"})
			.Constructor(BINDING_CONSTRUCTOR(FTransform, FVector, FVector, FVector, FVector),
			             {"InX", "InY", "InZ", "InTranslation"})
			.Plus()
			.Multiplies()
			.Function("operator *", FUNCTION_MULTIPLIES, BINDING_FUNCTION(&MultipliesImplementation))
			.Property("Identity", BINDING_READONLY_PROPERTY(&FTransform::Identity))
			.Function("DebugPrint", BINDING_FUNCTION(&FTransform::DebugPrint))
			.Function("ToHumanReadableString", BINDING_FUNCTION(&FTransform::ToHumanReadableString))
			.Function("ToString", BINDING_FUNCTION(&FTransform::ToString),
			          {}, EFunctionInteract::New)
			.Function("InitFromString", BINDING_FUNCTION(&FTransform::InitFromString),
			          {"InSourceString"})
			.Function("ToMatrixWithScale", BINDING_FUNCTION(&FTransform::ToMatrixWithScale))
			.Function("ToInverseMatrixWithScale", BINDING_FUNCTION(&FTransform::ToInverseMatrixWithScale))
			.Function("Inverse", BINDING_FUNCTION(&FTransform::Inverse))
			.Function("ToMatrixNoScale", BINDING_FUNCTION(&FTransform::ToMatrixNoScale))
			.Function("Blend", BINDING_FUNCTION(&FTransform::Blend),
			          {"Atom1", "Atom2", "Alpha"})
			.Function("BlendWith", BINDING_FUNCTION(&FTransform::BlendWith),
			          {"OtherAtom", "Alpha"})
			.Function("AnyHasNegativeScale", BINDING_FUNCTION(&FTransform::AnyHasNegativeScale),
			          {"InScale3D", "InOtherScale3D"})
			.Function("ScaleTranslation",
			          BINDING_OVERLOAD(void(FTransform::*)(const FVector&), &FTransform::ScaleTranslation),
			          {"InScale3D"})
			.Function("ScaleTranslation",
			          BINDING_OVERLOAD(void(FTransform::*)(const FTransform::FReal&), &FTransform::ScaleTranslation),
			          {"Scale"})
			.Function("RemoveScaling", BINDING_FUNCTION(&FTransform::RemoveScaling),
			          {"Tolerance"})
			.Function("GetMaximumAxisScale", BINDING_FUNCTION(&FTransform::GetMaximumAxisScale))
			.Function("GetMinimumAxisScale", BINDING_FUNCTION(&FTransform::GetMinimumAxisScale))
			.Function("GetRelativeTransform", BINDING_FUNCTION(&FTransform::GetRelativeTransform),
			          {"Other"})
			.Function("GetRelativeTransformReverse", BINDING_FUNCTION(&FTransform::GetRelativeTransformReverse),
			          {"Other"})
			.Function("SetToRelativeTransform", BINDING_FUNCTION(&FTransform::SetToRelativeTransform),
			          {"ParentTransform"})
			.Function("TransformFVector4", BINDING_FUNCTION(&FTransform::TransformFVector4),
			          {"V"})
			.Function("TransformFVector4NoScale", BINDING_FUNCTION(&FTransform::TransformFVector4NoScale),
			          {"V"})
			.Function("TransformPosition", BINDING_FUNCTION(&FTransform::TransformPosition),
			          {"V"})
			.Function("TransformPositionNoScale", BINDING_FUNCTION(&FTransform::TransformPositionNoScale),
			          {"V"})
			.Function("InverseTransformPosition", BINDING_FUNCTION(&FTransform::InverseTransformPosition),
			          {"V"})
			.Function("InverseTransformPositionNoScale", BINDING_FUNCTION(&FTransform::InverseTransformPositionNoScale),
			          {"V"})
			.Function("TransformVector", BINDING_FUNCTION(&FTransform::TransformVector),
			          {"V"})
			.Function("TransformVectorNoScale", BINDING_FUNCTION(&FTransform::TransformVectorNoScale),
			          {"V"})
			.Function("InverseTransformVector", BINDING_FUNCTION(&FTransform::InverseTransformVector),
			          {"V"})
			.Function("InverseTransformVectorNoScale", BINDING_FUNCTION(&FTransform::InverseTransformVectorNoScale),
			          {"V"})
			.Function("TransformRotation", BINDING_FUNCTION(&FTransform::TransformRotation),
			          {"Q"})
			.Function("InverseTransformRotation", BINDING_FUNCTION(&FTransform::InverseTransformRotation),
			          {"Q"})
			.Function("GetScaled",
			          BINDING_OVERLOAD(FTransform(FTransform::*)(FTransform::FReal)const, &FTransform::GetScaled),
			          {"Scale"})
			.Function("GetScaled", BINDING_OVERLOAD(FTransform(FTransform::*)(FVector)const, &FTransform::GetScaled),
			          {"Scale"})
			.Function("GetScaledAxis", BINDING_FUNCTION(&FTransform::GetScaledAxis),
			          {"InAxis"})
			.Function("GetUnitAxis", BINDING_FUNCTION(&FTransform::GetUnitAxis),
			          {"InAxis"})
			.Function("Mirror", BINDING_FUNCTION(&FTransform::Mirror),
			          {"MirrorAxis", "FlipAxis"})
			.Function("GetSafeScaleReciprocal",
			          BINDING_OVERLOAD(FVector(*)(const FVector&, FTransform::FReal),
			                           &FTransform::GetSafeScaleReciprocal),
			          {"InScale", "Tolerance"})
			.Function("GetLocation", BINDING_FUNCTION(&FTransform::GetLocation))
			.Function("Rotator", BINDING_FUNCTION(&FTransform::Rotator))
			.Function("GetDeterminant", BINDING_FUNCTION(&FTransform::GetDeterminant))
			.Function("SetLocation", BINDING_FUNCTION(&FTransform::SetLocation),
			          {"Origin"})
			.Function("ContainsNaN", BINDING_FUNCTION(&FTransform::ContainsNaN))
			.Function("IsValid", BINDING_FUNCTION(&FTransform::IsValid))
			.Function("AreRotationsEqual", BINDING_FUNCTION(&FTransform::AreRotationsEqual),
			          {"A", "B", "Tolerance"})
			.Function("AreTranslationsEqual", BINDING_FUNCTION(&FTransform::AreTranslationsEqual),
			          {"A", "B", "Tolerance"})
			.Function("AreScale3DsEqual", BINDING_FUNCTION(&FTransform::AreScale3DsEqual),
			          {"A", "B", "Tolerance"})
			.Function("RotationEquals", BINDING_FUNCTION(&FTransform::RotationEquals),
			          {"Other", "Tolerance"})
			.Function("TranslationEquals", BINDING_FUNCTION(&FTransform::TranslationEquals),
			          {"Other", "Tolerance"})
			.Function("Scale3DEquals", BINDING_FUNCTION(&FTransform::Scale3DEquals),
			          {"Other", "Tolerance"})
			.Function("Equals", BINDING_FUNCTION(&FTransform::Equals),
			          {"Other", "Tolerance"})
			.Function("Identical", BINDING_FUNCTION(&FTransform::Identical),
			          {"Other", "PortFlags"})
			.Function("EqualsNoScale", BINDING_FUNCTION(&FTransform::EqualsNoScale),
			          {"Other", "Tolerance"})
			.Function("Multiply", BINDING_FUNCTION(&FTransform::Multiply),
			          {"OutTransform", "A", "B"})
			.Function("SetComponents", BINDING_FUNCTION(&FTransform::SetComponents),
			          {"InRotation", "InTranslation", "InScale3D"})
			.Function("SetIdentity", BINDING_FUNCTION(&FTransform::SetIdentity))
			.Function("SetIdentityZeroScale", BINDING_FUNCTION(&FTransform::SetIdentityZeroScale))
			.Function("MultiplyScale3D", BINDING_FUNCTION(&FTransform::MultiplyScale3D),
			          {"Scale3DMultiplier"})
			.Function("SetTranslation", BINDING_FUNCTION(&FTransform::SetTranslation),
			          {"NewTranslation"})
			.Function("CopyTranslation", BINDING_FUNCTION(&FTransform::CopyTranslation),
			          {"Other"})
			.Function("ConcatenateRotation", BINDING_FUNCTION(&FTransform::ConcatenateRotation),
			          {"DeltaRotation"})
			.Function("AddToTranslation", BINDING_FUNCTION(&FTransform::AddToTranslation),
			          {"DeltaTranslation"})
			.Function("AddTranslations", BINDING_FUNCTION(&FTransform::AddTranslations),
			          {"A", "B"})
			.Function("SubtractTranslations", BINDING_FUNCTION(&FTransform::SubtractTranslations),
			          {"A", "B"})
			.Function("SetRotation", BINDING_FUNCTION(&FTransform::SetRotation),
			          {"NewRotation"})
			.Function("CopyRotation", BINDING_FUNCTION(&FTransform::CopyRotation),
			          {"Other"})
			.Function("SetScale3D", BINDING_FUNCTION(&FTransform::SetScale3D),
			          {"NewScale3D"})
			.Function("CopyScale3D", BINDING_FUNCTION(&FTransform::CopyScale3D),
			          {"Other"})
			.Function("SetTranslationAndScale3D", BINDING_FUNCTION(&FTransform::SetTranslationAndScale3D),
			          {"NewTranslation", "NewScale3D"})
			.Function("Accumulate", BINDING_OVERLOAD(void(FTransform::*)(const FTransform&), &FTransform::Accumulate),
			          {"SourceAtom"})
			.Function("NormalizeRotation", BINDING_FUNCTION(&FTransform::NormalizeRotation))
			.Function("IsRotationNormalized", BINDING_FUNCTION(&FTransform::IsRotationNormalized))
			.Function("GetRotation", BINDING_FUNCTION(&FTransform::GetRotation))
			.Function("GetTranslation", BINDING_FUNCTION(&FTransform::GetTranslation))
			.Function("GetScale3D", BINDING_FUNCTION(&FTransform::GetScale3D))
			.Function("CopyRotationPart", BINDING_FUNCTION(&FTransform::CopyRotationPart),
			          {"SrcBA"})
			.Function("CopyTranslationAndScale3D", BINDING_FUNCTION(&FTransform::CopyTranslationAndScale3D),
			          {"SrcBA"})
			.Function("SetFromMatrix", BINDING_FUNCTION(&FTransform::SetFromMatrix),
			          {"InMatrix"})
			.Register();
	}
};

static FRegisterTransform RegisterTransform;
