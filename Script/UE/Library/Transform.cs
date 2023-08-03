using System;
using Script.Library;
using Script.Common;
#if UE_5_0_OR_LATER
using LwcType = System.Double;
#else
using LwcType = System.Single;
#endif

namespace Script.CoreUObject
{
    public partial class FTransform
    {
        public void DebugPrint() =>
            TransformImplementation.Transform_DebugPrintImplementation(this);

        public FString ToHumanReadableString()
        {
            TransformImplementation.Transform_ToHumanReadableStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            TransformImplementation.Transform_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            TransformImplementation.Transform_InitFromStringImplementation(this, InSourceString);

        public FMatrix ToMatrixWithScale()
        {
            TransformImplementation.Transform_ToMatrixWithScaleImplementation(this, out var OutValue);

            return OutValue;
        }

        public FMatrix ToInverseMatrixWithScale()
        {
            TransformImplementation.Transform_ToInverseMatrixWithScaleImplementation(this, out var OutValue);

            return OutValue;
        }

        public FTransform Inverse()
        {
            TransformImplementation.Transform_InverseImplementation(this, out var OutValue);

            return OutValue;
        }

        public FMatrix ToMatrixNoScale()
        {
            TransformImplementation.Transform_ToMatrixNoScaleImplementation(this, out var OutValue);

            return OutValue;
        }

        public void Blend(FTransform Atom1, FTransform Atom2, LwcType Alpha) =>
            TransformImplementation.Transform_BlendImplementation(this, Atom1, Atom2, Alpha);

        public void BlendWith(FTransform OtherAtom, LwcType Alpha) =>
            TransformImplementation.Transform_BlendWithImplementation(this, OtherAtom, Alpha);

        public static FTransform operator +(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FTransform operator *(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FTransform operator *(FTransform A, FQuat B)
        {
            TransformImplementation.Transform_MultiplyQuatImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static Boolean AnyHasNegativeScale(FVector InScale3D, FVector InOtherScale3D) =>
            TransformImplementation.Transform_AnyHasNegativeScaleImplementation(InScale3D, InOtherScale3D);

        public void ScaleTranslation(FVector InScale3D) =>
            TransformImplementation.Transform_ScaleTranslationVectorImplementation(this, InScale3D);

        public void ScaleTranslation(LwcType Scale) =>
            TransformImplementation.Transform_ScaleTranslationScaleImplementation(this, Scale);

        // @TODO SMALL_NUMBER
        public void RemoveScaling(LwcType Scale) =>
            TransformImplementation.Transform_RemoveScalingImplementation(this, Scale);

        public LwcType GetMaximumAxisScale() =>
            TransformImplementation.Transform_GetMaximumAxisScaleImplementation(this);

        public LwcType GetMinimumAxisScale() =>
            TransformImplementation.Transform_GetMinimumAxisScaleImplementation(this);

        public FTransform GetRelativeTransform(FTransform Other)
        {
            TransformImplementation.Transform_GetRelativeTransformImplementation(this, Other, out var OutValue);

            return OutValue;
        }

        public FTransform GetRelativeTransformReverse(FTransform Other)
        {
            TransformImplementation.Transform_GetRelativeTransformReverseImplementation(this, Other, out var OutValue);

            return OutValue;
        }

        public void SetToRelativeTransform(FTransform ParentTransform) =>
            TransformImplementation.Transform_SetToRelativeTransformImplementation(this, ParentTransform);

        public FVector4 TransformFVector4(FVector4 V)
        {
            TransformImplementation.Transform_TransformFVector4Implementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector4 TransformFVector4NoScale(FVector4 V)
        {
            TransformImplementation.Transform_TransformFVector4NoScaleImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector TransformPosition(FVector V)
        {
            TransformImplementation.Transform_TransformPositionImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector TransformPositionNoScale(FVector V)
        {
            TransformImplementation.Transform_TransformPositionNoScaleImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformPosition(FVector V)
        {
            TransformImplementation.Transform_InverseTransformPositionImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformPositionNoScale(FVector V)
        {
            TransformImplementation.Transform_InverseTransformPositionNoScaleImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector TransformVector(FVector V)
        {
            TransformImplementation.Transform_TransformVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector TransformVectorNoScale(FVector V)
        {
            TransformImplementation.Transform_TransformVectorNoScaleImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformVector(FVector V)
        {
            TransformImplementation.Transform_InverseTransformVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformVectorNoScale(FVector V)
        {
            TransformImplementation.Transform_InverseTransformVectorNoScaleImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FQuat TransformRotation(FQuat Q)
        {
            TransformImplementation.Transform_TransformRotationImplementation(this, Q, out var OutValue);

            return OutValue;
        }

        public FQuat InverseTransformRotation(FQuat Q)
        {
            TransformImplementation.Transform_InverseTransformRotationImplementation(this, Q, out var OutValue);

            return OutValue;
        }

        public FTransform GetScaled(LwcType Scale)
        {
            TransformImplementation.Transform_GetScaledScaleImplementation(this, Scale, out var OutValue);

            return OutValue;
        }

        public FTransform GetScaled(FVector Scale)
        {
            TransformImplementation.Transform_GetScaledVectorImplementation(this, Scale, out var OutValue);

            return OutValue;
        }

        // @TODO
        // GetScaledAxis
        // GetUnitAxis
        // Mirror

        // @TODO SMALL_NUMBER
        public static FVector GetSafeScaleReciprocal(FVector InScale, LwcType Tolerance)
        {
            TransformImplementation.Transform_GetSafeScaleReciprocalImplementation(InScale, Tolerance,
                out var OutValue);

            return OutValue;
        }

        public FVector GetLocation()
        {
            TransformImplementation.Transform_GetLocationImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator Rotator()
        {
            TransformImplementation.Transform_RotatorImplementation(this, out var OutValue);

            return OutValue;
        }

        public LwcType GetDeterminant() =>
            TransformImplementation.Transform_GetDeterminantImplementation(this);

        public void SetLocation(FVector Origin) =>
            TransformImplementation.Transform_SetLocationImplementation(this, Origin);

        public Boolean ContainsNaN() =>
            TransformImplementation.Transform_ContainsNaNImplementation(this);

        public Boolean IsValid() =>
            TransformImplementation.Transform_IsValidImplementation(this);

        // @TODO KINDA_SMALL_NUMBER
        public static Boolean AreRotationsEqual(FTransform A, FTransform B, LwcType Tolerance) =>
            TransformImplementation.Transform_AreRotationsEqualImplementation(A, B, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public static Boolean AreTranslationsEqual(FTransform A, FTransform B, LwcType Tolerance) =>
            TransformImplementation.Transform_AreTranslationsEqualImplementation(A, B, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public static Boolean AreScale3DsEqual(FTransform A, FTransform B, LwcType Tolerance) =>
            TransformImplementation.Transform_AreScale3DsEqualImplementation(A, B, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean RotationEquals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_RotationEqualsImplementation(this, Other, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean TranslationEquals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_TranslationEqualsImplementation(this, Other, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Scale3DEquals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_Scale3DEqualsImplementation(this, Other, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_EqualsImplementation(this, Other, Tolerance);

        public Boolean Identical(FTransform Other, UInt32 PortFlags) =>
            TransformImplementation.Transform_IdenticalImplementation(this, Other, PortFlags);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean EqualsNoScale(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_EqualsNoScaleImplementation(this, Other, Tolerance);

        public static void Multiply(out FTransform OutTransform, FTransform A, FTransform B) =>
            TransformImplementation.Transform_StaticMultiplyImplementation(out OutTransform, A, B);

        public void SetComponents(FQuat InRotation, FVector InTranslation, FVector InScale3D) =>
            TransformImplementation.Transform_SetComponentsImplementation(this, InRotation, InTranslation, InScale3D);

        public void SetIdentity() =>
            TransformImplementation.Transform_SetIdentityImplementation(this);

        public void MultiplyScale3D(FVector Scale3DMultiplier) =>
            TransformImplementation.Transform_MultiplyScale3DImplementation(this, Scale3DMultiplier);

        public void SetTranslation(FVector NewTranslation) =>
            TransformImplementation.Transform_SetTranslationImplementation(this, NewTranslation);

        public void CopyTranslation(FTransform Other) =>
            TransformImplementation.Transform_CopyTranslationImplementation(this, Other);

        public void ConcatenateRotation(FQuat DeltaRotation) =>
            TransformImplementation.Transform_ConcatenateRotationImplementation(this, DeltaRotation);

        public void AddToTranslation(FVector DeltaTranslation) =>
            TransformImplementation.Transform_AddToTranslationImplementation(this, DeltaTranslation);

        public static FVector AddTranslations(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_AddTranslationsImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector SubtractTranslations(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_SubtractTranslationsImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public void SetRotation(FQuat NewRotation) =>
            TransformImplementation.Transform_SetRotationImplementation(this, NewRotation);

        public void CopyRotation(FTransform Other) =>
            TransformImplementation.Transform_CopyRotationImplementation(this, Other);

        public void SetScale3D(FVector NewScale3D) =>
            TransformImplementation.Transform_SetScale3DImplementation(this, NewScale3D);

        public void CopyScale3D(FTransform Other) =>
            TransformImplementation.Transform_CopyScale3DImplementation(this, Other);

        public void SetTranslationAndScale3D(FVector NewTranslation, FVector NewScale3D) =>
            TransformImplementation.Transform_SetTranslationAndScale3DImplementation(this, NewTranslation, NewScale3D);

        public void Accumulate(FTransform SourceAtom) =>
            TransformImplementation.Transform_AccumulateImplementation(this, SourceAtom);

        public void NormalizeRotation() =>
            TransformImplementation.Transform_NormalizeRotationImplementation(this);

        public Boolean IsRotationNormalized() =>
            TransformImplementation.Transform_IsRotationNormalizedImplementation(this);

        public FQuat GetRotation()
        {
            TransformImplementation.Transform_GetRotationImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetTranslation()
        {
            TransformImplementation.Transform_GetTranslationImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetScale3D()
        {
            TransformImplementation.Transform_GetScale3DImplementation(this, out var OutValue);

            return OutValue;
        }

        public void CopyRotationPart(FTransform SrcBA) =>
            TransformImplementation.Transform_CopyRotationPartImplementation(this, SrcBA);

        public void CopyTranslationAndScale3D(FTransform SrcBA) =>
            TransformImplementation.Transform_CopyTranslationAndScale3DImplementation(this, SrcBA);

        public void SetFromMatrix(FMatrix InMatrix) =>
            TransformImplementation.Transform_SetFromMatrixImplementation(this, InMatrix);
    }
}