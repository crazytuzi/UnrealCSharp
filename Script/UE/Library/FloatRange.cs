using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FFloatRange
    {
        public static Boolean operator ==(FFloatRange A, FFloatRange B) =>
            FloatRangeImplementation.FloatRange_EqualityImplementation(A, B);

        public static Boolean operator !=(FFloatRange A, FFloatRange B) =>
            FloatRangeImplementation.FloatRange_InequalityImplementation(A, B);

        public Boolean Adjoins(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_AdjoinsImplementation(this, Other);

        public Boolean Conjoins(FFloatRange X, FFloatRange Y) =>
            FloatRangeImplementation.FloatRange_ConjoinsImplementation(this, X, Y);

        public Boolean Contains(Single Element) =>
            FloatRangeImplementation.FloatRange_ContainsElementImplementation(this, Element);

        public Boolean Contains(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_ContainsImplementation(this, Other);

        public Boolean Contiguous(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_ContiguousImplementation(this, Other);

        public FFloatRangeBound GetLowerBound()
        {
            FloatRangeImplementation.FloatRange_GetLowerBoundImplementation(this, out var OutValue);

            return OutValue;
        }

        public void SetLowerBound(FFloatRangeBound NewLowerBound) =>
            FloatRangeImplementation.FloatRange_SetLowerBoundImplementation(this, NewLowerBound);

        public void SetLowerBoundValue(Single NewLowerBoundValue) =>
            FloatRangeImplementation.FloatRange_SetLowerBoundValueImplementation(this, NewLowerBoundValue);

        public Single GetLowerBoundValue() =>
            FloatRangeImplementation.FloatRange_GetLowerBoundValueImplementation(this);

        public FFloatRangeBound GetUpperBound()
        {
            FloatRangeImplementation.FloatRange_GetUpperBoundImplementation(this, out var OutValue);

            return OutValue;
        }

        public void SetUpperBound(FFloatRangeBound NewUpperBound) =>
            FloatRangeImplementation.FloatRange_SetUpperBoundImplementation(this, NewUpperBound);

        public void SetUpperBoundValue(Single NewLowerBoundValue) =>
            FloatRangeImplementation.FloatRange_SetUpperBoundValueImplementation(this, NewLowerBoundValue);

        public Single GetUpperBoundValue() =>
            FloatRangeImplementation.FloatRange_GetUpperBoundValueImplementation(this);

        public Boolean HasLowerBound() =>
            FloatRangeImplementation.FloatRange_HasLowerBoundImplementation(this);

        public Boolean HasUpperBound() =>
            FloatRangeImplementation.FloatRange_HasUpperBoundImplementation(this);

        public Boolean IsDegenerate() =>
            FloatRangeImplementation.FloatRange_IsDegenerateImplementation(this);

        public Boolean IsEmpty() =>
            FloatRangeImplementation.FloatRange_IsEmptyImplementation(this);

        public Boolean Overlaps(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_OverlapsImplementation(this, Other);

        // @TODO
        // Size
        // Split
        // Difference

        public static FFloatRange Hull(FFloatRange X, FFloatRange Y)
        {
            FloatRangeImplementation.FloatRange_HullImplementation(X, Y, out var OutValue);

            return OutValue;
        }

        // @TODO
        // Hull

        public static FFloatRange Intersection(FFloatRange X, FFloatRange Y)
        {
            FloatRangeImplementation.FloatRange_IntersectionImplementation(X, Y, out var OutValue);

            return OutValue;
        }

        // @TODO
        // Intersection
        // Union

        public static FFloatRange All()
        {
            FloatRangeImplementation.FloatRange_AllImplementation(out var OutValue);

            return OutValue;
        }

        public static FFloatRange AtLeast(Single Value)
        {
            FloatRangeImplementation.FloatRange_AtLeastImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FFloatRange AtMost(Single Value)
        {
            FloatRangeImplementation.FloatRange_AtMostImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FFloatRange Empty()
        {
            FloatRangeImplementation.FloatRange_EmptyImplementation(out var OutValue);

            return OutValue;
        }

        public static FFloatRange Exclusive(Single Min, Single Max)
        {
            FloatRangeImplementation.FloatRange_ExclusiveImplementation(Min, Max, out var OutValue);

            return OutValue;
        }

        public static FFloatRange GreaterThan(Single Value)
        {
            FloatRangeImplementation.FloatRange_GreaterThanImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FFloatRange Inclusive(Single Min, Single Max)
        {
            FloatRangeImplementation.FloatRange_InclusiveImplementation(Min, Max, out var OutValue);

            return OutValue;
        }

        public static FFloatRange LessThan(Single Value)
        {
            FloatRangeImplementation.FloatRange_LessThanImplementation(Value, out var OutValue);

            return OutValue;
        }
    }
}