#include "Domain/InternalCall/FTransformImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterTransform
{
	FRegisterTransform()
	{
		TReflectionClassBuilder<FTransform>(NAMESPACE_LIBRARY)
			.Function("DebugPrint", FTransformImplementation::Transform_DebugPrintImplementation)
			.Function("ToHumanReadableString", FTransformImplementation::Transform_ToHumanReadableStringImplementation)
			.Function("ToString", FTransformImplementation::Transform_ToStringImplementation)
			.Function("InitFromString", FTransformImplementation::Transform_InitFromStringImplementation)
			.Function("ToMatrixWithScale", FTransformImplementation::Transform_ToMatrixWithScaleImplementation)
			.Function("ToInverseMatrixWithScale",
			          FTransformImplementation::Transform_ToInverseMatrixWithScaleImplementation)
			.Function("Inverse", FTransformImplementation::Transform_InverseImplementation)
			.Function("ToMatrixNoScale", FTransformImplementation::Transform_ToMatrixNoScaleImplementation)
			.Function("Blend", FTransformImplementation::Transform_BlendImplementation)
			.Function("BlendWith", FTransformImplementation::Transform_BlendWithImplementation)
			.Function("Add", FTransformImplementation::Transform_AddImplementation)
			.Function("Multiply", FTransformImplementation::Transform_MultiplyImplementation)
			.Function("MultiplyQuat", FTransformImplementation::Transform_MultiplyQuatImplementation)
			.Function("AnyHasNegativeScale", FTransformImplementation::Transform_AnyHasNegativeScaleImplementation)
			.Function("ScaleTranslationVector",
			          FTransformImplementation::Transform_ScaleTranslationVectorImplementation)
			.Function("ScaleTranslationScale", FTransformImplementation::Transform_ScaleTranslationScaleImplementation)
			.Function("RemoveScaling", FTransformImplementation::Transform_RemoveScalingImplementation)
			.Function("GetMaximumAxisScale", FTransformImplementation::Transform_GetMaximumAxisScaleImplementation)
			.Function("GetMinimumAxisScale", FTransformImplementation::Transform_GetMinimumAxisScaleImplementation)
			.Function("GetRelativeTransform", FTransformImplementation::Transform_GetRelativeTransformImplementation)
			.Function("GetRelativeTransformReverse",
			          FTransformImplementation::Transform_GetRelativeTransformReverseImplementation)
			.Function("SetToRelativeTransform",
			          FTransformImplementation::Transform_SetToRelativeTransformImplementation)
			.Function("TransformFVector4", FTransformImplementation::Transform_TransformFVector4Implementation)
			.Function("TransformFVector4NoScale",
			          FTransformImplementation::Transform_TransformFVector4NoScaleImplementation)
			.Function("TransformPosition", FTransformImplementation::Transform_TransformPositionImplementation)
			.Function("TransformPositionNoScale",
			          FTransformImplementation::Transform_TransformPositionNoScaleImplementation)
			.Function("InverseTransformPositionNoScale",
			          FTransformImplementation::Transform_InverseTransformPositionNoScaleImplementation)
			.Function("TransformVector", FTransformImplementation::Transform_TransformVectorImplementation)
			.Function("TransformVectorNoScale",
			          FTransformImplementation::Transform_TransformVectorNoScaleImplementation)
			.Function("InverseTransformVector",
			          FTransformImplementation::Transform_InverseTransformVectorImplementation)
			.Function("InverseTransformVectorNoScale",
			          FTransformImplementation::Transform_InverseTransformVectorNoScaleImplementation)
			.Function("TransformRotation", FTransformImplementation::Transform_TransformRotationImplementation)
			.Function("InverseTransformRotation",
			          FTransformImplementation::Transform_InverseTransformRotationImplementation)
			.Function("GetScaledScale", FTransformImplementation::Transform_GetScaledScaleImplementation)
			.Function("GetScaledVector", FTransformImplementation::Transform_GetScaledVectorImplementation)
			.Function("GetSafeScaleReciprocal",
			          FTransformImplementation::Transform_GetSafeScaleReciprocalImplementation)
			.Function("GetLocation", FTransformImplementation::Transform_GetLocationImplementation)
			.Function("Rotator", FTransformImplementation::Transform_RotatorImplementation)
			.Function("GetDeterminant", FTransformImplementation::Transform_GetDeterminantImplementation)
			.Function("SetLocation", FTransformImplementation::Transform_SetLocationImplementation)
			.Function("ContainsNaN", FTransformImplementation::Transform_ContainsNaNImplementation)
			.Function("IsValid", FTransformImplementation::Transform_IsValidImplementation)
			.Function("AreRotationsEqual", FTransformImplementation::Transform_AreRotationsEqualImplementation)
			.Function("AreTranslationsEqual", FTransformImplementation::Transform_AreTranslationsEqualImplementation)
			.Function("AreScale3DsEqual", FTransformImplementation::Transform_AreScale3DsEqualImplementation)
			.Function("RotationEquals", FTransformImplementation::Transform_RotationEqualsImplementation)
			.Function("TranslationEquals", FTransformImplementation::Transform_TranslationEqualsImplementation)
			.Function("Scale3DEquals", FTransformImplementation::Transform_Scale3DEqualsImplementation)
			.Function("Equals", FTransformImplementation::Transform_EqualsImplementation)
			.Function("Identical", FTransformImplementation::Transform_IdenticalImplementation)
			.Function("EqualsNoScale", FTransformImplementation::Transform_EqualsNoScaleImplementation)
			.Function("StaticMultiply", FTransformImplementation::Transform_StaticMultiplyImplementation)
			.Function("SetComponents", FTransformImplementation::Transform_SetComponentsImplementation)
			.Function("SetIdentity", FTransformImplementation::Transform_SetIdentityImplementation)
			.Function("MultiplyScale3D", FTransformImplementation::Transform_MultiplyScale3DImplementation)
			.Function("SetTranslation", FTransformImplementation::Transform_SetTranslationImplementation)
			.Function("CopyTranslation", FTransformImplementation::Transform_CopyTranslationImplementation)
			.Function("ConcatenateRotation", FTransformImplementation::Transform_ConcatenateRotationImplementation)
			.Function("AddToTranslation", FTransformImplementation::Transform_AddToTranslationImplementation)
			.Function("AddTranslations", FTransformImplementation::Transform_AddTranslationsImplementation)
			.Function("SubtractTranslations", FTransformImplementation::Transform_SubtractTranslationsImplementation)
			.Function("SetRotation", FTransformImplementation::Transform_SetRotationImplementation)
			.Function("CopyRotation", FTransformImplementation::Transform_CopyRotationImplementation)
			.Function("SetScale3D", FTransformImplementation::Transform_SetScale3DImplementation)
			.Function("CopyScale3D", FTransformImplementation::Transform_CopyScale3DImplementation)
			.Function("SetTranslationAndScale3D",
			          FTransformImplementation::Transform_SetTranslationAndScale3DImplementation)
			.Function("Accumulate", FTransformImplementation::Transform_AccumulateImplementation)
			.Function("NormalizeRotation", FTransformImplementation::Transform_NormalizeRotationImplementation)
			.Function("IsRotationNormalized", FTransformImplementation::Transform_IsRotationNormalizedImplementation)
			.Function("GetRotation", FTransformImplementation::Transform_GetRotationImplementation)
			.Function("GetTranslation", FTransformImplementation::Transform_GetTranslationImplementation)
			.Function("GetScale3D", FTransformImplementation::Transform_GetScale3DImplementation)
			.Function("CopyRotationPart", FTransformImplementation::Transform_CopyRotationPartImplementation)
			.Function("CopyTranslationAndScale3D",
			          FTransformImplementation::Transform_CopyTranslationAndScale3DImplementation)
			.Function("SetFromMatrix", FTransformImplementation::Transform_SetFromMatrixImplementation)
			.Register();
	}
};

static FRegisterTransform RegisterTransform;

void FTransformImplementation::Transform_DebugPrintImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		Transform->DebugPrint();
	}
}

void FTransformImplementation::Transform_ToHumanReadableStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		const auto ResultString = Transform->ToHumanReadableString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FTransformImplementation::Transform_ToStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		const auto ResultString = Transform->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FTransformImplementation::Transform_InitFromStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InSourceString)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr && InSourceString != nullptr)
	{
		return Transform->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

void FTransformImplementation::Transform_ToMatrixWithScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Transform->ToMatrixWithScale());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_ToInverseMatrixWithScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Transform->ToInverseMatrixWithScale());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_InverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->Inverse());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_ToMatrixNoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->ToMatrixNoScale());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_BlendImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             const FGarbageCollectionHandle Atom1,
                                                             const FGarbageCollectionHandle Atom2, const LwcType Alpha)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformAtom1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Atom1);

	const auto TransformAtom2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Atom2);

	if (Transform != nullptr && TransformAtom1 != nullptr && TransformAtom2 != nullptr)
	{
		Transform->Blend(*TransformAtom1, *TransformAtom2, Alpha);
	}
}

void FTransformImplementation::Transform_BlendWithImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* OtherAtom, const LwcType Alpha)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOtherAtom = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(OtherAtom);

	if (Transform != nullptr && TransformOtherAtom)
	{
		Transform->BlendWith(*TransformOtherAtom, Alpha);
	}
}

void FTransformImplementation::Transform_AddImplementation(const FGarbageCollectionHandle A,
                                                           const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(TransformA->operator+(*TransformB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_MultiplyImplementation(const FGarbageCollectionHandle A,
                                                                const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(TransformA->operator*(*TransformB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_MultiplyQuatImplementation(const FGarbageCollectionHandle A,
                                                                    const MonoObject* B, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->operator*(*Quat));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

bool FTransformImplementation::Transform_AnyHasNegativeScaleImplementation(
	const MonoObject* InScale3D, const MonoObject* InOtherScale3D)
{
	const auto VectorInScale3D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InScale3D);

	const auto VectorInOtherScale3D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InOtherScale3D);

	if (VectorInScale3D != nullptr && VectorInOtherScale3D != nullptr)
	{
		return FTransform::AnyHasNegativeScale(*VectorInScale3D, *VectorInOtherScale3D);
	}

	return false;
}

void FTransformImplementation::Transform_ScaleTranslationVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* InScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InScale3D);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->ScaleTranslation(*Vector);
	}
}

void FTransformImplementation::Transform_ScaleTranslationScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Scale)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		Transform->ScaleTranslation(Scale);
	}
}

void FTransformImplementation::Transform_RemoveScalingImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		Transform->RemoveScaling(Tolerance);
	}
}

FTransformImplementation::LwcType FTransformImplementation::Transform_GetMaximumAxisScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		return Transform->GetMaximumAxisScale();
	}

	return 0.f;
}

FTransformImplementation::LwcType FTransformImplementation::Transform_GetMinimumAxisScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		return Transform->GetMinimumAxisScale();
	}

	return 0.f;
}

void FTransformImplementation::Transform_GetRelativeTransformImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->GetRelativeTransform(*TransformOther));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetRelativeTransformReverseImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->GetRelativeTransformReverse(*TransformOther));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_SetToRelativeTransformImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* ParentTransform)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformParentTransform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		ParentTransform);

	if (Transform != nullptr && TransformParentTransform != nullptr)
	{
		Transform->SetToRelativeTransform(*TransformParentTransform);
	}
}

void FTransformImplementation::Transform_TransformFVector4Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(V);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = new FVector4(Transform->TransformFVector4(*Vector4));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector4>::Get(), OutVector4,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_TransformFVector4NoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(V);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = new FVector4(Transform->TransformFVector4NoScale(*Vector4));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector4>::Get(), OutVector4,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_TransformPositionImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->TransformPosition(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_TransformPositionNoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->TransformPositionNoScale(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_InverseTransformPositionNoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->InverseTransformPositionNoScale(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_TransformVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->TransformVector(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_TransformVectorNoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->TransformVectorNoScale(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_InverseTransformVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->InverseTransformVector(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_InverseTransformVectorNoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->InverseTransformVectorNoScale(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_TransformRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Q, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = new FQuat(Transform->TransformRotation(*Quat));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FQuat>::Get(), OutQuat,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_InverseTransformRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Q, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = new FQuat(Transform->InverseTransformRotation(*Quat));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FQuat>::Get(), OutQuat,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetScaledScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Scale, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->GetScaled(Scale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetScaledVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Scale, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto VectorScale = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Scale);

	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform(Transform->GetScaled(*VectorScale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetSafeScaleReciprocalImplementation(
	const MonoObject* InScale, const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InScale);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FTransform::GetSafeScaleReciprocal(*Vector, Tolerance));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetLocationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->GetLocation());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_RotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = new FRotator(Transform->Rotator());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FRotator>::Get(), OutRotator,
	                                                        NewMonoObject);
}

FTransformImplementation::LwcType FTransformImplementation::Transform_GetDeterminantImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		return Transform->GetDeterminant();
	}

	return 0.f;
}

void FTransformImplementation::Transform_SetLocationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Origin)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Origin);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->SetLocation(*Vector);
	}
}

bool FTransformImplementation::Transform_ContainsNaNImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		return Transform->ContainsNaN();
	}

	return false;
}

bool FTransformImplementation::Transform_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		return Transform->IsValid();
	}

	return false;
}

bool FTransformImplementation::Transform_AreRotationsEqualImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B, const LwcType Tolerance)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	if (TransformA != nullptr && TransformB != nullptr)
	{
		return FTransform::AreRotationsEqual(*TransformA, *TransformB, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_AreTranslationsEqualImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B, const LwcType Tolerance)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	if (TransformA != nullptr && TransformB != nullptr)
	{
		return FTransform::AreTranslationsEqual(*TransformA, *TransformB, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_AreScale3DsEqualImplementation(const FGarbageCollectionHandle A,
                                                                        const FGarbageCollectionHandle B,
                                                                        const LwcType Tolerance)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	if (TransformA != nullptr && TransformB != nullptr)
	{
		return FTransform::AreScale3DsEqual(*TransformA, *TransformB, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_RotationEqualsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, const LwcType Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->RotationEquals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_TranslationEqualsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, const LwcType Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->TranslationEquals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_Scale3DEqualsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, const LwcType Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->Scale3DEquals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_EqualsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const MonoObject* Other, const LwcType Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->Equals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_IdenticalImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, const uint32 PortFlags)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->Identical(TransformOther, PortFlags);
	}

	return false;
}

bool FTransformImplementation::Transform_EqualsNoScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, const LwcType Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->EqualsNoScale(*TransformOther, Tolerance);
	}

	return false;
}

void FTransformImplementation::Transform_StaticMultiplyImplementation(MonoObject** OutValue,
                                                                      const FGarbageCollectionHandle A,
                                                                      const FGarbageCollectionHandle B)
{
	const auto FoundMonoClass = TPropertyClass<FTransform, FTransform>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = new FTransform();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FTransform>::Get(), OutTransform,
	                                                        NewMonoObject);

	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	FTransform::Multiply(OutTransform, TransformA, TransformB);
}

void FTransformImplementation::Transform_SetComponentsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* InRotation,
	const MonoObject* InTranslation, const MonoObject* InScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto QuatInRotation = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InRotation);

	const auto VectorInTranslation = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InTranslation);

	const auto VectorInScale3D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InScale3D);

	if (Transform != nullptr && QuatInRotation != nullptr && VectorInTranslation != nullptr && VectorInScale3D !=
		nullptr)
	{
		Transform->SetComponents(*QuatInRotation, *VectorInTranslation, *VectorInScale3D);
	}
}

void FTransformImplementation::Transform_SetIdentityImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		Transform->SetIdentity();
	}
}

void FTransformImplementation::Transform_MultiplyScale3DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Scale3DMultiplier)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Scale3DMultiplier);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->MultiplyScale3D(*Vector);
	}
}

void FTransformImplementation::Transform_SetTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewTranslation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewTranslation);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->SetTranslation(*Vector);
	}
}

void FTransformImplementation::Transform_CopyTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		Transform->CopyTranslation(*TransformOther);
	}
}

void FTransformImplementation::Transform_ConcatenateRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* DeltaRotation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(DeltaRotation);

	if (Transform != nullptr && Quat != nullptr)
	{
		Transform->ConcatenateRotation(*Quat);
	}
}

void FTransformImplementation::Transform_AddToTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* DeltaTranslation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(DeltaTranslation);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->AddToTranslation(*Vector);
	}
}

void FTransformImplementation::Transform_AddTranslationsImplementation(const FGarbageCollectionHandle A,
                                                                       const FGarbageCollectionHandle B,
                                                                       MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FTransform::AddTranslations(*TransformA, *TransformB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_SubtractTranslationsImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FTransform::SubtractTranslations(*TransformA, *TransformB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_SetRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewRotation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewRotation);

	if (Transform != nullptr && Quat != nullptr)
	{
		Transform->SetRotation(*Quat);
	}
}

void FTransformImplementation::Transform_CopyRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		Transform->CopyRotation(*TransformOther);
	}
}

void FTransformImplementation::Transform_SetScale3DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewScale3D);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->SetScale3D(*Vector);
	}
}

void FTransformImplementation::Transform_CopyScale3DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		Transform->CopyScale3D(*TransformOther);
	}
}

void FTransformImplementation::Transform_SetTranslationAndScale3DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewTranslation,
	const MonoObject* NewScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto VectorNewTranslation = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		NewTranslation);

	const auto VectorNewScale3D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewScale3D);

	if (Transform != nullptr && VectorNewTranslation != nullptr && VectorNewScale3D != nullptr)
	{
		Transform->SetTranslationAndScale3D(*VectorNewTranslation, *VectorNewScale3D);
	}
}

void FTransformImplementation::Transform_AccumulateImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* SourceAtom)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformSourceAtom = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(SourceAtom);

	if (Transform != nullptr && TransformSourceAtom != nullptr)
	{
		Transform->Accumulate(*TransformSourceAtom);
	}
}

void FTransformImplementation::Transform_NormalizeRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		Transform->NormalizeRotation();
	}
}

bool FTransformImplementation::Transform_IsRotationNormalizedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	if (Transform != nullptr)
	{
		return Transform->IsRotationNormalized();
	}

	return false;
}

void FTransformImplementation::Transform_GetRotationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = new FQuat(Transform->GetRotation());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FQuat>::Get(), OutQuat,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->GetTranslation());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_GetScale3DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Transform->GetScale3D());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FTransformImplementation::Transform_CopyRotationPartImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* SrcBA)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformSrcBA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(SrcBA);

	if (Transform != nullptr && TransformSrcBA != nullptr)
	{
		Transform->CopyRotationPart(*TransformSrcBA);
	}
}

void FTransformImplementation::Transform_CopyTranslationAndScale3DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* SrcBA)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto TransformSrcBA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(SrcBA);

	if (Transform != nullptr && TransformSrcBA != nullptr)
	{
		Transform->CopyTranslationAndScale3D(*TransformSrcBA);
	}
}

void FTransformImplementation::Transform_SetFromMatrixImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* InMatrix)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		InGarbageCollectionHandle);

	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMatrix);

	if (Transform != nullptr && Matrix != nullptr)
	{
		Transform->SetFromMatrix(*Matrix);
	}
}
