using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Box2DImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_AddVector2DImplementation(IntPtr A, IntPtr B, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_AddImplementation(IntPtr A, IntPtr B, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetReferenceImplementation(IntPtr InBox2D, Int32 Index, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_SetReferenceImplementation(IntPtr InBox2D, Int32 Index, FVector2D InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Box2D_ComputeSquaredDistanceToPointImplementation(IntPtr InBox2D, FVector2D Point);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_ExpandByImplementation(IntPtr InBox2D, LwcType W, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Box2D_GetAreaImplementation(IntPtr InBox2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetCenterImplementation(IntPtr InBox2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetCenterAndExtentsImplementation(IntPtr InBox2D, out FVector2D center,
            out FVector2D Extents);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetClosestPointToImplementation(IntPtr InBox2D, FVector2D Point,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetExtentImplementation(IntPtr InBox2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetSizeImplementation(IntPtr InBox2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_InitImplementation(IntPtr InBox2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_IntersectImplementation(IntPtr InBox2D, FBox2D other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_IsInsideVector2DImplementation(IntPtr InBox2D, FVector2D TestPoint);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_IsInsideBox2DImplementation(IntPtr InBox2D, FBox2D Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_ShiftByImplementation(IntPtr InBox2D, FVector2D Offset, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_ToStringImplementation(IntPtr InBox2D, out FString OutValue);
    }
}