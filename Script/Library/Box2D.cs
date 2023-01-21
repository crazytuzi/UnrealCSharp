using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FBox2D
    {
        public static Boolean operator ==(FBox2D A, FBox2D B) =>
            Box2DImplementation.Box2D_EqualityImplementation(A, B);

        public static Boolean operator !=(FBox2D A, FBox2D B) =>
            Box2DImplementation.Box2D_InequalityImplementation(A, B);

        public static FBox2D operator +(FBox2D A, FVector2D B)
        {
            Box2DImplementation.Box2D_AddVector2DImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FBox2D operator +(FBox2D A, FBox2D B)
        {
            Box2DImplementation.Box2D_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public FVector2D this[Int32 Index]
        {
            get
            {
                Box2DImplementation.Box2D_GetReferenceImplementation(this, Index, out var OutValue);

                return OutValue;
            }

            set => Box2DImplementation.Box2D_SetReferenceImplementation(this, Index, value);
        }

        public Single ComputeSquaredDistanceToPoint(FVector2D Point) =>
            Box2DImplementation.Box2D_ComputeSquaredDistanceToPointImplementation(this, Point);

        public FBox2D ExpandBy(Single W)
        {
            Box2DImplementation.Box2D_ExpandByImplementation(this, W, out var OutValue);

            return OutValue;
        }

        public Single GetArea() =>
            Box2DImplementation.Box2D_GetAreaImplementation(this);

        public FVector2D GetCenter()
        {
            Box2DImplementation.Box2D_GetCenterImplementation(this, out var OutValue);

            return OutValue;
        }

        public void GetCenterAndExtents(out FVector2D center, out FVector2D Extents) =>
            Box2DImplementation.Box2D_GetCenterAndExtentsImplementation(this, out center, out Extents);

        public FVector2D GetClosestPointTo(FVector2D Point)
        {
            Box2DImplementation.Box2D_GetClosestPointToImplementation(this, Point, out var OutValue);

            return OutValue;
        }

        public FVector2D GetExtent()
        {
            Box2DImplementation.Box2D_GetExtentImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector2D GetSize()
        {
            Box2DImplementation.Box2D_GetSizeImplementation(this, out var OutValue);

            return OutValue;
        }

        public void Init() =>
            Box2DImplementation.Box2D_InitImplementation(this);

        public Boolean Intersect(FBox2D other) =>
            Box2DImplementation.Box2D_IntersectImplementation(this, other);

        public Boolean IsInside(FVector2D TestPoint) =>
            Box2DImplementation.Box2D_IsInsideVector2DImplementation(this, TestPoint);

        public Boolean IsInside(FBox2D Other) =>
            Box2DImplementation.Box2D_IsInsideBox2DImplementation(this, Other);

        public FBox2D ShiftBy(FVector2D Offset)
        {
            Box2DImplementation.Box2D_ShiftByImplementation(this, Offset, out var OutValue);

            return OutValue;
        }

        public FString ToString()
        {
            Box2DImplementation.Box2D_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}