using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FFloatRangeBound
    {
        public static Boolean operator ==(FFloatRangeBound A, FFloatRangeBound B) =>
            FloatRangeBoundImplementation.FloatRangeBound_EqualityImplementation(A, B);

        public static Boolean operator !=(FFloatRangeBound A, FFloatRangeBound B) =>
            FloatRangeBoundImplementation.FloatRangeBound_InequalityImplementation(A, B);

        public Single GetValue() =>
            FloatRangeBoundImplementation.FloatRangeBound_GetValueImplementation(this);

        public void SetValue(Single NewValue) =>
            FloatRangeBoundImplementation.FloatRangeBound_SetValueImplementation(this, NewValue);

        public Boolean IsClosed() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsClosedImplementation(this);

        public Boolean IsExclusive() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsExclusiveImplementation(this);

        public Boolean IsInclusive() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsInclusiveImplementation(this);

        public Boolean IsOpen() =>
            FloatRangeBoundImplementation.FloatRangeBound_IsOpenImplementation(this);

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
            FloatRangeBoundImplementation.FloatRangeBound_MaxLowerImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MaxUpper(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MaxUpperImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MinLower(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MinLowerImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFloatRangeBound MinUpper(FFloatRangeBound A, FFloatRangeBound B)
        {
            FloatRangeBoundImplementation.FloatRangeBound_MinUpperImplementation(A, B, out var OutValue);

            return OutValue;
        }
    }
}