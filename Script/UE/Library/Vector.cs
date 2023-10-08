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
    public partial class FVector
    {
        public static FVector operator ^(FVector A, FVector B)
        {
            VectorImplementation.Vector_CrossProductImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector CrossProduct(FVector A, FVector B)
        {
            VectorImplementation.Vector_CrossProductImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static LwcType operator |(FVector A, FVector B) =>
            VectorImplementation.Vector_DotProductImplementation(A.GetHandle(), B.GetHandle());

        public static LwcType DotProduct(FVector A, FVector B) =>
            VectorImplementation.Vector_DotProductImplementation(A.GetHandle(), B.GetHandle());

        public static FVector operator +(FVector A, FVector B)
        {
            VectorImplementation.Vector_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector operator +(FVector A, LwcType Bias)
        {
            VectorImplementation.Vector_AddBiasImplementation(A.GetHandle(), Bias, out var OutValue);

            return OutValue;
        }

        public static FVector operator -(FVector A, FVector B)
        {
            VectorImplementation.Vector_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector operator -(FVector A, LwcType Bias)
        {
            VectorImplementation.Vector_SubtractBiasImplementation(A.GetHandle(), Bias, out var OutValue);

            return OutValue;
        }

        public static FVector operator *(FVector A, FVector B)
        {
            VectorImplementation.Vector_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector operator *(FVector A, LwcType Scale)
        {
            VectorImplementation.Vector_MultiplyScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector operator /(FVector A, FVector B)
        {
            VectorImplementation.Vector_DivideImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector operator /(FVector A, LwcType Scale)
        {
            VectorImplementation.Vector_DivideScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FVector V, LwcType Tolerance) =>
            VectorImplementation.Vector_EqualsImplementation(GetHandle(), V.GetHandle(), Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean AllComponentsEqual(LwcType Tolerance) =>
            VectorImplementation.Vector_AllComponentsEqualImplementation(GetHandle(), Tolerance);

        public static FVector operator -(FVector A)
        {
            VectorImplementation.Vector_NegatedImplementation(A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType this[Int32 Index]
        {
            get => VectorImplementation.Vector_GetComponentImplementation(GetHandle(), Index);

            set => VectorImplementation.Vector_SetComponentImplementation(GetHandle(), Index, value);
        }

        public LwcType Component(Int32 Index) =>
            VectorImplementation.Vector_ComponentImplementation(GetHandle(), Index);

        // @TODO
        // GetComponentForAxis
        // SetComponentForAxis

        public void Set(LwcType InX, LwcType InY, LwcType InZ) =>
            VectorImplementation.Vector_SetImplementation(GetHandle(), InX, InY, InZ);

        public LwcType GetMax() =>
            VectorImplementation.Vector_GetMaxImplementation(GetHandle());

        public LwcType GetAbsMax() =>
            VectorImplementation.Vector_GetAbsMaxImplementation(GetHandle());

        public LwcType GetMin() =>
            VectorImplementation.Vector_GetMinImplementation(GetHandle());

        public LwcType GetAbsMin() =>
            VectorImplementation.Vector_GetAbsMinImplementation(GetHandle());

        public FVector ComponentMin(FVector Other)
        {
            VectorImplementation.Vector_ComponentMinImplementation(GetHandle(), Other.GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector ComponentMax(FVector Other)
        {
            VectorImplementation.Vector_ComponentMaxImplementation(GetHandle(), Other.GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetAbs()
        {
            VectorImplementation.Vector_GetAbsImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType Size() =>
            VectorImplementation.Vector_SizeImplementation(GetHandle());

        public LwcType SizeSquared() =>
            VectorImplementation.Vector_SizeSquaredImplementation(GetHandle());

        public LwcType Size2D() =>
            VectorImplementation.Vector_Size2DImplementation(GetHandle());

        public LwcType SizeSquared2D() =>
            VectorImplementation.Vector_SizeSquared2DImplementation(GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero(LwcType Tolerance) =>
            VectorImplementation.Vector_IsNearlyZeroImplementation(GetHandle(), Tolerance);

        public Boolean IsZero() =>
            VectorImplementation.Vector_IsZeroImplementation(GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsUnit(LwcType Tolerance) =>
            VectorImplementation.Vector_IsUnitImplementation(GetHandle(), Tolerance);

        public Boolean IsNormalized() =>
            VectorImplementation.Vector_IsNormalizedImplementation(GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Normalize(LwcType Tolerance) =>
            VectorImplementation.Vector_NormalizeImplementation(GetHandle(), Tolerance);

        public FVector GetUnsafeNormal()
        {
            VectorImplementation.Vector_GetUnsafeNormalImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public FVector GetSafeNormal(LwcType Tolerance)
        {
            VectorImplementation.Vector_GetSafeNormalImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public FVector GetSafeNormal2D(LwcType Tolerance)
        {
            VectorImplementation.Vector_GetSafeNormal2DImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        public void ToDirectionAndLength(out FVector OutDir, out LwcType OutLength) =>
            VectorImplementation.Vector_ToDirectionAndLengthImplementation(GetHandle(), out OutDir, out OutLength);

        public FVector GetSignVector()
        {
            VectorImplementation.Vector_GetSignVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector Projection()
        {
            VectorImplementation.Vector_ProjectionImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetUnsafeNormal2D()
        {
            VectorImplementation.Vector_GetUnsafeNormal2DImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GridSnap(LwcType GridSz)
        {
            VectorImplementation.Vector_GridSnapImplementation(GetHandle(), GridSz, out var OutValue);

            return OutValue;
        }

        public FVector BoundToCube(LwcType Radius)
        {
            VectorImplementation.Vector_BoundToCubeImplementation(GetHandle(), Radius, out var OutValue);

            return OutValue;
        }

        public FVector BoundToBox(FVector Min, FVector Max)
        {
            VectorImplementation.Vector_BoundToBoxImplementation(GetHandle(), Min, Max, out var OutValue);

            return OutValue;
        }

        public FVector GetClampedToSize(LwcType Min, LwcType Max)
        {
            VectorImplementation.Vector_GetClampedToSizeImplementation(GetHandle(), Min, Max, out var OutValue);

            return OutValue;
        }

        public FVector GetClampedToSize2D(LwcType Min, LwcType Max)
        {
            VectorImplementation.Vector_GetClampedToSize2DImplementation(GetHandle(), Min, Max, out var OutValue);

            return OutValue;
        }

        public FVector GetClampedToMaxSize(LwcType MaxSize)
        {
            VectorImplementation.Vector_GetClampedToMaxSizeImplementation(GetHandle(), MaxSize, out var OutValue);

            return OutValue;
        }

        public FVector GetClampedToMaxSize2D(LwcType MaxSize)
        {
            VectorImplementation.Vector_GetClampedToMaxSize2DImplementation(GetHandle(), MaxSize, out var OutValue);

            return OutValue;
        }

        public void AddBounded(FVector V, LwcType Radius = Int16.MaxValue) =>
            VectorImplementation.Vector_AddBoundedImplementation(GetHandle(), V, Radius);

        public FVector Reciprocal()
        {
            VectorImplementation.Vector_ReciprocalImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsUniform(LwcType Tolerance) =>
            VectorImplementation.Vector_IsUniformImplementation(GetHandle(), Tolerance);

        public FVector MirrorByVector(FVector MirrorNormal)
        {
            VectorImplementation.Vector_MirrorByVectorImplementation(GetHandle(), MirrorNormal, out var OutValue);

            return OutValue;
        }

        public FVector MirrorByPlane(FPlane Plane)
        {
            VectorImplementation.Vector_MirrorByPlaneImplementation(GetHandle(), Plane, out var OutValue);

            return OutValue;
        }

        public FVector RotateAngleAxis(LwcType AngleDeg, FVector Axis)
        {
            VectorImplementation.Vector_RotateAngleAxisImplementation(GetHandle(), AngleDeg, Axis, out var OutValue);

            return OutValue;
        }

        public LwcType CosineAngle2D(FVector B) =>
            VectorImplementation.Vector_CosineAngle2DImplementation(GetHandle(), B.GetHandle());

        public FVector ProjectOnTo(FVector A)
        {
            VectorImplementation.Vector_ProjectOnToImplementation(GetHandle(), A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector ProjectOnToNormal(FVector Normal)
        {
            VectorImplementation.Vector_ProjectOnToNormalImplementation(GetHandle(), Normal, out var OutValue);

            return OutValue;
        }

        public FRotator ToOrientationRotator()
        {
            VectorImplementation.Vector_ToOrientationRotatorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FQuat ToOrientationQuat()
        {
            VectorImplementation.Vector_ToOrientationQuatImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator Rotation()
        {
            VectorImplementation.Vector_RotationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void FindBestAxisVectors(out FVector Axis1, out FVector Axis2) =>
            VectorImplementation.Vector_FindBestAxisVectorsImplementation(GetHandle(), out Axis1, out Axis2);

        public void UnwindEuler() =>
            VectorImplementation.Vector_UnwindEulerImplementation(GetHandle());

        public Boolean ContainsNaN() =>
            VectorImplementation.Vector_ContainsNaNImplementation(GetHandle());

        public override string ToString()
        {
            VectorImplementation.Vector_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public FText ToText()
        {
            VectorImplementation.Vector_ToTextImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString ToCompactString()
        {
            VectorImplementation.Vector_ToCompactStringImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FText ToCompactText()
        {
            VectorImplementation.Vector_ToCompactTextImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Boolean InitFromString(FString InSourceString) =>
            VectorImplementation.Vector_InitFromStringImplementation(GetHandle(), InSourceString);

        public FVector2D UnitCartesianToSpherical()
        {
            VectorImplementation.Vector_UnitCartesianToSphericalImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType HeadingAngle() =>
            VectorImplementation.Vector_HeadingAngleImplementation(GetHandle());

        public static void CreateOrthonormalBasis(out FVector XAxis, out FVector YAxis, out FVector ZAxis) =>
            VectorImplementation.Vector_CreateOrthonormalBasisImplementation(out XAxis, out YAxis, out ZAxis);

        public static Boolean PointsAreSame(FVector P, FVector Q) =>
            VectorImplementation.Vector_PointsAreSameImplementation(P, Q);

        public static Boolean PointsAreNear(FVector Point1, FVector Point2, LwcType Dist) =>
            VectorImplementation.Vector_PointsAreNearImplementation(Point1, Point2, Dist);

        public static LwcType PointPlaneDist(FVector Point, FVector PlaneBase, FVector PlaneNormal) =>
            VectorImplementation.Vector_PointPlaneDistImplementation(Point, PlaneBase, PlaneNormal);

        public static FVector PointPlaneProject(FVector Point, FPlane Plane)
        {
            VectorImplementation.Vector_PointPlaneProjectByPlaneImplementation(Point, Plane, out var OutValue);

            return OutValue;
        }

        public static FVector PointPlaneProject(FVector Point, FVector A, FVector B, FVector C)
        {
            VectorImplementation.Vector_PointPlaneProjectByPointsImplementation(Point, A, B, C, out var OutValue);

            return OutValue;
        }

        public static FVector PointPlaneProject(FVector Point, FVector PlaneBase, FVector PlaneNormal)
        {
            VectorImplementation.Vector_PointPlaneProjectByPlaneBaseAndPlaneNormalImplementation(Point, PlaneBase,
                PlaneNormal, out var OutValue);

            return OutValue;
        }

        public static FVector VectorPlaneProject(FVector V, FVector PlaneNormal)
        {
            VectorImplementation.Vector_VectorPlaneProjectImplementation(V, PlaneNormal, out var OutValue);

            return OutValue;
        }

        public static LwcType Dist(FVector V1, FVector V2) =>
            VectorImplementation.Vector_DistImplementation(V1, V2);

        public static LwcType Distance(FVector V1, FVector V2) =>
            VectorImplementation.Vector_DistanceImplementation(V1, V2);

        public static LwcType DistXY(FVector V1, FVector V2) =>
            VectorImplementation.Vector_DistXYImplementation(V1, V2);

        public static LwcType Dist2D(FVector V1, FVector V2) =>
            VectorImplementation.Vector_Dist2DImplementation(V1, V2);

        public static LwcType DistSquared(FVector V1, FVector V2) =>
            VectorImplementation.Vector_DistSquaredImplementation(V1, V2);

        public static LwcType DistSquaredXY(FVector V1, FVector V2) =>
            VectorImplementation.Vector_DistSquaredXYImplementation(V1, V2);

        public static LwcType DistSquared2D(FVector V1, FVector V2) =>
            VectorImplementation.Vector_DistSquared2DImplementation(V1, V2);

        public static LwcType BoxPushOut(FVector Normal, FVector Size) =>
            VectorImplementation.Vector_BoxPushOutImplementation(Normal, Size);

        // @TODO THRESH_NORMALS_ARE_PARALLEL
        public static Boolean Parallel(FVector Normal1, FVector Normal2, LwcType ParallelCosineThreshold) =>
            VectorImplementation.Vector_ParallelImplementation(Normal1, Normal2, ParallelCosineThreshold);

        // @TODO THRESH_NORMALS_ARE_PARALLEL
        public static Boolean Coincident(FVector Normal1, FVector Normal2, LwcType ParallelCosineThreshold) =>
            VectorImplementation.Vector_CoincidentImplementation(Normal1, Normal2, ParallelCosineThreshold);

        // @TODO THRESH_NORMALS_ARE_PARALLEL
        public static Boolean Orthogonal(FVector Normal1, FVector Normal2, LwcType ParallelCosineThreshold) =>
            VectorImplementation.Vector_OrthogonalImplementation(Normal1, Normal2, ParallelCosineThreshold);

        // @TODO THRESH_NORMALS_ARE_PARALLEL
        public static Boolean Coplanar(FVector Base1, FVector Normal1, FVector Base2, FVector Normal2,
            LwcType ParallelCosineThreshold) =>
            VectorImplementation.Vector_CoplanarImplementation(Base1, Normal1, Base2, Normal2, ParallelCosineThreshold);

        public static LwcType Triple(FVector X, FVector Y, FVector Z) =>
            VectorImplementation.Vector_TripleImplementation(X, Y, Z);

        // @TODO
        // EvaluateBezier

        public static FVector RadiansToDegrees(FVector RadVector)
        {
            VectorImplementation.Vector_RadiansToDegreesImplementation(RadVector, out var OutValue);

            return OutValue;
        }

        public static FVector DegreesToRadians(FVector DegVector)
        {
            VectorImplementation.Vector_DegreesToRadiansImplementation(DegVector, out var OutValue);

            return OutValue;
        }

        // @TODO
        // GenerateClusterCenters
    }
}