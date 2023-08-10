#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FTransformImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static void Transform_DebugPrintImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Transform_ToHumanReadableStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          MonoObject** OutValue);

	static void Transform_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static bool Transform_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject* InSourceString);

	static void Transform_ToMatrixWithScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject** OutValue);

	static void Transform_ToInverseMatrixWithScaleImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void Transform_InverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static void Transform_ToMatrixNoScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);

	static void Transform_BlendImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          const FGarbageCollectionHandle Atom1,
	                                          const FGarbageCollectionHandle Atom2, LwcType Alpha);

	static void Transform_BlendWithImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* OtherAtom, LwcType Alpha);

	static void Transform_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        MonoObject** OutValue);

	static void Transform_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                             MonoObject** OutValue);

	static void Transform_MultiplyQuatImplementation(const FGarbageCollectionHandle A, const MonoObject* B,
	                                                 MonoObject** OutValue);

	static bool Transform_AnyHasNegativeScaleImplementation(const MonoObject* InScale3D,
	                                                        const MonoObject* InOtherScale3D);

	static void Transform_ScaleTranslationVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                           const MonoObject* InScale3D);

	static void Transform_ScaleTranslationScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          LwcType Scale);

	static void Transform_RemoveScalingImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  LwcType Tolerance);

	static LwcType
	Transform_GetMaximumAxisScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType
	Transform_GetMinimumAxisScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Transform_GetRelativeTransformImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                         const MonoObject* Other, MonoObject** OutValue);

	static void Transform_GetRelativeTransformReverseImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Other, MonoObject** OutValue);

	static void Transform_SetToRelativeTransformImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                           const MonoObject* ParentTransform);

	static void Transform_TransformFVector4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformFVector4NoScaleImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformPositionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformPositionNoScaleImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue);

	static void Transform_InverseTransformPositionNoScaleImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformVectorNoScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                           const MonoObject* V, MonoObject** OutValue);

	static void Transform_InverseTransformVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                           const MonoObject* V, MonoObject** OutValue);

	static void Transform_InverseTransformVectorNoScaleImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformRotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      const MonoObject* Q, MonoObject** OutValue);

	static void Transform_InverseTransformRotationImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Q, MonoObject** OutValue);

	static void Transform_GetScaledScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   LwcType Scale, MonoObject** OutValue);

	static void Transform_GetScaledVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    const MonoObject* Scale, MonoObject** OutValue);

	static void Transform_GetSafeScaleReciprocalImplementation(const MonoObject* InScale, LwcType Tolerance,
	                                                           MonoObject** OutValue);

	static void Transform_GetLocationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);

	static void Transform_RotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static LwcType Transform_GetDeterminantImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Transform_SetLocationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                const MonoObject* Origin);

	static bool Transform_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Transform_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Transform_AreRotationsEqualImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B, LwcType Tolerance);

	static bool Transform_AreTranslationsEqualImplementation(const FGarbageCollectionHandle A,
	                                                         const FGarbageCollectionHandle B, LwcType Tolerance);

	static bool Transform_AreScale3DsEqualImplementation(const FGarbageCollectionHandle A,
	                                                     const FGarbageCollectionHandle B, LwcType Tolerance);

	static bool Transform_RotationEqualsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const MonoObject* Other, LwcType Tolerance);

	static bool Transform_TranslationEqualsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      const MonoObject* Other, LwcType Tolerance);

	static bool Transform_Scale3DEqualsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* Other, LwcType Tolerance);

	static bool Transform_EqualsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const MonoObject* Other, LwcType Tolerance);

	static bool Transform_IdenticalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* Other, uint32 PortFlags);

	static bool Transform_EqualsNoScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* Other, LwcType Tolerance);

	static void Transform_StaticMultiplyImplementation(MonoObject** OutValue, const FGarbageCollectionHandle A,
	                                                   const FGarbageCollectionHandle B);

	static void Transform_SetComponentsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* InRotation, const MonoObject* InTranslation,
	                                                  const MonoObject* InScale3D);

	static void Transform_SetIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Transform_MultiplyScale3DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    const MonoObject* Scale3DMultiplier);

	static void Transform_SetTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const MonoObject* NewTranslation);

	static void Transform_CopyTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    const MonoObject* Other);

	static void Transform_ConcatenateRotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                        const MonoObject* DeltaRotation);

	static void Transform_AddToTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     const MonoObject* DeltaTranslation);

	static void Transform_AddTranslationsImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B, MonoObject** OutValue);

	static void Transform_SubtractTranslationsImplementation(const FGarbageCollectionHandle A,
	                                                         const FGarbageCollectionHandle B, MonoObject** OutValue);

	static void Transform_SetRotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                const MonoObject* NewRotation);

	static void Transform_CopyRotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 const MonoObject* Other);

	static void Transform_SetScale3DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               const MonoObject* NewScale3D);

	static void Transform_CopyScale3DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                const MonoObject* Other);

	static void Transform_SetTranslationAndScale3DImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* NewTranslation,
		const MonoObject* NewScale3D);

	static void Transform_AccumulateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               const MonoObject* SourceAtom);

	static void Transform_NormalizeRotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Transform_IsRotationNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Transform_GetRotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);

	static void Transform_GetTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static void Transform_GetScale3DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static void Transform_CopyRotationPartImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     const MonoObject* SrcBA);

	static void Transform_CopyTranslationAndScale3DImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* SrcBA);

	static void Transform_SetFromMatrixImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* InMatrix);
};
