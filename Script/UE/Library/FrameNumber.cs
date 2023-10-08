using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FFrameNumber
    {
        public static FFrameNumber operator ++(FFrameNumber A)
        {
            FrameNumberImplementation.FrameNumber_IncrementImplementation(A.GetHandle());

            return A;
        }

        public static FFrameNumber operator --(FFrameNumber A)
        {
            FrameNumberImplementation.FrameNumber_DecrementImplementation(A.GetHandle());

            return A;
        }

        public static Boolean operator <(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_LessThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_GreaterThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <=(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_LessThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >=(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_GreaterThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static FFrameNumber operator +(FFrameNumber A, FFrameNumber B)
        {
            FrameNumberImplementation.FrameNumber_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator -(FFrameNumber A, FFrameNumber B)
        {
            FrameNumberImplementation.FrameNumber_SubtractImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator %(FFrameNumber A, FFrameNumber B)
        {
            FrameNumberImplementation.FrameNumber_RemainderImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator -(FFrameNumber A)
        {
            FrameNumberImplementation.FrameNumber_NegatedImplementation(A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator *(FFrameNumber A, Single Scalar)
        {
            FrameNumberImplementation.FrameNumber_MultiplyImplementation(A.GetHandle(), Scalar, out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator /(FFrameNumber A, Single Scalar)
        {
            FrameNumberImplementation.FrameNumber_DivideImplementation(A.GetHandle(), Scalar, out var OutValue);

            return OutValue;
        }
    }
}