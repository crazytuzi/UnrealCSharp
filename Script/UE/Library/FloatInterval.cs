using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FFloatInterval
    {
        public Single Size() =>
            FloatIntervalImplementation.FloatInterval_SizeImplementation(GetHandle());

        public Boolean IsValid() =>
            FloatIntervalImplementation.FloatInterval_IsValidImplementation(GetHandle());

        public Boolean Contains(Single Element) =>
            FloatIntervalImplementation.FloatInterval_ContainsImplementation(GetHandle(), Element);

        public void Expand(Single ExpandAmount) =>
            FloatIntervalImplementation.FloatInterval_ExpandImplementation(GetHandle(), ExpandAmount);

        public void Include(Single X) =>
            FloatIntervalImplementation.FloatInterval_IncludeImplementation(GetHandle(), X);

        public Single Interpolate(Single Alpha) =>
            FloatIntervalImplementation.FloatInterval_InterpolateImplementation(GetHandle(), Alpha);

        public static FFloatInterval Intersect(FFloatInterval A, FFloatInterval B)
        {
            FloatIntervalImplementation.FloatInterval_IntersectImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }
    }
}