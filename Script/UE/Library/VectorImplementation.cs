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
    public static class VectorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_CrossProductImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DotProductImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_AddImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_AddBiasImplementation(IntPtr InVector, LwcType Bias, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_SubtractImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Vector_SubtractBiasImplementation(IntPtr InVector, LwcType Bias, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MultiplyImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MultiplyScaleImplementation(IntPtr InVector, LwcType Scale,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_DivideImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Vector_DivideScaleImplementation(IntPtr InVector, LwcType Scale, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_EqualsImplementation(IntPtr A, IntPtr B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_AllComponentsEqualImplementation(IntPtr InVector, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_NegatedImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_GetComponentImplementation(IntPtr InVector, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_SetComponentImplementation(IntPtr InVector, Int32 InIndex, LwcType InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_ComponentImplementation(IntPtr InVector, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_SetImplementation(IntPtr InVector, LwcType InX, LwcType InY, LwcType InZ);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_GetMaxImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_GetAbsMaxImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_GetMinImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_GetAbsMinImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ComponentMinImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ComponentMaxImplementation(IntPtr A, IntPtr B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetAbsImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_SizeImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_SizeSquaredImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_Size2DImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_SizeSquared2DImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsNearlyZeroImplementation(IntPtr InVector, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsZeroImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsUnitImplementation(IntPtr InVector, LwcType LengthSquaredTolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsNormalizedImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_NormalizeImplementation(IntPtr InVector, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetUnsafeNormalImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetSafeNormalImplementation(IntPtr InVector, LwcType Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetSafeNormal2DImplementation(IntPtr InVector, LwcType Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToDirectionAndLengthImplementation(IntPtr InVector, out FVector OutDir,
            out LwcType OutLength);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetSignVectorImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ProjectionImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetUnsafeNormal2DImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GridSnapImplementation(IntPtr InVector, LwcType GridSz, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_BoundToCubeImplementation(IntPtr InVector, LwcType Radius,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_BoundToBoxImplementation(IntPtr InVector, FVector Min, FVector Max,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToSizeImplementation(IntPtr InVector, LwcType Min, LwcType Max,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToSize2DImplementation(IntPtr InVector, LwcType Min, LwcType Max,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToMaxSizeImplementation(IntPtr InVector, LwcType MaxSize,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToMaxSize2DImplementation(IntPtr InVector, LwcType MaxSize,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_AddBoundedImplementation(IntPtr InVector, FVector V, LwcType Radius);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ReciprocalImplementation(IntPtr InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsUniformImplementation(IntPtr InVector, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MirrorByVectorImplementation(IntPtr InVector, FVector MirrorNormal,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MirrorByPlaneImplementation(IntPtr InVector, FPlane Plane,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_RotateAngleAxisImplementation(IntPtr InVector, LwcType AngleDeg, FVector Axis,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_CosineAngle2DImplementation(IntPtr InVector, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ProjectOnToImplementation(IntPtr InVector, IntPtr A, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ProjectOnToNormalImplementation(IntPtr InVector, FVector Normal,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToOrientationRotatorImplementation(IntPtr InVector, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToOrientationQuatImplementation(IntPtr InVector, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_RotationImplementation(IntPtr InVector, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_FindBestAxisVectorsImplementation(IntPtr InVector, out FVector Axis1,
            out FVector Axis2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_UnwindEulerImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_ContainsNaNImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToStringImplementation(IntPtr InVector, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToTextImplementation(IntPtr InVector, out FText OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToCompactStringImplementation(IntPtr InVector, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToCompactTextImplementation(IntPtr InVector, out FText OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_InitFromStringImplementation(IntPtr InVector, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_UnitCartesianToSphericalImplementation(IntPtr InVector,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_HeadingAngleImplementation(IntPtr InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_CreateOrthonormalBasisImplementation(out FVector XAxis, out FVector YAxis,
            out FVector ZAxis);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_PointsAreSameImplementation(FVector P, FVector Q);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_PointsAreNearImplementation(FVector Point1, FVector Point2, LwcType Dist);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_PointPlaneDistImplementation(FVector Point, FVector PlaneBase,
            FVector PlaneNormal);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_PointPlaneProjectByPlaneImplementation(FVector Point, FPlane Plane,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_PointPlaneProjectByPointsImplementation(FVector Point, FVector A, FVector B,
            FVector C, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_PointPlaneProjectByPlaneBaseAndPlaneNormalImplementation(FVector Point,
            FVector PlaneBase, FVector PlaneNormal, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_VectorPlaneProjectImplementation(FVector V, FVector PlaneNormal,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DistImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DistanceImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DistXYImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_Dist2DImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DistSquaredImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DistSquaredXYImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_DistSquared2DImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_BoxPushOutImplementation(FVector Normal, FVector Size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_ParallelImplementation(FVector Normal1, FVector Normal2,
            LwcType ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_CoincidentImplementation(FVector Normal1, FVector Normal2,
            LwcType ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_OrthogonalImplementation(FVector Normal1, FVector Normal2,
            LwcType ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_CoplanarImplementation(FVector Base1, FVector Normal1, FVector Base2,
            FVector Normal2, LwcType ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector_TripleImplementation(FVector X, FVector Y, FVector Z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_RadiansToDegreesImplementation(FVector RadVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_DegreesToRadiansImplementation(FVector DegVector, out FVector OutValue);
    }
}