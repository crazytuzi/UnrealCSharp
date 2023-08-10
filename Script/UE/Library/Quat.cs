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
    public partial class FQuat
    {
        public static FQuat operator +(FQuat A, FQuat B)
        {
            QuatImplementation.Quat_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FQuat operator -(FQuat A, FQuat B)
        {
            QuatImplementation.Quat_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FQuat Q, LwcType Tolerance) =>
            QuatImplementation.Quat_EqualsImplementation(GetHandle(), Q.GetHandle(), Tolerance);

        // @TODO SMALL_NUMBER
        public Boolean IsIdentity(LwcType Tolerance) =>
            QuatImplementation.Quat_IsIdentityImplementation(GetHandle(), Tolerance);

        public static FQuat operator *(FQuat A, FQuat B)
        {
            QuatImplementation.Quat_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector operator *(FQuat A, FVector V)
        {
            QuatImplementation.Quat_MultiplyVectorImplementation(A.GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public static FMatrix operator *(FQuat A, FMatrix M)
        {
            QuatImplementation.Quat_MultiplyMatrixImplementation(A.GetHandle(), M, out var OutValue);

            return OutValue;
        }

        public static FQuat operator *(FQuat A, LwcType Scale)
        {
            QuatImplementation.Quat_MultiplyScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FQuat operator /(FQuat A, LwcType Scale)
        {
            QuatImplementation.Quat_DivideImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public Boolean Identical(FQuat Q, UInt32 PortFlags) =>
            QuatImplementation.Quat_IdenticalImplementation(GetHandle(), Q, PortFlags);

        public static Boolean operator ==(FQuat A, FQuat B) =>
            QuatImplementation.Quat_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FQuat A, FQuat B) =>
            QuatImplementation.Quat_InequalityImplementation(A.GetHandle(), B.GetHandle());

        public static LwcType operator |(FQuat A, FQuat B) =>
            QuatImplementation.Quat_DotProductImplementation(A.GetHandle(), B.GetHandle());

        public static FQuat MakeFromEuler(FVector Euler)
        {
            QuatImplementation.Quat_MakeFromEulerImplementation(Euler, out var OutValue);

            return OutValue;
        }

        public FVector Euler()
        {
            QuatImplementation.Quat_EulerImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void Normalize(LwcType Tolerance) =>
            QuatImplementation.Quat_NormalizeImplementation(GetHandle(), Tolerance);

        // @TODO SMALL_NUMBER
        public FQuat GetNormalized(LwcType Tolerance)
        {
            QuatImplementation.Quat_GetNormalizedImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        public Boolean IsNormalized() =>
            QuatImplementation.Quat_IsNormalizedImplementation(GetHandle());

        public LwcType Size() =>
            QuatImplementation.Quat_SizeImplementation(GetHandle());

        public LwcType SizeSquared() =>
            QuatImplementation.Quat_SizeSquaredImplementation(GetHandle());

        public LwcType GetAngle() =>
            QuatImplementation.Quat_GetAngleImplementation(GetHandle());

        public void ToAxisAndAngle(out FVector Axis, out LwcType Angle) =>
            QuatImplementation.Quat_ToAxisAndAngleImplementation(GetHandle(), out Axis, out Angle);

        public void ToSwingTwist(FVector InTwistAxis, out FQuat OutSwing, out FQuat OutTwist) =>
            QuatImplementation.Quat_ToSwingTwistImplementation(GetHandle(), InTwistAxis, out OutSwing, out OutTwist);

        public LwcType GetTwistAngle(FVector TwistAxis) =>
            QuatImplementation.Quat_GetTwistAngleImplementation(GetHandle(), TwistAxis);

        public FVector RotateVector(FVector V)
        {
            QuatImplementation.Quat_RotateVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector UnrotateVector(FVector V)
        {
            QuatImplementation.Quat_UnrotateVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FQuat Log()
        {
            QuatImplementation.Quat_LogImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FQuat Exp()
        {
            QuatImplementation.Quat_ExpImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FQuat Inverse()
        {
            QuatImplementation.Quat_InverseImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void EnforceShortestArcWith(FQuat OtherQuat) =>
            QuatImplementation.Quat_EnforceShortestArcWithImplementation(GetHandle(), OtherQuat);

        public FVector GetAxisX()
        {
            QuatImplementation.Quat_GetAxisXImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetAxisY()
        {
            QuatImplementation.Quat_GetAxisYImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetAxisZ()
        {
            QuatImplementation.Quat_GetAxisZImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetForwardVector()
        {
            QuatImplementation.Quat_GetForwardVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetRightVector()
        {
            QuatImplementation.Quat_GetRightVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetUpVector()
        {
            QuatImplementation.Quat_GetUpVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector Vector()
        {
            QuatImplementation.Quat_VectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator Rotator()
        {
            QuatImplementation.Quat_RotatorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector GetRotationAxis()
        {
            QuatImplementation.Quat_GetRotationAxisImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType AngularDistance(FQuat Q) =>
            QuatImplementation.Quat_AngularDistanceImplementation(GetHandle(), Q);

        public Boolean ContainsNaN() =>
            QuatImplementation.Quat_ContainsNaNImplementation(GetHandle());

        public override string ToString()
        {
            QuatImplementation.Quat_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            QuatImplementation.Quat_InitFromStringImplementation(GetHandle(), InSourceString);

        public static FQuat FindBetween(FVector Vector1, FVector Vector2)
        {
            QuatImplementation.Quat_FindBetweenImplementation(Vector1, Vector2, out var OutValue);

            return OutValue;
        }

        public static FQuat FindBetweenNormals(FVector Normal1, FVector Normal2)
        {
            QuatImplementation.Quat_FindBetweenNormalsImplementation(Normal1, Normal2, out var OutValue);

            return OutValue;
        }

        public static FQuat FindBetweenVectors(FVector Vector1, FVector Vector2)
        {
            QuatImplementation.Quat_FindBetweenVectorsImplementation(Vector1, Vector2, out var OutValue);

            return OutValue;
        }

        public static LwcType Error(FQuat Q1, FQuat Q2) =>
            QuatImplementation.Quat_ErrorImplementation(Q1.GetHandle(), Q2.GetHandle());

        public static LwcType ErrorAutoNormalize(FQuat Q1, FQuat Q2) =>
            QuatImplementation.Quat_ErrorAutoNormalizeImplementation(Q1.GetHandle(), Q2.GetHandle());

        public static FQuat FastLerp(FQuat A, FQuat B, LwcType Alpha)
        {
            QuatImplementation.Quat_FastLerpImplementation(A.GetHandle(), B.GetHandle(), Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat FastBilerp(FQuat P00, FQuat P10, FQuat P01, FQuat P11, LwcType FracX, LwcType FracY)
        {
            QuatImplementation.Quat_FastBilerpImplementation(P00.GetHandle(), P10.GetHandle(), P01.GetHandle(),
                P11.GetHandle(), FracX, FracY, out var OutValue);

            return OutValue;
        }

        public static FQuat Slerp_NotNormalized(FQuat Quat1, FQuat Quat2, LwcType Slerp)
        {
            QuatImplementation.Quat_Slerp_NotNormalizedImplementation(Quat1.GetHandle(), Quat2.GetHandle(), Slerp,
                out var OutValue);

            return OutValue;
        }

        public static FQuat Slerp(FQuat Quat1, FQuat Quat2, LwcType Slerp)
        {
            QuatImplementation.Quat_SlerpImplementation(Quat1.GetHandle(), Quat2.GetHandle(), Slerp, out var OutValue);

            return OutValue;
        }

        public static FQuat SlerpFullPath_NotNormalized(FQuat quat1, FQuat quat2, LwcType Alpha)
        {
            QuatImplementation.Quat_SlerpFullPath_NotNormalizedImplementation(quat1.GetHandle(), quat2.GetHandle(),
                Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat SlerpFullPath(FQuat quat1, FQuat quat2, LwcType Alpha)
        {
            QuatImplementation.Quat_SlerpFullPathImplementation(quat1.GetHandle(), quat2.GetHandle(), Alpha,
                out var OutValue);

            return OutValue;
        }

        public static FQuat Squad(FQuat quat1, FQuat tang1, FQuat quat2, FQuat tang2, LwcType Alpha)
        {
            QuatImplementation.Quat_SquadImplementation(quat1.GetHandle(), tang1.GetHandle(), quat2.GetHandle(),
                tang2.GetHandle(), Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat SquadFullPath(FQuat quat1, FQuat tang1, FQuat quat2, FQuat tang2, LwcType Alpha)
        {
            QuatImplementation.Quat_SquadFullPathImplementation(quat1.GetHandle(), tang1.GetHandle(), quat2.GetHandle(),
                tang2.GetHandle(), Alpha, out var OutValue);

            return OutValue;
        }

        public static void Quat_CalcTangentsImplementation(FQuat PrevP, FQuat P, FQuat NextP, LwcType Tension,
            out FQuat OutTan) =>
            QuatImplementation.Quat_CalcTangentsImplementation(PrevP.GetHandle(), P.GetHandle(), NextP.GetHandle(),
                Tension, out OutTan);
    }
}