using System;
using Script.Library;
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
            PlaneImplementation.Plane_IsValidImplementation(GetHandle());

        public FVector GetOrigin()
        {
            PlaneImplementation.Plane_GetOriginImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetNormal()
        {
            PlaneImplementation.Plane_GetNormalImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType PlaneDot(FVector P) =>
            PlaneImplementation.Plane_PlaneDotImplementation(GetHandle(), P);

        // @TODO SMALL_NUMBER
        public new Boolean Normalize(LwcType Tolerance) =>
            PlaneImplementation.Plane_NormalizeImplementation(GetHandle(), Tolerance);

        public FPlane Flip()
        {
            PlaneImplementation.Plane_FlipImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FPlane TransformBy(FMatrix M)
        {
            PlaneImplementation.Plane_TransformByImplementation(GetHandle(), M, out var OutValue);

            return OutValue;
        }

        public FPlane TransformByUsingAdjointT(FMatrix M, LwcType DetM, FMatrix TA)
        {
            PlaneImplementation.Plane_TransformByUsingAdjointTImplementation(GetHandle(), M, DetM, TA,
                out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FPlane A, FPlane B) =>
            PlaneImplementation.Plane_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FPlane A, FPlane B) =>
            PlaneImplementation.Plane_InequalityImplementation(A.GetHandle(), B.GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FPlane V, LwcType Tolerance) =>
            PlaneImplementation.Plane_EqualsImplementation(GetHandle(), V, Tolerance);

        public static LwcType operator |(FPlane A, FPlane B) =>
            PlaneImplementation.Plane_DotProductImplementation(A.GetHandle(), B.GetHandle());

        public static FPlane operator +(FPlane A, FPlane B)
        {
            PlaneImplementation.Plane_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FPlane operator -(FPlane A, FPlane B)
        {
            PlaneImplementation.Plane_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FPlane operator /(FPlane A, LwcType Scale)
        {
            PlaneImplementation.Plane_DivideImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FPlane operator *(FPlane A, LwcType Scale)
        {
            PlaneImplementation.Plane_MultiplyImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }
    }
}