using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FInt32RangeBound
    {
        public static Boolean operator ==(FInt32RangeBound A, FInt32RangeBound B) =>
            Int32RangeBoundImplementation.Int32RangeBound_EqualityImplementation(A, B);

        public static Boolean operator !=(FInt32RangeBound A, FInt32RangeBound B) =>
            Int32RangeBoundImplementation.Int32RangeBound_InequalityImplementation(A, B);

        public Int32 GetValue() =>
            Int32RangeBoundImplementation.Int32RangeBound_GetValueImplementation(this);

        public void SetValue(Int32 NewValue) =>
            Int32RangeBoundImplementation.Int32RangeBound_SetValueImplementation(this, NewValue);

        public Boolean IsClosed() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsClosedImplementation(this);

        public Boolean IsExclusive() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsExclusiveImplementation(this);

        public Boolean IsInclusive() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsInclusiveImplementation(this);

        public Boolean IsOpen() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsOpenImplementation(this);

        public static FInt32RangeBound Exclusive(Int32 Value)
        {
            Int32RangeBoundImplementation.Int32RangeBound_ExclusiveImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound Inclusive(Int32 Value)
        {
            Int32RangeBoundImplementation.Int32RangeBound_InclusiveImplementation(Value, out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound Open()
        {
            Int32RangeBoundImplementation.Int32RangeBound_OpenImplementation(out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound FlipInclusion(FInt32RangeBound Bound)
        {
            Int32RangeBoundImplementation.Int32RangeBound_FlipInclusionImplementation(Bound, out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MaxLower(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MaxLowerImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MaxUpper(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MaxUpperImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MinLower(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MinLowerImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MinUpper(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MinUpperImplementation(A, B, out var OutValue);

            return OutValue;
        }
    }
}