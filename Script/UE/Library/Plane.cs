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
    public partial class FPlane
    {
        public Boolean IsValid() =>
            PlaneImplementation.Plane_IsValidImplementation(this);

        public FVector GetOrigin()
        {
            PlaneImplementation.Plane_GetOriginImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetNormal()
        {
            PlaneImplementation.Plane_GetNormalImplementation(this, out var OutValue);

            return OutValue;
        }

        public LwcType PlaneDot(FVector P) =>
            PlaneImplementation.Plane_PlaneDotImplementation(this, P);

        // @TODO SMALL_NUMBER
        public new Boolean Normalize(LwcType Tolerance) =>
            PlaneImplementation.Plane_NormalizeImplementation(this, Tolerance);

        public FPlane Flip()
        {
            PlaneImplementation.Plane_FlipImplementation(this, out var OutValue);

            return OutValue;
        }

        public FPlane TransformBy(FMatrix M)
        {
            PlaneImplementation.Plane_TransformByImplementation(this, M, out var OutValue);

            return OutValue;
        }

        public FPlane TransformByUsingAdjointT(FMatrix M, LwcType DetM, FMatrix TA)
        {
            PlaneImplementation.Plane_TransformByUsingAdjointTImplementation(this, M, DetM, TA, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FPlane A, FPlane B) =>
            PlaneImplementation.Plane_EqualityImplementation(A, B);

        public static Boolean operator !=(FPlane A, FPlane B) =>
            PlaneImplementation.Plane_InequalityImplementation(A, B);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FPlane V, LwcType Tolerance) =>
            PlaneImplementation.Plane_EqualsImplementation(this, V, Tolerance);

        public static LwcType operator |(FPlane A, FPlane B) =>
            PlaneImplementation.Plane_DotProductImplementation(A, B);

        public static FPlane operator +(FPlane A, FPlane B)
        {
            PlaneImplementation.Plane_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FPlane operator -(FPlane A, FPlane B)
        {
            PlaneImplementation.Plane_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FPlane operator /(FPlane A, LwcType Scale)
        {
            PlaneImplementation.Plane_DivideImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FPlane operator *(FPlane A, LwcType Scale)
        {
            PlaneImplementation.Plane_MultiplyImplementation(A, Scale, out var OutValue);

            return OutValue;
        }
    }
}