using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
#if UE_5_0_OR_LATER
using LwcType = System.Double;
#else
using LwcType = System.Single;
#endif

namespace Script.Library
{
    public static class TransformImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_DebugPrintImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToHumanReadableStringImplementation(FTransform InTransform,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToStringImplementation(FTransform InTransform, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_InitFromStringImplementation(FTransform InTransform,
            FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToMatrixWithScaleImplementation(FTransform InTransform,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToInverseMatrixWithScaleImplementation(FTransform InTransform,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseImplementation(FTransform InTransform, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToMatrixNoScaleImplementation(FTransform InTransform, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_BlendImplementation(FTransform InTransform, FTransform Atom1,
            FTransform Atom2, LwcType Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_BlendWithImplementation(FTransform InTransform, FTransform OtherAtom,
            LwcType Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AddImplementation(FTransform A, FTransform B, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_MultiplyImplementation(FTransform A, FTransform B, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_MultiplyQuatImplementation(FTransform InTransform, FQuat Other,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AnyHasNegativeScaleImplementation(FVector InScale3D,
            FVector InOtherScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ScaleTranslationVectorImplementation(FTransform InTransform,
            FVector InScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ScaleTranslationScaleImplementation(FTransform InTransform, LwcType Scale);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_RemoveScalingImplementation(FTransform InTransform, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Transform_GetMaximumAxisScaleImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Transform_GetMinimumAxisScaleImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetRelativeTransformImplementation(FTransform InTransform, FTransform Other,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetRelativeTransformReverseImplementation(FTransform InTransform,
            FTransform Other, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetToRelativeTransformImplementation(FTransform InTransform,
            FTransform ParentTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformFVector4Implementation(FTransform InTransform, FVector4 V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformFVector4NoScaleImplementation(FTransform InTransform, FVector4 V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformPositionImplementation(FTransform InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformPositionNoScaleImplementation(FTransform InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformPositionImplementation(FTransform InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformPositionNoScaleImplementation(FTransform InTransform,
            FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformVectorImplementation(FTransform InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformVectorNoScaleImplementation(FTransform InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformVectorImplementation(FTransform InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformVectorNoScaleImplementation(FTransform InTransform,
            FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformRotationImplementation(FTransform InTransform, FQuat Q,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformRotationImplementation(FTransform InTransform, FQuat Q,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetScaledScaleImplementation(FTransform InTransform, LwcType Scale,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetScaledVectorImplementation(FTransform InTransform, FVector Scale,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetSafeScaleReciprocalImplementation(FVector InScale, LwcType Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetLocationImplementation(FTransform InTransform, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_RotatorImplementation(FTransform InTransform, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Transform_GetDeterminantImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetLocationImplementation(FTransform InTransform, FVector Origin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_ContainsNaNImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_IsValidImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AreRotationsEqualImplementation(FTransform A, FTransform B,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AreTranslationsEqualImplementation(FTransform A, FTransform B,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AreScale3DsEqualImplementation(FTransform A, FTransform B,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_RotationEqualsImplementation(FTransform InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_TranslationEqualsImplementation(FTransform InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_Scale3DEqualsImplementation(FTransform InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_EqualsImplementation(FTransform InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_IdenticalImplementation(FTransform InTransform, FTransform Other,
            UInt32 PortFlags);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_EqualsNoScaleImplementation(FTransform InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_StaticMultiplyImplementation(out FTransform OutTransform, FTransform A,
            FTransform B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetComponentsImplementation(FTransform InTransform, FQuat InRotation,
            FVector InTranslation, FVector InScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetIdentityImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_MultiplyScale3DImplementation(FTransform InTransform,
            FVector Scale3DMultiplier);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Transform_SetTranslationImplementation(FTransform InTransform, FVector NewTranslation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyTranslationImplementation(FTransform InTransform, FTransform Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ConcatenateRotationImplementation(FTransform InTransform,
            FQuat DeltaRotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AddToTranslationImplementation(FTransform InTransform,
            FVector DeltaTranslation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AddTranslationsImplementation(FTransform A, FTransform B,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SubtractTranslationsImplementation(FTransform A, FTransform B,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetRotationImplementation(FTransform InTransform, FQuat NewRotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyRotationImplementation(FTransform InTransform, FTransform Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetScale3DImplementation(FTransform InTransform, FVector NewScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyScale3DImplementation(FTransform InTransform, FTransform Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetTranslationAndScale3DImplementation(FTransform InTransform,
            FVector NewTranslation, FVector NewScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AccumulateImplementation(FTransform InTransform, FTransform SourceAtom);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_NormalizeRotationImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_IsRotationNormalizedImplementation(FTransform InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetRotationImplementation(FTransform InTransform, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetTranslationImplementation(FTransform InTransform, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetScale3DImplementation(FTransform InTransform, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyRotationPartImplementation(FTransform InTransform, FTransform SrcBA);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyTranslationAndScale3DImplementation(FTransform InTransform,
            FTransform SrcBA);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetFromMatrixImplementation(FTransform InTransform, FMatrix InMatrix);
    }
}