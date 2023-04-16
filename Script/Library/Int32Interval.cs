using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FInt32Interval
    {
        public Int32 Size() =>
            Int32IntervalImplementation.Int32Interval_SizeImplementation(this);

        public Boolean IsValid() =>
            Int32IntervalImplementation.Int32Interval_IsValidImplementation(this);

        public Boolean Contains(Int32 Element) =>
            Int32IntervalImplementation.Int32Interval_ContainsImplementation(this, Element);

        public void Expand(Int32 ExpandAmount) =>
            Int32IntervalImplementation.Int32Interval_ExpandImplementation(this, ExpandAmount);

        public void Include(Int32 X) =>
            Int32IntervalImplementation.Int32Interval_IncludeImplementation(this, X);

        public Int32 Interpolate(Single Alpha) =>
            Int32IntervalImplementation.Int32Interval_InterpolateImplementation(this, Alpha);

        public static FInt32Interval Intersect(FInt32Interval A, FInt32Interval B)
        {
            Int32IntervalImplementation.Int32Interval_IntersectImplementation(A, B, out var OutValue);

            return OutValue;
        }
    }
}