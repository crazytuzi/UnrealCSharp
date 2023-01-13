using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FQuat
    {
        public static FQuat operator +(FQuat A, FQuat B)
        {
            QuatImplementation.Quat_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FQuat operator -(FQuat A, FQuat B)
        {
            QuatImplementation.Quat_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FQuat Q, Single Tolerance) =>
            QuatImplementation.Quat_EqualsImplementation(this, Q, Tolerance);

        // @TODO SMALL_NUMBER
        public Boolean IsIdentity(Single Tolerance) =>
            QuatImplementation.Quat_IsIdentityImplementation(this, Tolerance);

        public static FQuat operator *(FQuat A, FQuat B)
        {
            QuatImplementation.Quat_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector operator *(FQuat A, FVector V)
        {
            QuatImplementation.Quat_MultiplyVectorImplementation(A, V, out var OutValue);

            return OutValue;
        }

        public static FMatrix operator *(FQuat A, FMatrix M)
        {
            QuatImplementation.Quat_MultiplyMatrixImplementation(A, M, out var OutValue);

            return OutValue;
        }

        public static FQuat operator *(FQuat A, Single Scale)
        {
            QuatImplementation.Quat_MultiplyScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FQuat operator /(FQuat A, Single Scale)
        {
            QuatImplementation.Quat_DivideImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public Boolean Identical(FQuat Q, UInt32 PortFlags) =>
            QuatImplementation.Quat_IdenticalImplementation(this, Q, PortFlags);

        public static Boolean operator ==(FQuat A, FQuat B) =>
            QuatImplementation.Quat_EqualityImplementation(A, B);

        public static Boolean operator !=(FQuat A, FQuat B) =>
            QuatImplementation.Quat_InequalityImplementation(A, B);

        public static Single operator |(FQuat A, FQuat B) =>
            QuatImplementation.Quat_DotProductImplementation(A, B);

        public static FQuat MakeFromEuler(FVector Euler)
        {
            QuatImplementation.Quat_MakeFromEulerImplementation(Euler, out var OutValue);

            return OutValue;
        }

        public FVector Euler()
        {
            QuatImplementation.Quat_EulerImplementation(this, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void Normalize(Single Tolerance) =>
            QuatImplementation.Quat_NormalizeImplementation(this, Tolerance);

        // @TODO SMALL_NUMBER
        public FQuat GetNormalized(Single Tolerance)
        {
            QuatImplementation.Quat_GetNormalizedImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        public Boolean IsNormalized() =>
            QuatImplementation.Quat_IsNormalizedImplementation(this);

        public Single Size() =>
            QuatImplementation.Quat_SizeImplementation(this);

        public Single SizeSquared() =>
            QuatImplementation.Quat_SizeSquaredImplementation(this);

        public Single GetAngle() =>
            QuatImplementation.Quat_GetAngleImplementation(this);

        public void ToAxisAndAngle(out FVector Axis, out Single Angle) =>
            QuatImplementation.Quat_ToAxisAndAngleImplementation(this, out Axis, out Angle);

        public void ToSwingTwist(FVector InTwistAxis, out FQuat OutSwing, out FQuat OutTwist) =>
            QuatImplementation.Quat_ToSwingTwistImplementation(this, InTwistAxis, out OutSwing, out OutTwist);

        public Single GetTwistAngle(FVector TwistAxis) =>
            QuatImplementation.Quat_GetTwistAngleImplementation(this, TwistAxis);

        public FVector RotateVector(FVector V)
        {
            QuatImplementation.Quat_RotateVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector UnrotateVector(FVector V)
        {
            QuatImplementation.Quat_UnrotateVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FQuat Log()
        {
            QuatImplementation.Quat_LogImplementation(this, out var OutValue);

            return OutValue;
        }

        public FQuat Exp()
        {
            QuatImplementation.Quat_ExpImplementation(this, out var OutValue);

            return OutValue;
        }

        public FQuat Inverse()
        {
            QuatImplementation.Quat_InverseImplementation(this, out var OutValue);

            return OutValue;
        }

        public void EnforceShortestArcWith(FQuat OtherQuat) =>
            QuatImplementation.Quat_EnforceShortestArcWithImplementation(this, OtherQuat);

        public FVector GetAxisX()
        {
            QuatImplementation.Quat_GetAxisXImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetAxisY()
        {
            QuatImplementation.Quat_GetAxisYImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetAxisZ()
        {
            QuatImplementation.Quat_GetAxisZImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetForwardVector()
        {
            QuatImplementation.Quat_GetForwardVectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetRightVector()
        {
            QuatImplementation.Quat_GetRightVectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetUpVector()
        {
            QuatImplementation.Quat_GetUpVectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector Vector()
        {
            QuatImplementation.Quat_VectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator Rotator()
        {
            QuatImplementation.Quat_RotatorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector GetRotationAxis()
        {
            QuatImplementation.Quat_GetRotationAxisImplementation(this, out var OutValue);

            return OutValue;
        }

        public Single AngularDistance(FQuat Q) =>
            QuatImplementation.Quat_AngularDistanceImplementation(this, Q);

        public Boolean ContainsNaN() =>
            QuatImplementation.Quat_ContainsNaNImplementation(this);

        public FString ToString()
        {
            QuatImplementation.Quat_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public Boolean InitFromString(FString InSourceString) =>
            QuatImplementation.Quat_InitFromStringImplementation(this, InSourceString);

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

        public static Single Error(FQuat Q1, FQuat Q2) =>
            QuatImplementation.Quat_ErrorImplementation(Q1, Q2);

        public static Single ErrorAutoNormalize(FQuat Q1, FQuat Q2) =>
            QuatImplementation.Quat_ErrorAutoNormalizeImplementation(Q1, Q2);

        public static FQuat FastLerp(FQuat A, FQuat B, Single Alpha)
        {
            QuatImplementation.Quat_FastLerpImplementation(A, B, Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat FastBilerp(FQuat P00, FQuat P10, FQuat P01, FQuat P11, Single FracX, Single FracY)
        {
            QuatImplementation.Quat_FastBilerpImplementation(P00, P10, P01, P11, FracX, FracY, out var OutValue);

            return OutValue;
        }

        public static FQuat Slerp_NotNormalized(FQuat Quat1, FQuat Quat2, Single Slerp)
        {
            QuatImplementation.Quat_Slerp_NotNormalizedImplementation(Quat1, Quat2, Slerp, out var OutValue);

            return OutValue;
        }

        public static FQuat Slerp(FQuat Quat1, FQuat Quat2, Single Slerp)
        {
            QuatImplementation.Quat_SlerpImplementation(Quat1, Quat2, Slerp, out var OutValue);

            return OutValue;
        }

        public static FQuat SlerpFullPath_NotNormalized(FQuat quat1, FQuat quat2, Single Alpha)
        {
            QuatImplementation.Quat_SlerpFullPath_NotNormalizedImplementation(quat1, quat2, Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat SlerpFullPath(FQuat quat1, FQuat quat2, Single Alpha)
        {
            QuatImplementation.Quat_SlerpFullPathImplementation(quat1, quat2, Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat Squad(FQuat quat1, FQuat tang1, FQuat quat2, FQuat tang2, Single Alpha)
        {
            QuatImplementation.Quat_SquadImplementation(quat1, tang1, quat2, tang2, Alpha, out var OutValue);

            return OutValue;
        }

        public static FQuat SquadFullPath(FQuat quat1, FQuat tang1, FQuat quat2, FQuat tang2, Single Alpha)
        {
            QuatImplementation.Quat_SquadFullPathImplementation(quat1, tang1, quat2, tang2, Alpha, out var OutValue);

            return OutValue;
        }

        public static void Quat_CalcTangentsImplementation(FQuat PrevP, FQuat P, FQuat NextP, Single Tension,
            out FQuat OutTan) =>
            QuatImplementation.Quat_CalcTangentsImplementation(PrevP, P, NextP, Tension, out OutTan);
    }
}