using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;
#if UE_5_0_OR_LATER
using LwcType = System.Double;
#else
using LwcType = System.Single;
#endif

namespace Script.Library
{
    public static class QuatImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_AddImplementation(IntPtr A, IntPtr B, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SubtractImplementation(IntPtr A, IntPtr B, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_EqualsImplementation(IntPtr A, IntPtr B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_IsIdentityImplementation(IntPtr InQuat, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyImplementation(IntPtr A, IntPtr B, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyVectorImplementation(IntPtr A, FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyMatrixImplementation(IntPtr A, FMatrix M, out FMatrix OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MultiplyScaleImplementation(IntPtr InQuat, LwcType Scale, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_DivideImplementation(IntPtr InQuat, LwcType Scale, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_IdenticalImplementation(IntPtr InQuat, FQuat Q, UInt32 PortFlags);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_DotProductImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_MakeFromEulerImplementation(FVector Euler, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_EulerImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_NormalizeImplementation(IntPtr InQuat, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            Quat_GetNormalizedImplementation(IntPtr InQuat, LwcType Tolerance, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_IsNormalizedImplementation(IntPtr InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_SizeImplementation(IntPtr InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_SizeSquaredImplementation(IntPtr InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_GetAngleImplementation(IntPtr InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ToAxisAndAngleImplementation(IntPtr InQuat, out FVector Axis, out LwcType Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ToSwingTwistImplementation(IntPtr InQuat, FVector InTwistAxis,
            out FQuat OutSwing,
            out FQuat OutTwist);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_GetTwistAngleImplementation(IntPtr InQuat, FVector TwistAxis);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_RotateVectorImplementation(IntPtr InQuat, FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_UnrotateVectorImplementation(IntPtr InQuat, FVector V, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_LogImplementation(IntPtr InQuat, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ExpImplementation(IntPtr InQuat, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_InverseImplementation(IntPtr InQuat, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_EnforceShortestArcWithImplementation(IntPtr InQuat, FQuat OtherQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetAxisXImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetAxisYImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetAxisZImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetForwardVectorImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetRightVectorImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetUpVectorImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_VectorImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_RotatorImplementation(IntPtr InQuat, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_GetRotationAxisImplementation(IntPtr InQuat, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_AngularDistanceImplementation(IntPtr InQuat, FQuat Q);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_ContainsNaNImplementation(IntPtr InQuat);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_ToStringImplementation(IntPtr InQuat, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Quat_InitFromStringImplementation(IntPtr InQuat, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FindBetweenImplementation(FVector Vector1, FVector Vector2, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FindBetweenNormalsImplementation(FVector Normal1, FVector Normal2,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FindBetweenVectorsImplementation(FVector Vector1, FVector Vector2,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_ErrorImplementation(IntPtr Q1, IntPtr Q2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Quat_ErrorAutoNormalizeImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FastLerpImplementation(IntPtr A, IntPtr B, LwcType Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_FastBilerpImplementation(IntPtr P00, IntPtr P10, IntPtr P01, IntPtr P11,
            LwcType FracX, LwcType FracY, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_Slerp_NotNormalizedImplementation(IntPtr Quat1, IntPtr Quat2, LwcType Slerp,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SlerpImplementation(IntPtr Quat1, IntPtr Quat2, LwcType Slerp,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SlerpFullPath_NotNormalizedImplementation(IntPtr quat1, IntPtr quat2,
            LwcType Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SlerpFullPathImplementation(IntPtr quat1, IntPtr quat2, LwcType Alpha,
            out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SquadImplementation(IntPtr quat1, IntPtr tang1, IntPtr quat2, IntPtr tang2,
            LwcType Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_SquadFullPathImplementation(IntPtr quat1, IntPtr tang1, IntPtr quat2,
            IntPtr tang2,
            LwcType Alpha, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Quat_CalcTangentsImplementation(IntPtr PrevP, IntPtr P, IntPtr NextP, LwcType Tension,
            out FQuat OutTan);
    }
}