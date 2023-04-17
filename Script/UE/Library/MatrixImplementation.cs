using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class MatrixImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Matrix_GetMImplementation(FMatrix InMatrix, UInt32 InRow, UInt32 InColumn);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetMImplementation(FMatrix InMatrix, UInt32 InRow, UInt32 InColumn,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetIdentityImplementation(FMatrix InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_MultiplyImplementation(FMatrix A, FMatrix B, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_AddImplementation(FMatrix A, FMatrix B, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_MultiplyScaleImplementation(FMatrix InMatrix, Single Other,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_EqualityImplementation(FMatrix A, FMatrix B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_EqualsImplementation(FMatrix A, FMatrix B, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_InequalityImplementation(FMatrix A, FMatrix B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransformFVector4Implementation(FMatrix InMatrix, FVector4 V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransformPositionImplementation(FMatrix InMatrix, FVector V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseTransformPositionImplementation(FMatrix InMatrix, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransformVectorImplementation(FMatrix InMatrix, FVector V,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseTransformVectorImplementation(FMatrix InMatrix, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetTransposedImplementation(FMatrix InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Matrix_DeterminantImplementation(FMatrix InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Matrix_RotDeterminantImplementation(FMatrix InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseFastImplementation(FMatrix InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_InverseImplementation(FMatrix InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_TransposeAdjointImplementation(FMatrix InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_RemoveScalingImplementation(FMatrix InMatrix, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetMatrixWithoutScaleImplementation(FMatrix InMatrix, Single Tolerance,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ExtractScalingImplementation(FMatrix InMatrix, Single Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetScaleVectorImplementation(FMatrix InMatrix, Single Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_RemoveTranslationImplementation(FMatrix InMatrix, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ConcatTranslationImplementation(FMatrix InMatrix, FVector Translation,
            out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_ContainsNaNImplementation(FMatrix InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ScaleTranslationImplementation(FMatrix InMatrix, FVector Scale3D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Matrix_GetMaximumAxisScaleImplementation(FMatrix InMatrix);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ApplyScaleImplementation(FMatrix InMatrix, Single Scale, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetOriginImplementation(FMatrix InMatrix, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetScaledAxesImplementation(FMatrix InMatrix, out FVector X, out FVector Y,
            out FVector Z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetUnitAxesImplementation(FMatrix InMatrix, out FVector X, out FVector Y,
            out FVector Z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetAxisImplementation(FMatrix InMatrix, Int32 i, FVector Axis);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetOriginImplementation(FMatrix InMatrix, FVector NewOrigin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetAxesImplementation(FMatrix InMatrix, FVector Axis0, FVector Axis1,
            FVector Axis2, FVector Origin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_GetColumnImplementation(FMatrix InMatrix, Int32 i, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_SetColumnImplementation(FMatrix InMatrix, Int32 i, FVector Value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_RotatorImplementation(FMatrix InMatrix, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ToQuatImplementation(FMatrix InMatrix, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumNearPlaneImplementation(FMatrix InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumFarPlaneImplementation(FMatrix InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumLeftPlaneImplementation(FMatrix InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumRightPlaneImplementation(FMatrix InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumTopPlaneImplementation(FMatrix InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Matrix_GetFrustumBottomPlaneImplementation(FMatrix InMatrix, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Matrix_ToStringImplementation(FMatrix InMatrix, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Matrix_ComputeHashImplementation(FMatrix InMatrix);
    }
}