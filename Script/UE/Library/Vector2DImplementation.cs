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
    public static class Vector2DImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_AddImplementation(IntPtr A, IntPtr B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SubtractImplementation(IntPtr A, IntPtr B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MultiplyScaleImplementation(IntPtr InVector2D, LwcType Scale,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_DivideScaleImplementation(IntPtr InVector2D, LwcType Scale,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_AddAImplementation(IntPtr InVector2D, LwcType A, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SubtractAImplementation(IntPtr InVector2D, LwcType A,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MultiplyImplementation(IntPtr A, IntPtr B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_DivideImplementation(IntPtr A, IntPtr B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_DotProductImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_CrossProductImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_LessThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_GreaterThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_LessThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_GreaterThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_NegatedImplementation(IntPtr InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetComponentImplementation(IntPtr InVector2D, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SetComponentImplementation(IntPtr InVector2D, Int32 InIndex,
            LwcType InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_ComponentImplementation(IntPtr InVector2D, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_DistSquaredImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_DistanceImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MaxImplementation(IntPtr A, IntPtr B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MinImplementation(IntPtr A, IntPtr B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_EqualsImplementation(IntPtr A, IntPtr B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SetImplementation(IntPtr InVector2D, LwcType InX, LwcType InY);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetMaxImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetAbsMaxImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetMinImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_SizeImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_SizeSquaredImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetRotatedImplementation(IntPtr InVector2D, LwcType AngleDeg,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetSafeNormalImplementation(IntPtr InVector2D, LwcType Tolerance,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_NormalizeImplementation(IntPtr InVector2D, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_IsNearlyZeroImplementation(IntPtr InVector2D, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_ToDirectionAndLengthImplementation(IntPtr InVector2D,
            out FVector2D OutDir, out LwcType OutLength);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_IsZeroImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_IntPointImplementation(IntPtr InVector2D, out FIntPoint OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_RoundToVectorImplementation(IntPtr InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_ClampAxesImplementation(IntPtr InVector2D, LwcType MinAxisVal,
            LwcType MaxAxisVal, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetSignVectorImplementation(IntPtr InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetAbsImplementation(IntPtr InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_ToStringImplementation(IntPtr InVector2D, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean
            Vector2D_InitFromStringImplementation(IntPtr InVector2D, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_ContainsNaNImplementation(IntPtr InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SphericalToUnitCartesianImplementation(IntPtr InVector2D,
            out FVector OutValue);
    }
}