using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FFloatRange
    {
        public static Boolean operator ==(FFloatRange A, FFloatRange B) =>
            FloatRangeImplementation.FloatRange_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FFloatRange A, FFloatRange B) =>
            FloatRangeImplementation.FloatRange_InequalityImplementation(A.GetHandle(), B.GetHandle());

        public Boolean Adjoins(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_AdjoinsImplementation(GetHandle(), Other);

        public Boolean Conjoins(FFloatRange X, FFloatRange Y) =>
            FloatRangeImplementation.FloatRange_ConjoinsImplementation(GetHandle(), X, Y);

        public Boolean Contains(Single Element) =>
            FloatRangeImplementation.FloatRange_ContainsElementImplementation(GetHandle(), Element);

        public Boolean Contains(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_ContainsImplementation(GetHandle(), Other);

        public Boolean Contiguous(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_ContiguousImplementation(GetHandle(), Other);

        public FFloatRangeBound GetLowerBound()
        {
            FloatRangeImplementation.FloatRange_GetLowerBoundImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void SetLowerBound(FFloatRangeBound NewLowerBound) =>
            FloatRangeImplementation.FloatRange_SetLowerBoundImplementation(GetHandle(), NewLowerBound);

        public void SetLowerBoundValue(Single NewLowerBoundValue) =>
            FloatRangeImplementation.FloatRange_SetLowerBoundValueImplementation(GetHandle(), NewLowerBoundValue);

        public Single GetLowerBoundValue() =>
            FloatRangeImplementation.FloatRange_GetLowerBoundValueImplementation(GetHandle());

        public FFloatRangeBound GetUpperBound()
        {
            FloatRangeImplementation.FloatRange_GetUpperBoundImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void SetUpperBound(FFloatRangeBound NewUpperBound) =>
            FloatRangeImplementation.FloatRange_SetUpperBoundImplementation(GetHandle(), NewUpperBound);

        public void SetUpperBoundValue(Single NewLowerBoundValue) =>
            FloatRangeImplementation.FloatRange_SetUpperBoundValueImplementation(GetHandle(), NewLowerBoundValue);

        public Single GetUpperBoundValue() =>
            FloatRangeImplementation.FloatRange_GetUpperBoundValueImplementation(GetHandle());

        public Boolean HasLowerBound() =>
            FloatRangeImplementation.FloatRange_HasLowerBoundImplementation(GetHandle());

        public Boolean HasUpperBound() =>
            FloatRangeImplementation.FloatRange_HasUpperBoundImplementation(GetHandle());

        public Boolean IsDegenerate() =>
            FloatRangeImplementation.FloatRange_IsDegenerateImplementation(GetHandle());

        public Boolean IsEmpty() =>
            FloatRangeImplementation.FloatRange_IsEmptyImplementation(GetHandle());

        public Boolean Overlaps(FFloatRange Other) =>
            FloatRangeImplementation.FloatRange_OverlapsImplementation(GetHandle(), Other);

        // @TODO
        // Size
        // Split
        // Difference

        public static FFloatRange Hull(FFloatRange X, FFloatRange Y)
        {
            FloatRangeImplementation.FloatRange_HullImplementation(X.GetHandle(), Y.GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO
        // Hull

        public static FFloatRange Intersection(FFloatRange X, FFloatRange Y)
        {
            FloatRangeImplementation.FloatRange_IntersectionImplementation(X.GetHandle(), Y.GetHandle(),
                out var OutValue);

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