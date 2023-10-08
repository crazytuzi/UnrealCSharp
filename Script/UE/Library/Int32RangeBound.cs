using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FInt32RangeBound
    {
        public Int32 GetValue() =>
            Int32RangeBoundImplementation.Int32RangeBound_GetValueImplementation(GetHandle());

        public void SetValue(Int32 NewValue) =>
            Int32RangeBoundImplementation.Int32RangeBound_SetValueImplementation(GetHandle(), NewValue);

        public Boolean IsClosed() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsClosedImplementation(GetHandle());

        public Boolean IsExclusive() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsExclusiveImplementation(GetHandle());

        public Boolean IsInclusive() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsInclusiveImplementation(GetHandle());

        public Boolean IsOpen() =>
            Int32RangeBoundImplementation.Int32RangeBound_IsOpenImplementation(GetHandle());

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
            Int32RangeBoundImplementation.Int32RangeBound_FlipInclusionImplementation(Bound.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MaxLower(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MaxLowerImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MaxUpper(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MaxUpperImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MinLower(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MinLowerImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FInt32RangeBound MinUpper(FInt32RangeBound A, FInt32RangeBound B)
        {
            Int32RangeBoundImplementation.Int32RangeBound_MinUpperImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }
    }
}