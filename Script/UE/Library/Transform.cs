using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FTransform
    {
        public void DebugPrint() =>
            TransformImplementation.Transform_DebugPrintImplementation(GetHandle());

        public FString ToHumanReadableString()
        {
            TransformImplementation.Transform_ToHumanReadableStringImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            TransformImplementation.Transform_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            TransformImplementation.Transform_InitFromStringImplementation(GetHandle(), InSourceString);

        public FMatrix ToMatrixWithScale()
        {
            TransformImplementation.Transform_ToMatrixWithScaleImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FMatrix ToInverseMatrixWithScale()
        {
            TransformImplementation.Transform_ToInverseMatrixWithScaleImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FTransform Inverse()
        {
            TransformImplementation.Transform_InverseImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FMatrix ToMatrixNoScale()
        {
            TransformImplementation.Transform_ToMatrixNoScaleImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void Blend(FTransform Atom1, FTransform Atom2, LwcType Alpha) =>
            TransformImplementation.Transform_BlendImplementation(GetHandle(), Atom1, Atom2, Alpha);

        public void BlendWith(FTransform OtherAtom, LwcType Alpha) =>
            TransformImplementation.Transform_BlendWithImplementation(GetHandle(), OtherAtom, Alpha);

        public static FTransform operator +(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FTransform operator *(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FTransform operator *(FTransform A, FQuat B)
        {
            TransformImplementation.Transform_MultiplyQuatImplementation(A.GetHandle(), B, out var OutValue);

            return OutValue;
        }

        public static Boolean AnyHasNegativeScale(FVector InScale3D, FVector InOtherScale3D) =>
            TransformImplementation.Transform_AnyHasNegativeScaleImplementation(InScale3D, InOtherScale3D);

        public void ScaleTranslation(FVector InScale3D) =>
            TransformImplementation.Transform_ScaleTranslationVectorImplementation(GetHandle(), InScale3D);

        public void ScaleTranslation(LwcType Scale) =>
            TransformImplementation.Transform_ScaleTranslationScaleImplementation(GetHandle(), Scale);

        // @TODO SMALL_NUMBER
        public void RemoveScaling(LwcType Scale) =>
            TransformImplementation.Transform_RemoveScalingImplementation(GetHandle(), Scale);

        public LwcType GetMaximumAxisScale() =>
            TransformImplementation.Transform_GetMaximumAxisScaleImplementation(GetHandle());

        public LwcType GetMinimumAxisScale() =>
            TransformImplementation.Transform_GetMinimumAxisScaleImplementation(GetHandle());

        public FTransform GetRelativeTransform(FTransform Other)
        {
            TransformImplementation.Transform_GetRelativeTransformImplementation(GetHandle(), Other, out var OutValue);

            return OutValue;
        }

        public FTransform GetRelativeTransformReverse(FTransform Other)
        {
            TransformImplementation.Transform_GetRelativeTransformReverseImplementation(GetHandle(), Other,
                out var OutValue);

            return OutValue;
        }

        public void SetToRelativeTransform(FTransform ParentTransform) =>
            TransformImplementation.Transform_SetToRelativeTransformImplementation(GetHandle(), ParentTransform);

        public FVector4 TransformFVector4(FVector4 V)
        {
            TransformImplementation.Transform_TransformFVector4Implementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector4 TransformFVector4NoScale(FVector4 V)
        {
            TransformImplementation.Transform_TransformFVector4NoScaleImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector TransformPosition(FVector V)
        {
            TransformImplementation.Transform_TransformPositionImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector TransformPositionNoScale(FVector V)
        {
            TransformImplementation.Transform_TransformPositionNoScaleImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformPosition(FVector V)
        {
            TransformImplementation.Transform_InverseTransformPositionImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformPositionNoScale(FVector V)
        {
            TransformImplementation.Transform_InverseTransformPositionNoScaleImplementation(GetHandle(), V,
                out var OutValue);

            return OutValue;
        }

        public FVector TransformVector(FVector V)
        {
            TransformImplementation.Transform_TransformVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector TransformVectorNoScale(FVector V)
        {
            TransformImplementation.Transform_TransformVectorNoScaleImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformVector(FVector V)
        {
            TransformImplementation.Transform_InverseTransformVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformVectorNoScale(FVector V)
        {
            TransformImplementation.Transform_InverseTransformVectorNoScaleImplementation(GetHandle(), V,
                out var OutValue);

            return OutValue;
        }

        public FQuat TransformRotation(FQuat Q)
        {
            TransformImplementation.Transform_TransformRotationImplementation(GetHandle(), Q, out var OutValue);

            return OutValue;
        }

        public FQuat InverseTransformRotation(FQuat Q)
        {
            TransformImplementation.Transform_InverseTransformRotationImplementation(GetHandle(), Q, out var OutValue);

            return OutValue;
        }

        public FTransform GetScaled(LwcType Scale)
        {
            TransformImplementation.Transform_GetScaledScaleImplementation(GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public FTransform GetScaled(FVector Scale)
        {
            TransformImplementation.Transform_GetScaledVectorImplementation(GetHandle(), Scale, out var OutValue);

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
            TransformImplementation.Transform_GetLocationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator Rotator()
        {
            TransformImplementation.Transform_RotatorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType GetDeterminant() =>
            TransformImplementation.Transform_GetDeterminantImplementation(GetHandle());

        public void SetLocation(FVector Origin) =>
            TransformImplementation.Transform_SetLocationImplementation(GetHandle(), Origin);

        public Boolean ContainsNaN() =>
            TransformImplementation.Transform_ContainsNaNImplementation(GetHandle());

        public Boolean IsValid() =>
            TransformImplementation.Transform_IsValidImplementation(GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public static Boolean AreRotationsEqual(FTransform A, FTransform B, LwcType Tolerance) =>
            TransformImplementation.Transform_AreRotationsEqualImplementation(A.GetHandle(), B.GetHandle(), Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public static Boolean AreTranslationsEqual(FTransform A, FTransform B, LwcType Tolerance) =>
            TransformImplementation.Transform_AreTranslationsEqualImplementation(A.GetHandle(), B.GetHandle(),
                Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public static Boolean AreScale3DsEqual(FTransform A, FTransform B, LwcType Tolerance) =>
            TransformImplementation.Transform_AreScale3DsEqualImplementation(A.GetHandle(), B.GetHandle(), Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean RotationEquals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_RotationEqualsImplementation(GetHandle(), Other, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean TranslationEquals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_TranslationEqualsImplementation(GetHandle(), Other, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Scale3DEquals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_Scale3DEqualsImplementation(GetHandle(), Other, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_EqualsImplementation(GetHandle(), Other, Tolerance);

        public Boolean Identical(FTransform Other, UInt32 PortFlags) =>
            TransformImplementation.Transform_IdenticalImplementation(GetHandle(), Other, PortFlags);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean EqualsNoScale(FTransform Other, LwcType Tolerance) =>
            TransformImplementation.Transform_EqualsNoScaleImplementation(GetHandle(), Other, Tolerance);

        public static void Multiply(out FTransform OutTransform, FTransform A, FTransform B) =>
            TransformImplementation.Transform_StaticMultiplyImplementation(out OutTransform, A.GetHandle(),
                B.GetHandle());

        public void SetComponents(FQuat InRotation, FVector InTranslation, FVector InScale3D) =>
            TransformImplementation.Transform_SetComponentsImplementation(GetHandle(), InRotation, InTranslation,
                InScale3D);

        public void SetIdentity() =>
            TransformImplementation.Transform_SetIdentityImplementation(GetHandle());

        public void MultiplyScale3D(FVector Scale3DMultiplier) =>
            TransformImplementation.Transform_MultiplyScale3DImplementation(GetHandle(), Scale3DMultiplier);

        public void SetTranslation(FVector NewTranslation) =>
            TransformImplementation.Transform_SetTranslationImplementation(GetHandle(), NewTranslation);

        public void CopyTranslation(FTransform Other) =>
            TransformImplementation.Transform_CopyTranslationImplementation(GetHandle(), Other);

        public void ConcatenateRotation(FQuat DeltaRotation) =>
            TransformImplementation.Transform_ConcatenateRotationImplementation(GetHandle(), DeltaRotation);

        public void AddToTranslation(FVector DeltaTranslation) =>
            TransformImplementation.Transform_AddToTranslationImplementation(GetHandle(), DeltaTranslation);

        public static FVector AddTranslations(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_AddTranslationsImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FVector SubtractTranslations(FTransform A, FTransform B)
        {
            TransformImplementation.Transform_SubtractTranslationsImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public void SetRotation(FQuat NewRotation) =>
            TransformImplementation.Transform_SetRotationImplementation(GetHandle(), NewRotation);

        public void CopyRotation(FTransform Other) =>
            TransformImplementation.Transform_CopyRotationImplementation(GetHandle(), Other);

        public void SetScale3D(FVector NewScale3D) =>
            TransformImplementation.Transform_SetScale3DImplementation(GetHandle(), NewScale3D);

        public void CopyScale3D(FTransform Other) =>
            TransformImplementation.Transform_CopyScale3DImplementation(GetHandle(), Other);

        public void SetTranslationAndScale3D(FVector NewTranslation, FVector NewScale3D) =>
            TransformImplementation.Transform_SetTranslationAndScale3DImplementation(GetHandle(), NewTranslation,
                NewScale3D);

        public void Accumulate(FTransform SourceAtom) =>
            TransformImplementation.Transform_AccumulateImplementation(GetHandle(), SourceAtom);

        public void NormalizeRotation() =>
            TransformImplementation.Transform_NormalizeRotationImplementation(GetHandle());

        public Boolean IsRotationNormalized() =>
            TransformImplementation.Transform_IsRotationNormalizedImplementation(GetHandle());

        public FQuat GetRotation()
        {
            TransformImplementation.Transform_GetRotationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetTranslation()
        {
            TransformImplementation.Transform_GetTranslationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetScale3D()
        {
            TransformImplementation.Transform_GetScale3DImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void CopyRotationPart(FTransform SrcBA) =>
            TransformImplementation.Transform_CopyRotationPartImplementation(GetHandle(), SrcBA);

        public void CopyTranslationAndScale3D(FTransform SrcBA) =>
            TransformImplementation.Transform_CopyTranslationAndScale3DImplementation(GetHandle(), SrcBA);

        public void SetFromMatrix(FMatrix InMatrix) =>
            TransformImplementation.Transform_SetFromMatrixImplementation(GetHandle(), InMatrix);
    }
}