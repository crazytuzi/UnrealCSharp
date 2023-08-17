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
    public static class MatrixImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Matrix_GetMImplementation(IntPtr InMatrix, UInt32 InRow, UInt32 InColumn);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetMImplementation(IntPtr InMatrix, UInt32 InRow, UInt32 InColumn,
            LwcType InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetIdentityImplementation(IntPtr InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_MultiplyImplementation(IntPtr A, IntPtr B, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_AddImplementation(IntPtr A, IntPtr B, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_MultiplyScaleImplementation(IntPtr InMatrix, LwcType Other,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_EqualsImplementation(IntPtr A, IntPtr B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransformFVector4Implementation(IntPtr InMatrix, FVector4 V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransformPositionImplementation(IntPtr InMatrix, FVector V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseTransformPositionImplementation(IntPtr InMatrix, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransformVectorImplementation(IntPtr InMatrix, FVector V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseTransformVectorImplementation(IntPtr InMatrix, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetTransposedImplementation(IntPtr InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Matrix_DeterminantImplementation(IntPtr InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Matrix_RotDeterminantImplementation(IntPtr InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseFastImplementation(IntPtr InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseImplementation(IntPtr InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransposeAdjointImplementation(IntPtr InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_RemoveScalingImplementation(IntPtr InMatrix, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetMatrixWithoutScaleImplementation(IntPtr InMatrix, LwcType Tolerance,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ExtractScalingImplementation(IntPtr InMatrix, LwcType Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetScaleVectorImplementation(IntPtr InMatrix, LwcType Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_RemoveTranslationImplementation(IntPtr InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ConcatTranslationImplementation(IntPtr InMatrix, FVector Translation,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_ContainsNaNImplementation(IntPtr InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ScaleTranslationImplementation(IntPtr InMatrix, FVector Scale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Matrix_GetMaximumAxisScaleImplementation(IntPtr InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Matrix_ApplyScaleImplementation(IntPtr InMatrix, LwcType Scale, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetOriginImplementation(IntPtr InMatrix, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetScaledAxesImplementation(IntPtr InMatrix, out FVector X, out FVector Y,
            out FVector Z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetUnitAxesImplementation(IntPtr InMatrix, out FVector X, out FVector Y,
            out FVector Z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetAxisImplementation(IntPtr InMatrix, Int32 i, FVector Axis);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetOriginImplementation(IntPtr InMatrix, FVector NewOrigin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetAxesImplementation(IntPtr InMatrix, FVector Axis0, FVector Axis1,
            FVector Axis2, FVector Origin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetColumnImplementation(IntPtr InMatrix, Int32 i, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetColumnImplementation(IntPtr InMatrix, Int32 i, FVector Value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_RotatorImplementation(IntPtr InMatrix, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ToQuatImplementation(IntPtr InMatrix, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumNearPlaneImplementation(IntPtr InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumFarPlaneImplementation(IntPtr InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumLeftPlaneImplementation(IntPtr InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumRightPlaneImplementation(IntPtr InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumTopPlaneImplementation(IntPtr InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumBottomPlaneImplementation(IntPtr InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ToStringImplementation(IntPtr InMatrix, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Matrix_ComputeHashImplementation(IntPtr InMatrix);
    }
}