using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class VectorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_CrossProductImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_DotProductImplementation(FVector A, FVector B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_AddImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_AddBiasImplementation(FVector InVector, Single Bias, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_SubtractImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Vector_SubtractBiasImplementation(FVector InVector, Single Bias, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MultiplyImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MultiplyScaleImplementation(FVector InVector, Single Scale,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_DivideImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Vector_DivideScaleImplementation(FVector InVector, Single Scale, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_EqualityImplementation(FVector A, FVector B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_InequalityImplementation(FVector A, FVector B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_EqualsImplementation(FVector A, FVector B, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_AllComponentsEqualImplementation(FVector InVector, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_NegatedImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_GetComponentImplementation(FVector InVector, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_SetComponentImplementation(FVector InVector, Int32 InIndex, Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_ComponentImplementation(FVector InVector, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_SetImplementation(FVector InVector, Single InX, Single InY, Single InZ);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_GetMaxImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_GetAbsMaxImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_GetMinImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_GetAbsMinImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ComponentMinImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ComponentMaxImplementation(FVector A, FVector B, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetAbsImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_SizeImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_SizeSquaredImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_Size2DImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_SizeSquared2DImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsNearlyZeroImplementation(FVector InVector, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsZeroImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsUnitImplementation(FVector InVector, Single LengthSquaredTolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsNormalizedImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_NormalizeImplementation(FVector InVector, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetUnsafeNormalImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetSafeNormalImplementation(FVector InVector, Single Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetSafeNormal2DImplementation(FVector InVector, Single Tolerance,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToDirectionAndLengthImplementation(FVector InVector, out FVector OutDir,
            out Single OutLength);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetSignVectorImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ProjectionImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetUnsafeNormal2DImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GridSnapImplementation(FVector InVector, Single GridSz, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_BoundToCubeImplementation(FVector InVector, Single Radius,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_BoundToBoxImplementation(FVector InVector, FVector Min, FVector Max,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToSizeImplementation(FVector InVector, Single Min, Single Max,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToSize2DImplementation(FVector InVector, Single Min, Single Max,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToMaxSizeImplementation(FVector InVector, Single MaxSize,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_GetClampedToMaxSize2DImplementation(FVector InVector, Single MaxSize,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_AddBoundedImplementation(FVector InVector, FVector V, Single Radius);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ReciprocalImplementation(FVector InVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_IsUniformImplementation(FVector InVector, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MirrorByVectorImplementation(FVector InVector, FVector MirrorNormal,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_MirrorByPlaneImplementation(FVector InVector, FPlane Plane,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_RotateAngleAxisImplementation(FVector InVector, Single AngleDeg, FVector Axis,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_CosineAngle2DImplementation(FVector InVector, FVector B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ProjectOnToImplementation(FVector InVector, FVector A, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ProjectOnToNormalImplementation(FVector InVector, FVector Normal,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToOrientationRotatorImplementation(FVector InVector, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToOrientationQuatImplementation(FVector InVector, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_RotationImplementation(FVector InVector, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_FindBestAxisVectorsImplementation(FVector InVector, out FVector Axis1,
            out FVector Axis2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_UnwindEulerImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_ContainsNaNImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToStringImplementation(FVector InVector, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToTextImplementation(FVector InVector, out FText OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToCompactStringImplementation(FVector InVector, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_ToCompactTextImplementation(FVector InVector, out FText OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_InitFromStringImplementation(FVector InVector, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_UnitCartesianToSphericalImplementation(FVector InVector,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_HeadingAngleImplementation(FVector InVector);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_CreateOrthonormalBasisImplementation(out FVector XAxis, out FVector YAxis,
            out FVector ZAxis);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_PointsAreSameImplementation(FVector P, FVector Q);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_PointsAreNearImplementation(FVector Point1, FVector Point2, Single Dist);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_PointPlaneDistImplementation(FVector Point, FVector PlaneBase,
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
        public static extern Single Vector_DistImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_DistanceImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_DistXYImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_Dist2DImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_DistSquaredImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_DistSquaredXYImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_DistSquared2DImplementation(FVector V1, FVector V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_BoxPushOutImplementation(FVector Normal, FVector Size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_ParallelImplementation(FVector Normal1, FVector Normal2,
            Single ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_CoincidentImplementation(FVector Normal1, FVector Normal2,
            Single ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_OrthogonalImplementation(FVector Normal1, FVector Normal2,
            Single ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector_CoplanarImplementation(FVector Base1, FVector Normal1, FVector Base2,
            FVector Normal2, Single ParallelCosineThreshold);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Vector_TripleImplementation(FVector X, FVector Y, FVector Z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_RadiansToDegreesImplementation(FVector RadVector, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector_DegreesToRadiansImplementation(FVector DegVector, out FVector OutValue);
    }
}