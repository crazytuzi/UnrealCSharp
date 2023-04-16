using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Box2DImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_EqualityImplementation(FBox2D A, FBox2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_InequalityImplementation(FBox2D A, FBox2D B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_AddVector2DImplementation(FBox2D A, FVector2D B, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_AddImplementation(FBox2D A, FBox2D B, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetReferenceImplementation(FBox2D InBox2D, Int32 Index, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_SetReferenceImplementation(FBox2D InBox2D, Int32 Index, FVector2D InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Box2D_ComputeSquaredDistanceToPointImplementation(FBox2D InBox2D, FVector2D Point);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_ExpandByImplementation(FBox2D InBox2D, Single W, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Box2D_GetAreaImplementation(FBox2D InBox2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetCenterImplementation(FBox2D InBox2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetCenterAndExtentsImplementation(FBox2D InBox2D, out FVector2D center,
            out FVector2D Extents);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetClosestPointToImplementation(FBox2D InBox2D, FVector2D Point,
            out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetExtentImplementation(FBox2D InBox2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_GetSizeImplementation(FBox2D InBox2D, out FVector2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_InitImplementation(FBox2D InBox2D);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_IntersectImplementation(FBox2D InBox2D, FBox2D other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_IsInsideVector2DImplementation(FBox2D InBox2D, FVector2D TestPoint);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Box2D_IsInsideBox2DImplementation(FBox2D InBox2D, FBox2D Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_ShiftByImplementation(FBox2D InBox2D, FVector2D Offset, out FBox2D OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Box2D_ToStringImplementation(FBox2D InBox2D, out FString OutValue);
    }
}