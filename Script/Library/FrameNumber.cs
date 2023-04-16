using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FFrameNumber
    {
        public static FFrameNumber operator ++(FFrameNumber A)
        {
            FrameNumberImplementation.FrameNumber_IncrementImplementation(A);

            return A;
        }

        public static FFrameNumber operator --(FFrameNumber A)
        {
            FrameNumberImplementation.FrameNumber_DecrementImplementation(A);

            return A;
        }

        public static Boolean operator ==(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_EqualityImplementation(A, B);

        public static Boolean operator !=(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_InequalityImplementation(A, B);

        public static Boolean operator <(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_LessThanImplementation(A, B);

        public static Boolean operator >(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_GreaterThanImplementation(A, B);

        public static Boolean operator <=(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_LessThanOrEqualImplementation(A, B);

        public static Boolean operator >=(FFrameNumber A, FFrameNumber B) =>
            FrameNumberImplementation.FrameNumber_GreaterThanOrEqualImplementation(A, B);

        public static FFrameNumber operator +(FFrameNumber A, FFrameNumber B)
        {
            FrameNumberImplementation.FrameNumber_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator -(FFrameNumber A, FFrameNumber B)
        {
            FrameNumberImplementation.FrameNumber_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator %(FFrameNumber A, FFrameNumber B)
        {
            FrameNumberImplementation.FrameNumber_RemainderImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator -(FFrameNumber A)
        {
            FrameNumberImplementation.FrameNumber_NegatedImplementation(A, out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator *(FFrameNumber A, Single Scalar)
        {
            FrameNumberImplementation.FrameNumber_MultiplyImplementation(A, Scalar, out var OutValue);

            return OutValue;
        }

        public static FFrameNumber operator /(FFrameNumber A, Single Scalar)
        {
            FrameNumberImplementation.FrameNumber_DivideImplementation(A, Scalar, out var OutValue);

            return OutValue;
        }
    }
}