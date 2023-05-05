#include "Domain/InternalCall/FTransformImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

struct FRegisterTransform
{
	FRegisterTransform()
	{
		TScriptStructBuilder<FTransform>(NAMESPACE_LIBRARY)
			.Function("DebugPrint", static_cast<void*>(FTransformImplementation::Transform_DebugPrintImplementation))
			.Function("ToHumanReadableString",
			          static_cast<void*>(FTransformImplementation::Transform_ToHumanReadableStringImplementation))
			.Function("ToString", static_cast<void*>(FTransformImplementation::Transform_ToStringImplementation))
			.Function("InitFromString",
			          static_cast<void*>(FTransformImplementation::Transform_InitFromStringImplementation))
			.Function("ToMatrixWithScale",
			          static_cast<void*>(FTransformImplementation::Transform_ToMatrixWithScaleImplementation))
			.Function("ToInverseMatrixWithScale",
			          static_cast<void*>(FTransformImplementation::Transform_ToInverseMatrixWithScaleImplementation))
			.Function("Inverse", static_cast<void*>(FTransformImplementation::Transform_InverseImplementation))
			.Function("ToMatrixNoScale",
			          static_cast<void*>(FTransformImplementation::Transform_ToMatrixNoScaleImplementation))
			.Function("Blend", static_cast<void*>(FTransformImplementation::Transform_BlendImplementation))
			.Function("BlendWith", static_cast<void*>(FTransformImplementation::Transform_BlendWithImplementation))
			.Function("Add", static_cast<void*>(FTransformImplementation::Transform_AddImplementation))
			.Function("Multiply", static_cast<void*>(FTransformImplementation::Transform_MultiplyImplementation))
			.Function("MultiplyQuat",
			          static_cast<void*>(FTransformImplementation::Transform_MultiplyQuatImplementation))
			.Function("AnyHasNegativeScale",
			          static_cast<void*>(FTransformImplementation::Transform_AnyHasNegativeScaleImplementation))
			.Function("ScaleTranslationVector",
			          static_cast<void*>(FTransformImplementation::Transform_ScaleTranslationVectorImplementation))
			.Function("ScaleTranslationScale",
			          static_cast<void*>(FTransformImplementation::Transform_ScaleTranslationScaleImplementation))
			.Function("RemoveScaling",
			          static_cast<void*>(FTransformImplementation::Transform_RemoveScalingImplementation))
			.Function("GetMaximumAxisScale",
			          static_cast<void*>(FTransformImplementation::Transform_GetMaximumAxisScaleImplementation))
			.Function("GetMinimumAxisScale",
			          static_cast<void*>(FTransformImplementation::Transform_GetMinimumAxisScaleImplementation))
			.Function("GetRelativeTransform",
			          static_cast<void*>(FTransformImplementation::Transform_GetRelativeTransformImplementation))
			.Function("GetRelativeTransformReverse",
			          static_cast<void*>(FTransformImplementation::Transform_GetRelativeTransformReverseImplementation))
			.Function("SetToRelativeTransform",
			          static_cast<void*>(FTransformImplementation::Transform_SetToRelativeTransformImplementation))
			.Function("TransformFVector4",
			          static_cast<void*>(FTransformImplementation::Transform_TransformFVector4Implementation))
			.Function("TransformFVector4NoScale",
			          static_cast<void*>(FTransformImplementation::Transform_TransformFVector4NoScaleImplementation))
			.Function("TransformPosition",
			          static_cast<void*>(FTransformImplementation::Transform_TransformPositionImplementation))
			.Function("TransformPositionNoScale",
			          static_cast<void*>(FTransformImplementation::Transform_TransformPositionNoScaleImplementation))
			.Function("InverseTransformPositionNoScale",
			          static_cast<void*>(
				          FTransformImplementation::Transform_InverseTransformPositionNoScaleImplementation))
			.Function("TransformVector",
			          static_cast<void*>(FTransformImplementation::Transform_TransformVectorImplementation))
			.Function("TransformVectorNoScale",
			          static_cast<void*>(FTransformImplementation::Transform_TransformVectorNoScaleImplementation))
			.Function("InverseTransformVector",
			          static_cast<void*>(FTransformImplementation::Transform_InverseTransformVectorImplementation))
			.Function("InverseTransformVectorNoScale",
			          static_cast<void*>(
				          FTransformImplementation::Transform_InverseTransformVectorNoScaleImplementation))
			.Function("TransformRotation",
			          static_cast<void*>(FTransformImplementation::Transform_TransformRotationImplementation))
			.Function("InverseTransformRotation",
			          static_cast<void*>(FTransformImplementation::Transform_InverseTransformRotationImplementation))
			.Function("GetScaledScale",
			          static_cast<void*>(FTransformImplementation::Transform_GetScaledScaleImplementation))
			.Function("GetScaledVector",
			          static_cast<void*>(FTransformImplementation::Transform_GetScaledVectorImplementation))
			.Function("GetSafeScaleReciprocal",
			          static_cast<void*>(FTransformImplementation::Transform_GetSafeScaleReciprocalImplementation))
			.Function("GetLocation", static_cast<void*>(FTransformImplementation::Transform_GetLocationImplementation))
			.Function("Rotator", static_cast<void*>(FTransformImplementation::Transform_RotatorImplementation))
			.Function("GetDeterminant",
			          static_cast<void*>(FTransformImplementation::Transform_GetDeterminantImplementation))
			.Function("SetLocation", static_cast<void*>(FTransformImplementation::Transform_SetLocationImplementation))
			.Function("ContainsNaN", static_cast<void*>(FTransformImplementation::Transform_ContainsNaNImplementation))
			.Function("IsValid", static_cast<void*>(FTransformImplementation::Transform_IsValidImplementation))
			.Function("AreRotationsEqual",
			          static_cast<void*>(FTransformImplementation::Transform_AreRotationsEqualImplementation))
			.Function("AreTranslationsEqual",
			          static_cast<void*>(FTransformImplementation::Transform_AreTranslationsEqualImplementation))
			.Function("AreScale3DsEqual",
			          static_cast<void*>(FTransformImplementation::Transform_AreScale3DsEqualImplementation))
			.Function("RotationEquals",
			          static_cast<void*>(FTransformImplementation::Transform_RotationEqualsImplementation))
			.Function("TranslationEquals",
			          static_cast<void*>(FTransformImplementation::Transform_TranslationEqualsImplementation))
			.Function("Scale3DEquals",
			          static_cast<void*>(FTransformImplementation::Transform_Scale3DEqualsImplementation))
			.Function("Equals", static_cast<void*>(FTransformImplementation::Transform_EqualsImplementation))
			.Function("Identical", static_cast<void*>(FTransformImplementation::Transform_IdenticalImplementation))
			.Function("EqualsNoScale",
			          static_cast<void*>(FTransformImplementation::Transform_EqualsNoScaleImplementation))
			.Function("StaticMultiply",
			          static_cast<void*>(FTransformImplementation::Transform_StaticMultiplyImplementation))
			.Function("SetComponents",
			          static_cast<void*>(FTransformImplementation::Transform_SetComponentsImplementation))
			.Function("SetIdentity", static_cast<void*>(FTransformImplementation::Transform_SetIdentityImplementation))
			.Function("MultiplyScale3D",
			          static_cast<void*>(FTransformImplementation::Transform_MultiplyScale3DImplementation))
			.Function("SetTranslation",
			          static_cast<void*>(FTransformImplementation::Transform_SetTranslationImplementation))
			.Function("CopyTranslation",
			          static_cast<void*>(FTransformImplementation::Transform_CopyTranslationImplementation))
			.Function("ConcatenateRotation",
			          static_cast<void*>(FTransformImplementation::Transform_ConcatenateRotationImplementation))
			.Function("AddToTranslation",
			          static_cast<void*>(FTransformImplementation::Transform_AddToTranslationImplementation))
			.Function("AddTranslations",
			          static_cast<void*>(FTransformImplementation::Transform_AddTranslationsImplementation))
			.Function("SubtractTranslations",
			          static_cast<void*>(FTransformImplementation::Transform_SubtractTranslationsImplementation))
			.Function("SetRotation", static_cast<void*>(FTransformImplementation::Transform_SetRotationImplementation))
			.Function("CopyRotation",
			          static_cast<void*>(FTransformImplementation::Transform_CopyRotationImplementation))
			.Function("SetScale3D", static_cast<void*>(FTransformImplementation::Transform_SetScale3DImplementation))
			.Function("CopyScale3D", static_cast<void*>(FTransformImplementation::Transform_CopyScale3DImplementation))
			.Function("SetTranslationAndScale3D",
			          static_cast<void*>(FTransformImplementation::Transform_SetTranslationAndScale3DImplementation))
			.Function("Accumulate", static_cast<void*>(FTransformImplementation::Transform_AccumulateImplementation))
			.Function("NormalizeRotation",
			          static_cast<void*>(FTransformImplementation::Transform_NormalizeRotationImplementation))
			.Function("IsRotationNormalized",
			          static_cast<void*>(FTransformImplementation::Transform_IsRotationNormalizedImplementation))
			.Function("GetRotation", static_cast<void*>(FTransformImplementation::Transform_GetRotationImplementation))
			.Function("GetTranslation",
			          static_cast<void*>(FTransformImplementation::Transform_GetTranslationImplementation))
			.Function("GetScale3D", static_cast<void*>(FTransformImplementation::Transform_GetScale3DImplementation))
			.Function("CopyRotationPart",
			          static_cast<void*>(FTransformImplementation::Transform_CopyRotationPartImplementation))
			.Function("CopyTranslationAndScale3D",
			          static_cast<void*>(FTransformImplementation::Transform_CopyTranslationAndScale3DImplementation))
			.Function("SetFromMatrix",
			          static_cast<void*>(FTransformImplementation::Transform_SetFromMatrixImplementation))
			.Register();
	}
};

static FRegisterTransform RegisterTransform;

void FTransformImplementation::Transform_DebugPrintImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		Transform->DebugPrint();
	}
}

void FTransformImplementation::Transform_ToHumanReadableStringImplementation(const MonoObject* InMonoObject,
                                                                             MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		const auto ResultString = Transform->ToHumanReadableString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FTransformImplementation::Transform_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		const auto ResultString = Transform->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FTransformImplementation::Transform_InitFromStringImplementation(const MonoObject* InMonoObject,
                                                                      MonoObject* InSourceString)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr && InSourceString != nullptr)
	{
		return Transform->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

void FTransformImplementation::Transform_ToMatrixWithScaleImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Transform != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Transform->ToMatrixWithScale();
	}
}

void FTransformImplementation::Transform_ToInverseMatrixWithScaleImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Transform != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Transform->ToInverseMatrixWithScale();
	}
}

void FTransformImplementation::Transform_InverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (Transform != nullptr && OutTransform != nullptr)
	{
		*OutTransform = Transform->Inverse();
	}
}

void FTransformImplementation::Transform_ToMatrixNoScaleImplementation(const MonoObject* InMonoObject,
                                                                       MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Transform != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Transform->ToMatrixNoScale();
	}
}

void FTransformImplementation::Transform_BlendImplementation(const MonoObject* InMonoObject, const MonoObject* Atom1,
                                                             const MonoObject* Atom2, const float Alpha)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformAtom1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Atom1);

	const auto TransformAtom2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Atom2);

	if (Transform != nullptr && TransformAtom1 != nullptr && TransformAtom2 != nullptr)
	{
		Transform->Blend(*TransformAtom1, *TransformAtom2, Alpha);
	}
}

void FTransformImplementation::Transform_BlendWithImplementation(const MonoObject* InMonoObject,
                                                                 const MonoObject* OtherAtom, const float Alpha)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOtherAtom = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(OtherAtom);

	if (Transform != nullptr && TransformOtherAtom)
	{
		Transform->BlendWith(*TransformOtherAtom, Alpha);
	}
}

void FTransformImplementation::Transform_AddImplementation(const MonoObject* A, const MonoObject* B,
                                                           MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (TransformA != nullptr && TransformB != nullptr && OutTransform != nullptr)
	{
		*OutTransform = TransformA->operator+(*TransformB);
	}
}

void FTransformImplementation::Transform_MultiplyImplementation(const MonoObject* A, const MonoObject* B,
                                                                MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (TransformA != nullptr && TransformB != nullptr && OutTransform != nullptr)
	{
		*OutTransform = TransformA->operator*(*TransformB);
	}
}

void FTransformImplementation::Transform_MultiplyQuatImplementation(const MonoObject* A, const MonoObject* B,
                                                                    MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (Transform != nullptr && Quat != nullptr && OutTransform != nullptr)
	{
		*OutTransform = Transform->operator*(*Quat);
	}
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
	const MonoObject* InMonoObject, const MonoObject* InScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InScale3D);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->ScaleTranslation(*Vector);
	}
}

void FTransformImplementation::Transform_ScaleTranslationScaleImplementation(
	const MonoObject* InMonoObject, const float Scale)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		Transform->ScaleTranslation(Scale);
	}
}

void FTransformImplementation::Transform_RemoveScalingImplementation(const MonoObject* InMonoObject,
                                                                     const float Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		Transform->RemoveScaling(Tolerance);
	}
}

float FTransformImplementation::Transform_GetMaximumAxisScaleImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		return Transform->GetMaximumAxisScale();
	}

	return 0.f;
}

float FTransformImplementation::Transform_GetMinimumAxisScaleImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		return Transform->GetMinimumAxisScale();
	}

	return 0.f;
}

void FTransformImplementation::Transform_GetRelativeTransformImplementation(
	const MonoObject* InMonoObject, const MonoObject* Other, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (Transform != nullptr && TransformOther != nullptr && OutTransform != nullptr)
	{
		*OutTransform = Transform->GetRelativeTransform(*TransformOther);
	}
}

void FTransformImplementation::Transform_GetRelativeTransformReverseImplementation(
	const MonoObject* InMonoObject, const MonoObject* Other, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (Transform != nullptr && TransformOther != nullptr && OutTransform != nullptr)
	{
		*OutTransform = Transform->GetRelativeTransformReverse(*TransformOther);
	}
}

void FTransformImplementation::Transform_SetToRelativeTransformImplementation(
	const MonoObject* InMonoObject, const MonoObject* ParentTransform)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformParentTransform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(
		ParentTransform);

	if (Transform != nullptr && TransformParentTransform != nullptr)
	{
		Transform->SetToRelativeTransform(*TransformParentTransform);
	}
}

void FTransformImplementation::Transform_TransformFVector4Implementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Transform != nullptr && Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Transform->TransformFVector4(*Vector4);
	}
}

void FTransformImplementation::Transform_TransformFVector4NoScaleImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Transform != nullptr && Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Transform->TransformFVector4NoScale(*Vector4);
	}
}

void FTransformImplementation::Transform_TransformPositionImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->TransformPosition(*Vector);
	}
}

void FTransformImplementation::Transform_TransformPositionNoScaleImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->TransformPositionNoScale(*Vector);
	}
}

void FTransformImplementation::Transform_InverseTransformPositionNoScaleImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->InverseTransformPositionNoScale(*Vector);
	}
}

void FTransformImplementation::Transform_TransformVectorImplementation(const MonoObject* InMonoObject,
                                                                       const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->TransformVector(*Vector);
	}
}

void FTransformImplementation::Transform_TransformVectorNoScaleImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->TransformVectorNoScale(*Vector);
	}
}

void FTransformImplementation::Transform_InverseTransformVectorImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->InverseTransformVector(*Vector);
	}
}

void FTransformImplementation::Transform_InverseTransformVectorNoScaleImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->InverseTransformVectorNoScale(*Vector);
	}
}

void FTransformImplementation::Transform_TransformRotationImplementation(
	const MonoObject* InMonoObject, const MonoObject* Q, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FQuat)),
		CLASS_SCRIPT_STRUCT_NAME(FQuat));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Transform != nullptr && Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Transform->TransformRotation(*Quat);
	}
}

void FTransformImplementation::Transform_InverseTransformRotationImplementation(
	const MonoObject* InMonoObject, const MonoObject* Q, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FQuat)),
		CLASS_SCRIPT_STRUCT_NAME(FQuat));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Transform != nullptr && Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Transform->InverseTransformRotation(*Quat);
	}
}

void FTransformImplementation::Transform_GetScaledScaleImplementation(const MonoObject* InMonoObject, const float Scale,
                                                                      MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (Transform != nullptr && OutTransform != nullptr)
	{
		*OutTransform = Transform->GetScaled(Scale);
	}
}

void FTransformImplementation::Transform_GetScaledVectorImplementation(const MonoObject* InMonoObject,
                                                                       const MonoObject* Scale, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto VectorScale = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Scale);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	if (Transform != nullptr && VectorScale != nullptr && OutTransform != nullptr)
	{
		*OutTransform = Transform->GetScaled(*VectorScale);
	}
}

void FTransformImplementation::Transform_GetSafeScaleReciprocalImplementation(
	const MonoObject* InScale, const float Tolerance, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InScale);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = FTransform::GetSafeScaleReciprocal(*Vector, Tolerance);
	}
}

void FTransformImplementation::Transform_GetLocationImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->GetLocation();
	}
}

void FTransformImplementation::Transform_RotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Transform != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Transform->Rotator();
	}
}

float FTransformImplementation::Transform_GetDeterminantImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		return Transform->GetDeterminant();
	}

	return 0.f;
}

void FTransformImplementation::Transform_SetLocationImplementation(const MonoObject* InMonoObject,
                                                                   const MonoObject* Origin)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Origin);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->SetLocation(*Vector);
	}
}

bool FTransformImplementation::Transform_ContainsNaNImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		return Transform->ContainsNaN();
	}

	return false;
}

bool FTransformImplementation::Transform_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		return Transform->IsValid();
	}

	return false;
}

bool FTransformImplementation::Transform_AreRotationsEqualImplementation(
	const MonoObject* A, const MonoObject* B, const float Tolerance)
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
	const MonoObject* A, const MonoObject* B, const float Tolerance)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	if (TransformA != nullptr && TransformB != nullptr)
	{
		return FTransform::AreTranslationsEqual(*TransformA, *TransformB, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_AreScale3DsEqualImplementation(const MonoObject* A, const MonoObject* B,
                                                                        const float Tolerance)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	if (TransformA != nullptr && TransformB != nullptr)
	{
		return FTransform::AreScale3DsEqual(*TransformA, *TransformB, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_RotationEqualsImplementation(const MonoObject* InMonoObject,
                                                                      const MonoObject* Other, const float Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->RotationEquals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_TranslationEqualsImplementation(
	const MonoObject* InMonoObject, const MonoObject* Other, const float Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->TranslationEquals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_Scale3DEqualsImplementation(const MonoObject* InMonoObject,
                                                                     const MonoObject* Other, const float Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->Scale3DEquals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_EqualsImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
                                                              const float Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->Equals(*TransformOther, Tolerance);
	}

	return false;
}

bool FTransformImplementation::Transform_IdenticalImplementation(const MonoObject* InMonoObject,
                                                                 const MonoObject* Other, const uint32 PortFlags)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->Identical(TransformOther, PortFlags);
	}

	return false;
}

bool FTransformImplementation::Transform_EqualsNoScaleImplementation(const MonoObject* InMonoObject,
                                                                     const MonoObject* Other, const float Tolerance)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		return Transform->EqualsNoScale(*TransformOther, Tolerance);
	}

	return false;
}

void FTransformImplementation::Transform_StaticMultiplyImplementation(MonoObject** OutValue, const MonoObject* A,
                                                                      const MonoObject* B)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FTransform)),
		CLASS_SCRIPT_STRUCT_NAME(FTransform));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutTransform = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(NewMonoObject);

	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	if (OutTransform != nullptr && TransformA != nullptr && TransformB != nullptr)
	{
		FTransform::Multiply(OutTransform, TransformA, TransformB);
	}
}

void FTransformImplementation::Transform_SetComponentsImplementation(const MonoObject* InMonoObject,
                                                                     const MonoObject* InRotation,
                                                                     const MonoObject* InTranslation,
                                                                     const MonoObject* InScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

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

void FTransformImplementation::Transform_SetIdentityImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		Transform->SetIdentity();
	}
}

void FTransformImplementation::Transform_MultiplyScale3DImplementation(const MonoObject* InMonoObject,
                                                                       const MonoObject* Scale3DMultiplier)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Scale3DMultiplier);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->MultiplyScale3D(*Vector);
	}
}

void FTransformImplementation::Transform_SetTranslationImplementation(const MonoObject* InMonoObject,
                                                                      const MonoObject* NewTranslation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewTranslation);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->SetTranslation(*Vector);
	}
}

void FTransformImplementation::Transform_CopyTranslationImplementation(const MonoObject* InMonoObject,
                                                                       const MonoObject* Other)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		Transform->CopyTranslation(*TransformOther);
	}
}

void FTransformImplementation::Transform_ConcatenateRotationImplementation(
	const MonoObject* InMonoObject, const MonoObject* DeltaRotation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(DeltaRotation);

	if (Transform != nullptr && Quat != nullptr)
	{
		Transform->ConcatenateRotation(*Quat);
	}
}

void FTransformImplementation::Transform_AddToTranslationImplementation(const MonoObject* InMonoObject,
                                                                        const MonoObject* DeltaTranslation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(DeltaTranslation);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->AddToTranslation(*Vector);
	}
}

void FTransformImplementation::Transform_AddTranslationsImplementation(const MonoObject* A, const MonoObject* B,
                                                                       MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (TransformA != nullptr && TransformB != nullptr && OutVector != nullptr)
	{
		*OutVector = FTransform::AddTranslations(*TransformA, *TransformB);
	}
}

void FTransformImplementation::Transform_SubtractTranslationsImplementation(
	const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto TransformA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(A);

	const auto TransformB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (TransformA != nullptr && TransformB != nullptr && OutVector != nullptr)
	{
		*OutVector = FTransform::SubtractTranslations(*TransformA, *TransformB);
	}
}

void FTransformImplementation::Transform_SetRotationImplementation(const MonoObject* InMonoObject,
                                                                   const MonoObject* NewRotation)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewRotation);

	if (Transform != nullptr && Quat != nullptr)
	{
		Transform->SetRotation(*Quat);
	}
}

void FTransformImplementation::Transform_CopyRotationImplementation(const MonoObject* InMonoObject,
                                                                    const MonoObject* Other)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		Transform->CopyRotation(*TransformOther);
	}
}

void FTransformImplementation::Transform_SetScale3DImplementation(const MonoObject* InMonoObject,
                                                                  const MonoObject* NewScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewScale3D);

	if (Transform != nullptr && Vector != nullptr)
	{
		Transform->SetScale3D(*Vector);
	}
}

void FTransformImplementation::Transform_CopyScale3DImplementation(const MonoObject* InMonoObject,
                                                                   const MonoObject* Other)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(Other);

	if (Transform != nullptr && TransformOther != nullptr)
	{
		Transform->CopyScale3D(*TransformOther);
	}
}

void FTransformImplementation::Transform_SetTranslationAndScale3DImplementation(
	const MonoObject* InMonoObject, const MonoObject* NewTranslation, const MonoObject* NewScale3D)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto VectorNewTranslation = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		NewTranslation);

	const auto VectorNewScale3D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewScale3D);

	if (Transform != nullptr && VectorNewTranslation != nullptr && VectorNewScale3D != nullptr)
	{
		Transform->SetTranslationAndScale3D(*VectorNewTranslation, *VectorNewScale3D);
	}
}

void FTransformImplementation::Transform_AccumulateImplementation(const MonoObject* InMonoObject,
                                                                  const MonoObject* SourceAtom)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformSourceAtom = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FTransform>(SourceAtom);

	if (Transform != nullptr && TransformSourceAtom != nullptr)
	{
		Transform->Accumulate(*TransformSourceAtom);
	}
}

void FTransformImplementation::Transform_NormalizeRotationImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		Transform->NormalizeRotation();
	}
}

bool FTransformImplementation::Transform_IsRotationNormalizedImplementation(const MonoObject* InMonoObject)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	if (Transform != nullptr)
	{
		return Transform->IsRotationNormalized();
	}

	return false;
}

void FTransformImplementation::Transform_GetRotationImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FQuat)),
		CLASS_SCRIPT_STRUCT_NAME(FQuat));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Transform != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Transform->GetRotation();
	}
}

void FTransformImplementation::Transform_GetTranslationImplementation(const MonoObject* InMonoObject,
                                                                      MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->GetTranslation();
	}
}

void FTransformImplementation::Transform_GetScale3DImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Transform != nullptr && OutVector != nullptr)
	{
		*OutVector = Transform->GetScale3D();
	}
}

void FTransformImplementation::Transform_CopyRotationPartImplementation(const MonoObject* InMonoObject,
                                                                        const MonoObject* SrcBA)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformSrcBA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(SrcBA);

	if (Transform != nullptr && TransformSrcBA != nullptr)
	{
		Transform->CopyRotationPart(*TransformSrcBA);
	}
}

void FTransformImplementation::Transform_CopyTranslationAndScale3DImplementation(
	const MonoObject* InMonoObject, const MonoObject* SrcBA)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto TransformSrcBA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(SrcBA);

	if (Transform != nullptr && TransformSrcBA != nullptr)
	{
		Transform->CopyTranslationAndScale3D(*TransformSrcBA);
	}
}

void FTransformImplementation::Transform_SetFromMatrixImplementation(const MonoObject* InMonoObject,
                                                                     const MonoObject* InMatrix)
{
	const auto Transform = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FTransform>(InMonoObject);

	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMatrix);

	if (Transform != nullptr && Matrix != nullptr)
	{
		Transform->SetFromMatrix(*Matrix);
	}
}
