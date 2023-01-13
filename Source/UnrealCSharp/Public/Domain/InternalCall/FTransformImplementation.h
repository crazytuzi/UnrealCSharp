#pragma once

#include "mono/metadata/object-forward.h"

class FTransformImplementation
{
public:
	static void Transform_DebugPrintImplementation(const MonoObject* InMonoObject);

	static void Transform_ToHumanReadableStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Transform_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static void Transform_ToMatrixWithScaleImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_ToInverseMatrixWithScaleImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_InverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_ToMatrixNoScaleImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_BlendImplementation(const MonoObject* InMonoObject, const MonoObject* Atom1,
	                                          const MonoObject* Atom2, float Alpha);

	static void Transform_BlendWithImplementation(const MonoObject* InMonoObject, const MonoObject* OtherAtom,
	                                              float Alpha);

	static void Transform_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Transform_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Transform_MultiplyQuatImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static bool Transform_AnyHasNegativeScaleImplementation(const MonoObject* InScale3D,
	                                                        const MonoObject* InOtherScale3D);

	static void Transform_ScaleTranslationVectorImplementation(const MonoObject* InMonoObject,
	                                                           const MonoObject* InScale3D);

	static void Transform_ScaleTranslationScaleImplementation(const MonoObject* InMonoObject, float Scale);

	static void Transform_RemoveScalingImplementation(const MonoObject* InMonoObject, float Tolerance);

	static float Transform_GetMaximumAxisScaleImplementation(const MonoObject* InMonoObject);

	static float Transform_GetMinimumAxisScaleImplementation(const MonoObject* InMonoObject);

	static void Transform_GetRelativeTransformImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                                         MonoObject** OutValue);

	static void Transform_GetRelativeTransformReverseImplementation(const MonoObject* InMonoObject,
	                                                                const MonoObject* Other, MonoObject** OutValue);

	static void Transform_SetToRelativeTransformImplementation(const MonoObject* InMonoObject,
	                                                           const MonoObject* ParentTransform);

	static void Transform_TransformFVector4Implementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                      MonoObject** OutValue);

	static void Transform_TransformFVector4NoScaleImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                             MonoObject** OutValue);

	static void Transform_TransformPositionImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                      MonoObject** OutValue);

	static void Transform_TransformPositionNoScaleImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                             MonoObject** OutValue);

	static void Transform_InverseTransformPositionNoScaleImplementation(const MonoObject* InMonoObject,
	                                                                    const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                    MonoObject** OutValue);

	static void Transform_TransformVectorNoScaleImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                           MonoObject** OutValue);

	static void Transform_InverseTransformVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                           MonoObject** OutValue);

	static void Transform_InverseTransformVectorNoScaleImplementation(const MonoObject* InMonoObject,
	                                                                  const MonoObject* V, MonoObject** OutValue);

	static void Transform_TransformRotationImplementation(const MonoObject* InMonoObject, const MonoObject* Q,
	                                                      MonoObject** OutValue);

	static void Transform_InverseTransformRotationImplementation(const MonoObject* InMonoObject, const MonoObject* Q,
	                                                             MonoObject** OutValue);

	static void Transform_GetScaledScaleImplementation(const MonoObject* InMonoObject, float Scale,
	                                                   MonoObject** OutValue);

	static void Transform_GetScaledVectorImplementation(const MonoObject* InMonoObject, const MonoObject* Scale,
	                                                    MonoObject** OutValue);

	static void Transform_GetSafeScaleReciprocalImplementation(const MonoObject* InScale, float Tolerance,
	                                                           MonoObject** OutValue);

	static void Transform_GetLocationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_RotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static float Transform_GetDeterminantImplementation(const MonoObject* InMonoObject);

	static void Transform_SetLocationImplementation(const MonoObject* InMonoObject, const MonoObject* Origin);

	static bool Transform_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static bool Transform_IsValidImplementation(const MonoObject* InMonoObject);

	static bool Transform_AreRotationsEqualImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static bool Transform_AreTranslationsEqualImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static bool Transform_AreScale3DsEqualImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static bool Transform_RotationEqualsImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                                   float Tolerance);

	static bool Transform_TranslationEqualsImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                                      float Tolerance);

	static bool Transform_Scale3DEqualsImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                                  float Tolerance);

	static bool Transform_EqualsImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                           float Tolerance);

	static bool Transform_IdenticalImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                              uint32 PortFlags);

	static bool Transform_EqualsNoScaleImplementation(const MonoObject* InMonoObject, const MonoObject* Other,
	                                                  float Tolerance);

	static void Transform_StaticMultiplyImplementation(MonoObject** OutValue, const MonoObject* A, const MonoObject* B);

	static void Transform_SetComponentsImplementation(const MonoObject* InMonoObject, const MonoObject* InRotation,
	                                                  const MonoObject* InTranslation, const MonoObject* InScale3D);

	static void Transform_SetIdentityImplementation(const MonoObject* InMonoObject);

	static void Transform_MultiplyScale3DImplementation(const MonoObject* InMonoObject,
	                                                    const MonoObject* Scale3DMultiplier);

	static void Transform_SetTranslationImplementation(const MonoObject* InMonoObject,
	                                                   const MonoObject* NewTranslation);

	static void Transform_CopyTranslationImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static void Transform_ConcatenateRotationImplementation(const MonoObject* InMonoObject,
	                                                        const MonoObject* DeltaRotation);

	static void Transform_AddToTranslationImplementation(const MonoObject* InMonoObject,
	                                                     const MonoObject* DeltaTranslation);

	static void Transform_AddTranslationsImplementation(const MonoObject* A, const MonoObject* B,
	                                                    MonoObject** OutValue);

	static void Transform_SubtractTranslationsImplementation(const MonoObject* A, const MonoObject* B,
	                                                         MonoObject** OutValue);

	static void Transform_SetRotationImplementation(const MonoObject* InMonoObject, const MonoObject* NewRotation);

	static void Transform_CopyRotationImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static void Transform_SetScale3DImplementation(const MonoObject* InMonoObject, const MonoObject* NewScale3D);

	static void Transform_CopyScale3DImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static void Transform_SetTranslationAndScale3DImplementation(const MonoObject* InMonoObject,
	                                                             const MonoObject* NewTranslation,
	                                                             const MonoObject* NewScale3D);

	static void Transform_AccumulateImplementation(const MonoObject* InMonoObject, const MonoObject* SourceAtom);

	static void Transform_NormalizeRotationImplementation(const MonoObject* InMonoObject);

	static bool Transform_IsRotationNormalizedImplementation(const MonoObject* InMonoObject);

	static void Transform_GetRotationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_GetTranslationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_GetScale3DImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Transform_CopyRotationPartImplementation(const MonoObject* InMonoObject, const MonoObject* SrcBA);

	static void Transform_CopyTranslationAndScale3DImplementation(const MonoObject* InMonoObject,
	                                                              const MonoObject* SrcBA);

	static void Transform_SetFromMatrixImplementation(const MonoObject* InMonoObject, const MonoObject* InMatrix);
};
