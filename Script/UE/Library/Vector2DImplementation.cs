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
        public static extern void Vector2D_AddImplementation(FVector2D A, FVector2D B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SubtractImplementation(FVector2D A, FVector2D B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MultiplyScaleImplementation(FVector2D InVector2D, LwcType Scale,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_DivideScaleImplementation(FVector2D InVector2D, LwcType Scale,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_AddAImplementation(FVector2D InVector2D, LwcType A, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SubtractAImplementation(FVector2D InVector2D, LwcType A,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MultiplyImplementation(FVector2D A, FVector2D B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_DivideImplementation(FVector2D A, FVector2D B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_DotProductImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_CrossProductImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_EqualityImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_InequalityImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_LessThanImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_GreaterThanImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_LessThanOrEqualImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_GreaterThanOrEqualImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_NegatedImplementation(FVector2D InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetComponentImplementation(FVector2D InVector2D, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SetComponentImplementation(FVector2D InVector2D, Int32 InIndex,
            LwcType InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_ComponentImplementation(FVector2D InVector2D, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_DistSquaredImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_DistanceImplementation(FVector2D A, FVector2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MaxImplementation(FVector2D A, FVector2D B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_MinImplementation(FVector2D A, FVector2D B, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_EqualsImplementation(FVector2D A, FVector2D B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SetImplementation(FVector2D InVector2D, LwcType InX, LwcType InY);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetMaxImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetAbsMaxImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_GetMinImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_SizeImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector2D_SizeSquaredImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetRotatedImplementation(FVector2D InVector2D, LwcType AngleDeg,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetSafeNormalImplementation(FVector2D InVector2D, LwcType Tolerance,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_NormalizeImplementation(FVector2D InVector2D, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_IsNearlyZeroImplementation(FVector2D InVector2D, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_ToDirectionAndLengthImplementation(FVector2D InVector2D,
            out FVector2D OutDir, out LwcType OutLength);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_IsZeroImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_IntPointImplementation(FVector2D InVector2D, out FIntPoint OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_RoundToVectorImplementation(FVector2D InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_ClampAxesImplementation(FVector2D InVector2D, LwcType MinAxisVal,
            LwcType MaxAxisVal, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetSignVectorImplementation(FVector2D InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_GetAbsImplementation(FVector2D InVector2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_ToStringImplementation(FVector2D InVector2D, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean
            Vector2D_InitFromStringImplementation(FVector2D InVector2D, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector2D_ContainsNaNImplementation(FVector2D InVector2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector2D_SphericalToUnitCartesianImplementation(FVector2D InVector2D,
            out FVector OutValue);
    }
}