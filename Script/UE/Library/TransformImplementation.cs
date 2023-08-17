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
        public static extern void Transform_DebugPrintImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToHumanReadableStringImplementation(IntPtr InTransform,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToStringImplementation(IntPtr InTransform, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_InitFromStringImplementation(IntPtr InTransform,
            FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToMatrixWithScaleImplementation(IntPtr InTransform,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToInverseMatrixWithScaleImplementation(IntPtr InTransform,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseImplementation(IntPtr InTransform, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ToMatrixNoScaleImplementation(IntPtr InTransform, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_BlendImplementation(IntPtr InTransform, FTransform Atom1,
            FTransform Atom2, LwcType Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_BlendWithImplementation(IntPtr InTransform, FTransform OtherAtom,
            LwcType Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AddImplementation(IntPtr A, IntPtr B, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_MultiplyImplementation(IntPtr A, IntPtr B, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_MultiplyQuatImplementation(IntPtr InTransform, FQuat Other,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AnyHasNegativeScaleImplementation(FVector InScale3D,
            FVector InOtherScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ScaleTranslationVectorImplementation(IntPtr InTransform,
            FVector InScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ScaleTranslationScaleImplementation(IntPtr InTransform, LwcType Scale);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_RemoveScalingImplementation(IntPtr InTransform, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Transform_GetMaximumAxisScaleImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Transform_GetMinimumAxisScaleImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetRelativeTransformImplementation(IntPtr InTransform, FTransform Other,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetRelativeTransformReverseImplementation(IntPtr InTransform,
            FTransform Other, out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetToRelativeTransformImplementation(IntPtr InTransform,
            FTransform ParentTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformFVector4Implementation(IntPtr InTransform, FVector4 V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformFVector4NoScaleImplementation(IntPtr InTransform, FVector4 V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformPositionImplementation(IntPtr InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformPositionNoScaleImplementation(IntPtr InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformPositionImplementation(IntPtr InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformPositionNoScaleImplementation(IntPtr InTransform,
            FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformVectorImplementation(IntPtr InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformVectorNoScaleImplementation(IntPtr InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformVectorImplementation(IntPtr InTransform, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformVectorNoScaleImplementation(IntPtr InTransform,
            FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_TransformRotationImplementation(IntPtr InTransform, FQuat Q,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_InverseTransformRotationImplementation(IntPtr InTransform, FQuat Q,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetScaledScaleImplementation(IntPtr InTransform, LwcType Scale,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetScaledVectorImplementation(IntPtr InTransform, FVector Scale,
            out FTransform OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetSafeScaleReciprocalImplementation(FVector InScale, LwcType Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetLocationImplementation(IntPtr InTransform, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_RotatorImplementation(IntPtr InTransform, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Transform_GetDeterminantImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetLocationImplementation(IntPtr InTransform, FVector Origin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_ContainsNaNImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_IsValidImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AreRotationsEqualImplementation(IntPtr A, IntPtr B,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AreTranslationsEqualImplementation(IntPtr A, IntPtr B,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_AreScale3DsEqualImplementation(IntPtr A, IntPtr B,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_RotationEqualsImplementation(IntPtr InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_TranslationEqualsImplementation(IntPtr InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_Scale3DEqualsImplementation(IntPtr InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_EqualsImplementation(IntPtr InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_IdenticalImplementation(IntPtr InTransform, FTransform Other,
            UInt32 PortFlags);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_EqualsNoScaleImplementation(IntPtr InTransform, FTransform Other,
            LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_StaticMultiplyImplementation(out FTransform OutTransform, IntPtr A,
            IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetComponentsImplementation(IntPtr InTransform, FQuat InRotation,
            FVector InTranslation, FVector InScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetIdentityImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_MultiplyScale3DImplementation(IntPtr InTransform,
            FVector Scale3DMultiplier);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Transform_SetTranslationImplementation(IntPtr InTransform, FVector NewTranslation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyTranslationImplementation(IntPtr InTransform, FTransform Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_ConcatenateRotationImplementation(IntPtr InTransform,
            FQuat DeltaRotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AddToTranslationImplementation(IntPtr InTransform,
            FVector DeltaTranslation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AddTranslationsImplementation(IntPtr A, IntPtr B,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SubtractTranslationsImplementation(IntPtr A, IntPtr B,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetRotationImplementation(IntPtr InTransform, FQuat NewRotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyRotationImplementation(IntPtr InTransform, FTransform Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetScale3DImplementation(IntPtr InTransform, FVector NewScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyScale3DImplementation(IntPtr InTransform, FTransform Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetTranslationAndScale3DImplementation(IntPtr InTransform,
            FVector NewTranslation, FVector NewScale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_AccumulateImplementation(IntPtr InTransform, FTransform SourceAtom);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_NormalizeRotationImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Transform_IsRotationNormalizedImplementation(IntPtr InTransform);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetRotationImplementation(IntPtr InTransform, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetTranslationImplementation(IntPtr InTransform, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_GetScale3DImplementation(IntPtr InTransform, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyRotationPartImplementation(IntPtr InTransform, FTransform SrcBA);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_CopyTranslationAndScale3DImplementation(IntPtr InTransform,
            FTransform SrcBA);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Transform_SetFromMatrixImplementation(IntPtr InTransform, FMatrix InMatrix);
    }
}