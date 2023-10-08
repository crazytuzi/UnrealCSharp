using System;
using Script.Library;
#if UE_5_0_OR_LATER
using LwcType = System.Double;
#else
using LwcType = System.Single;
#endif

namespace Script.CoreUObject
{
    public partial class FBox2D
    {
        public static FBox2D operator +(FBox2D A, FVector2D B)
        {
            Box2DImplementation.Box2D_AddVector2DImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FBox2D operator +(FBox2D A, FBox2D B)
        {
            Box2DImplementation.Box2D_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector2D this[Int32 Index]
        {
            get
            {
                Box2DImplementation.Box2D_GetReferenceImplementation(GetHandle(), Index, out var OutValue);

                return OutValue;
            }

            set => Box2DImplementation.Box2D_SetReferenceImplementation(GetHandle(), Index, value);
        }

        public LwcType ComputeSquaredDistanceToPoint(FVector2D Point) =>
            Box2DImplementation.Box2D_ComputeSquaredDistanceToPointImplementation(GetHandle(), Point);

        public FBox2D ExpandBy(LwcType W)
        {
            Box2DImplementation.Box2D_ExpandByImplementation(GetHandle(), W, out var OutValue);

            return OutValue;
        }

        public LwcType GetArea() =>
            Box2DImplementation.Box2D_GetAreaImplementation(GetHandle());

        public FVector2D GetCenter()
        {
            Box2DImplementation.Box2D_GetCenterImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void GetCenterAndExtents(out FVector2D center, out FVector2D Extents) =>
            Box2DImplementation.Box2D_GetCenterAndExtentsImplementation(GetHandle(), out center, out Extents);

        public FVector2D GetClosestPointTo(FVector2D Point)
        {
            Box2DImplementation.Box2D_GetClosestPointToImplementation(GetHandle(), Point, out var OutValue);

            return OutValue;
        }

        public FVector2D GetExtent()
        {
            Box2DImplementation.Box2D_GetExtentImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector2D GetSize()
        {
            Box2DImplementation.Box2D_GetSizeImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void Init() =>
            Box2DImplementation.Box2D_InitImplementation(GetHandle());

        public Boolean Intersect(FBox2D other) =>
            Box2DImplementation.Box2D_IntersectImplementation(GetHandle(), other);

        public Boolean IsInside(FVector2D TestPoint) =>
            Box2DImplementation.Box2D_IsInsideVector2DImplementation(GetHandle(), TestPoint);

        public Boolean IsInside(FBox2D Other) =>
            Box2DImplementation.Box2D_IsInsideBox2DImplementation(GetHandle(), Other);

        public FBox2D ShiftBy(FVector2D Offset)
        {
            Box2DImplementation.Box2D_ShiftByImplementation(GetHandle(), Offset, out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            Box2DImplementation.Box2D_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }
    }
}