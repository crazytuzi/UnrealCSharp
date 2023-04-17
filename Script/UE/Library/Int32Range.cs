using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FInt32Range
    {
        public static Boolean operator ==(FInt32Range A, FInt32Range B) =>
            Int32RangeImplementation.Int32Range_EqualityImplementation(A, B);

        public static Boolean operator !=(FInt32Range A, FInt32Range B) =>
            Int32RangeImplementation.Int32Range_InequalityImplementation(A, B);

        public Boolean Adjoins(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_AdjoinsImplementation(this, Other);

        public Boolean Conjoins(FInt32Range X, FInt32Range Y) =>
            Int32RangeImplementation.Int32Range_ConjoinsImplementation(this, X, Y);

        public Boolean Contains(Int32 Element) =>
            Int32RangeImplementation.Int32Range_ContainsElementImplementation(this, Element);

        public Boolean Contains(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_ContainsImplementation(this, Other);

        public Boolean Contiguous(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_ContiguousImplementation(this, Other);

        public FInt32RangeBound GetLowerBound()
        {
            Int32RangeImplementation.Int32Range_GetLowerBoundImplementation(this, out var OutValue);

            return OutValue;
        }

        public void SetLowerBound(FInt32RangeBound NewLowerBound) =>
            Int32RangeImplementation.Int32Range_SetLowerBoundImplementation(this, NewLowerBound);

        public void SetLowerBoundValue(Int32 NewLowerBoundValue) =>
            Int32RangeImplementation.Int32Range_SetLowerBoundValueImplementation(this, NewLowerBoundValue);

        public Int32 GetLowerBoundValue() =>
            Int32RangeImplementation.Int32Range_GetLowerBoundValueImplementation(this);

        public FInt32RangeBound GetUpperBound()
        {
            Int32RangeImplementation.Int32Range_GetUpperBoundImplementation(this, out var OutValue);

            return OutValue;
        }

        public void SetUpperBound(FInt32RangeBound NewUpperBound) =>
            Int32RangeImplementation.Int32Range_SetUpperBoundImplementation(this, NewUpperBound);

        public void SetUpperBoundValue(Int32 NewLowerBoundValue) =>
            Int32RangeImplementation.Int32Range_SetUpperBoundValueImplementation(this, NewLowerBoundValue);

        public Int32 GetUpperBoundValue() =>
            Int32RangeImplementation.Int32Range_GetUpperBoundValueImplementation(this);

        public Boolean HasLowerBound() =>
            Int32RangeImplementation.Int32Range_HasLowerBoundImplementation(this);

        public Boolean HasUpperBound() =>
            Int32RangeImplementation.Int32Range_HasUpperBoundImplementation(this);

        public Boolean IsDegenerate() =>
            Int32RangeImplementation.Int32Range_IsDegenerateImplementation(this);

        public Boolean IsEmpty() =>
            Int32RangeImplementation.Int32Range_IsEmptyImplementation(this);

        public Boolean Overlaps(FInt32Range Other) =>
            Int32RangeImplementation.Int32Range_OverlapsImplementation(this, Other);

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