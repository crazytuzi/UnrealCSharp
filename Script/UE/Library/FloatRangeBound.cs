using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FFloatRangeBound
    {
        public static Boolean operator ==(FFloatRangeBound A, FFloatRangeBound B) =>
            FloatRangeBoundImplementation.FloatRangeBound_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FFloatRangeBound A, FFloatRangeBound B) =>
            FloatRangeBoundImplementation.FloatRangeBound_InequalityImplementation(A.GetHandle(), B.GetHandle());

        public Single GetValue() =>
            FloatRangeBoundImplementation.FloatRangeBound_GetValueImplementation(GetHandle());

        public void SetValue(Single NewValue) =>
            FloatRangeBoundImplementation.FloatRangeBound_SetValueImplementation(GetHandle(), NewValue);

        public Boolean IsClosed() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsClosedImplementation(GetHandle());

        public Boolean IsExclusive() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsExclusiveImplementation(GetHandle());

        public Boolean IsInclusive() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsInclusiveImplementation(GetHandle());

        public Boolean IsOpen() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsOpenImplementation(GetHandle());

        public static FFloatRangeBound Exclusive(Single Value)
        {
            FloatRangeBoundImplementation.FloatRangeBound_ExclusiveImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound Inclusive(Single Value)
        {
            FloatRangeBoundImplementation.FloatRangeBound_InclusiveImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound Open()
        {
            FloatRangeBoundImplementation.FloatRangeBound_OpenImplementation(out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound FlipInclusion(FFloatRangeBound Bound)
        {
            FloatRangeBoundImplementation.FloatRangeBound_FlipInclusionImplementation(Bound, out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MaxLower(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MaxLowerImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MaxUpper(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MaxUpperImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MinLower(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MinLowerImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MinUpper(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MinUpperImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }
    }
}