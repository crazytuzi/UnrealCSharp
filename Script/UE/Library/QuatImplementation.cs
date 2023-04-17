using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class QuatImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_AddImplementation(FQuat A, FQuat B, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SubtractImplementation(FQuat A, FQuat B, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_EqualsImplementation(FQuat A, FQuat B, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_IsIdentityImplementation(FQuat InQuat, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyImplementation(FQuat A, FQuat B, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyVectorImplementation(FQuat A, FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyMatrixImplementation(FQuat A, FMatrix M, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyScaleImplementation(FQuat InQuat, Single Scale, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_DivideImplementation(FQuat InQuat, Single Scale, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_IdenticalImplementation(FQuat InQuat, FQuat Q, UInt32 PortFlags);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_EqualityImplementation(FQuat A, FQuat B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_InequalityImplementation(FQuat A, FQuat B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_DotProductImplementation(FQuat A, FQuat B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MakeFromEulerImplementation(FVector Euler, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_EulerImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_NormalizeImplementation(FQuat InQuat, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetNormalizedImplementation(FQuat InQuat, Single Tolerance, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_IsNormalizedImplementation(FQuat InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_SizeImplementation(FQuat InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_SizeSquaredImplementation(FQuat InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_GetAngleImplementation(FQuat InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ToAxisAndAngleImplementation(FQuat InQuat, out FVector Axis, out Single Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ToSwingTwistImplementation(FQuat InQuat, FVector InTwistAxis, out FQuat OutSwing,
            out FQuat OutTwist);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_GetTwistAngleImplementation(FQuat InQuat, FVector TwistAxis);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_RotateVectorImplementation(FQuat InQuat, FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_UnrotateVectorImplementation(FQuat InQuat, FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_LogImplementation(FQuat InQuat, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ExpImplementation(FQuat InQuat, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_InverseImplementation(FQuat InQuat, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_EnforceShortestArcWithImplementation(FQuat InQuat, FQuat OtherQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetAxisXImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetAxisYImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetAxisZImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetForwardVectorImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetRightVectorImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetUpVectorImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_VectorImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_RotatorImplementation(FQuat InQuat, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetRotationAxisImplementation(FQuat InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_AngularDistanceImplementation(FQuat InQuat, FQuat Q);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_ContainsNaNImplementation(FQuat InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ToStringImplementation(FQuat InQuat, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_InitFromStringImplementation(FQuat InQuat, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FindBetweenImplementation(FVector Vector1, FVector Vector2, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FindBetweenNormalsImplementation(FVector Normal1, FVector Normal2,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FindBetweenVectorsImplementation(FVector Vector1, FVector Vector2,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_ErrorImplementation(FQuat Q1, FQuat Q2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Quat_ErrorAutoNormalizeImplementation(FQuat A, FQuat B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FastLerpImplementation(FQuat A, FQuat B, Single Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FastBilerpImplementation(FQuat P00, FQuat P10, FQuat P01, FQuat P11,
            Single FracX, Single FracY, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_Slerp_NotNormalizedImplementation(FQuat Quat1, FQuat Quat2, Single Slerp,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SlerpImplementation(FQuat Quat1, FQuat Quat2, Single Slerp, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SlerpFullPath_NotNormalizedImplementation(FQuat quat1, FQuat quat2, Single Alpha,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SlerpFullPathImplementation(FQuat quat1, FQuat quat2, Single Alpha,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SquadImplementation(FQuat quat1, FQuat tang1, FQuat quat2, FQuat tang2,
            Single Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SquadFullPathImplementation(FQuat quat1, FQuat tang1, FQuat quat2, FQuat tang2,
            Single Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_CalcTangentsImplementation(FQuat PrevP, FQuat P, FQuat NextP, Single Tension,
            out FQuat OutTan);
    }
}