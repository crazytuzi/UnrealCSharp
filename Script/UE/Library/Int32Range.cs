using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FInt32Range
    {
        public Boolean Adjoins(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_AdjoinsImplementation(GetHandle(), Other);

        public Boolean Conjoins(FInt32Range X, FInt32Range Y) =>
            Int32RangeImplementation.Int32Range_ConjoinsImplementation(GetHandle(), X, Y);

        public Boolean Contains(Int32 Element) =>
            Int32RangeImplementation.Int32Range_ContainsElementImplementation(GetHandle(), Element);

        public Boolean Contains(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_ContainsImplementation(GetHandle(), Other);

        public Boolean Contiguous(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_ContiguousImplementation(GetHandle(), Other);

        public FInt32RangeBound GetLowerBound()
        {
            Int32RangeImplementation.Int32Range_GetLowerBoundImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void SetLowerBound(FInt32RangeBound NewLowerBound) =>
            Int32RangeImplementation.Int32Range_SetLowerBoundImplementation(GetHandle(), NewLowerBound);

        public void SetLowerBoundValue(Int32 NewLowerBoundValue) =>
            Int32RangeImplementation.Int32Range_SetLowerBoundValueImplementation(GetHandle(), NewLowerBoundValue);

        public Int32 GetLowerBoundValue() =>
            Int32RangeImplementation.Int32Range_GetLowerBoundValueImplementation(GetHandle());

        public FInt32RangeBound GetUpperBound()
        {
            Int32RangeImplementation.Int32Range_GetUpperBoundImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void SetUpperBound(FInt32RangeBound NewUpperBound) =>
            Int32RangeImplementation.Int32Range_SetUpperBoundImplementation(GetHandle(), NewUpperBound);

        public void SetUpperBoundValue(Int32 NewLowerBoundValue) =>
            Int32RangeImplementation.Int32Range_SetUpperBoundValueImplementation(GetHandle(), NewLowerBoundValue);

        public Int32 GetUpperBoundValue() =>
            Int32RangeImplementation.Int32Range_GetUpperBoundValueImplementation(GetHandle());

        public Boolean HasLowerBound() =>
            Int32RangeImplementation.Int32Range_HasLowerBoundImplementation(GetHandle());

        public Boolean HasUpperBound() =>
            Int32RangeImplementation.Int32Range_HasUpperBoundImplementation(GetHandle());

        public Boolean IsDegenerate() =>
            Int32RangeImplementation.Int32Range_IsDegenerateImplementation(GetHandle());

        public Boolean IsEmpty() =>
            Int32RangeImplementation.Int32Range_IsEmptyImplementation(GetHandle());

        public Boolean Overlaps(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_OverlapsImplementation(GetHandle(), Other);

        // @TODO
        // Size
        // Split
        // Difference

        public static FInt32Range Hull(FInt32Range X, FInt32Range Y)
        {
            Int32RangeImplementation.Int32Range_HullImplementation(X, Y, out var OutValue);

            return OutValue;
        }

        // @TODO
        // Hull

        public static FInt32Range Intersection(FInt32Range X, FInt32Range Y)
        {
            Int32RangeImplementation.Int32Range_IntersectionImplementation(X, Y, out var OutValue);

            return OutValue;
        }

        // @TODO
        // Intersection
        // Union

        public static FInt32Range All()
        {
            Int32RangeImplementation.Int32Range_AllImplementation(out var OutValue);

            return OutValue;
        }

        public static FInt32Range AtLeast(Int32 Value)
        {
            Int32RangeImplementation.Int32Range_AtLeastImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FInt32Range AtMost(Int32 Value)
        {
            Int32RangeImplementation.Int32Range_AtMostImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FInt32Range Empty()
        {
            Int32RangeImplementation.Int32Range_EmptyImplementation(out var OutValue);

            return OutValue;
        }

        public static FInt32Range Exclusive(Int32 Min, Int32 Max)
        {
            Int32RangeImplementation.Int32Range_ExclusiveImplementation(Min, Max, out var OutValue);

            return OutValue;
        }

        public static FInt32Range GreaterThan(Int32 Value)
        {
            Int32RangeImplementation.Int32Range_GreaterThanImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FInt32Range Inclusive(Int32 Min, Int32 Max)
        {
            Int32RangeImplementation.Int32Range_InclusiveImplementation(Min, Max, out var OutValue);

            return OutValue;
        }

        public static FInt32Range LessThan(Int32 Value)
        {
            Int32RangeImplementation.Int32Range_LessThanImplementation(Value, out var OutValue);

            return OutValue;
        }
    }
}