using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FFloatInterval
    {
        public Single Size() =>
            FloatIntervalImplementation.FloatInterval_SizeImplementation(this);

        public Boolean IsValid() =>
            FloatIntervalImplementation.FloatInterval_IsValidImplementation(this);

        public Boolean Contains(Single Element) =>
            FloatIntervalImplementation.FloatInterval_ContainsImplementation(this, Element);

        public void Expand(Single ExpandAmount) =>
            FloatIntervalImplementation.FloatInterval_ExpandImplementation(this, ExpandAmount);

        public void Include(Single X) =>
            FloatIntervalImplementation.FloatInterval_IncludeImplementation(this, X);

        public Single Interpolate(Single Alpha) =>
            FloatIntervalImplementation.FloatInterval_InterpolateImplementation(this, Alpha);

        public static FFloatInterval Intersect(FFloatInterval A, FFloatInterval B)
        {
            FloatIntervalImplementation.FloatInterval_IntersectImplementation(A, B, out var OutValue);

            return OutValue;
        }
    }
}