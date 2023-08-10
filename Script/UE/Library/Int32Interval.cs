using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FInt32Interval
    {
        public Int32 Size() =>
            Int32IntervalImplementation.Int32Interval_SizeImplementation(GetHandle());

        public Boolean IsValid() =>
            Int32IntervalImplementation.Int32Interval_IsValidImplementation(GetHandle());

        public Boolean Contains(Int32 Element) =>
            Int32IntervalImplementation.Int32Interval_ContainsImplementation(GetHandle(), Element);

        public void Expand(Int32 ExpandAmount) =>
            Int32IntervalImplementation.Int32Interval_ExpandImplementation(GetHandle(), ExpandAmount);

        public void Include(Int32 X) =>
            Int32IntervalImplementation.Int32Interval_IncludeImplementation(GetHandle(), X);

        public Int32 Interpolate(Single Alpha) =>
            Int32IntervalImplementation.Int32Interval_InterpolateImplementation(GetHandle(), Alpha);

        public static FInt32Interval Intersect(FInt32Interval A, FInt32Interval B)
        {
            Int32IntervalImplementation.Int32Interval_IntersectImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }
    }
}