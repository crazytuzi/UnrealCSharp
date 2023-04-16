using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FFrameTime
    {
        public FFrameNumber GetFrame()
        {
            FrameTimeImplementation.FrameTime_GetFrameImplementation(this, out var OutValue);

            return OutValue;
        }

        public Single GetSubFrame() =>
            FrameTimeImplementation.FrameTime_GetSubFrameImplementation(this);

        public FFrameNumber FloorToFrame()
        {
            FrameTimeImplementation.FrameTime_FloorToFrameImplementation(this, out var OutValue);

            return OutValue;
        }

        public FFrameNumber CeilToFrame()
        {
            FrameTimeImplementation.FrameTime_CeilToFrameImplementation(this, out var OutValue);

            return OutValue;
        }

        public FFrameNumber RoundToFrame()
        {
            FrameTimeImplementation.FrameTime_RoundToFrameImplementation(this, out var OutValue);

            return OutValue;
        }

        public Double AsDecimal() =>
            FrameTimeImplementation.FrameTime_AsDecimalImplementation(this);

        public static FFrameTime FromDecimal(Double InDecimalFrame)
        {
            FrameTimeImplementation.FrameTime_FromDecimalImplementation(InDecimalFrame, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_EqualityImplementation(A, B);

        public static Boolean operator !=(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_InequalityImplementation(A, B);

        public static Boolean operator >(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_GreaterThanImplementation(A, B);

        public static Boolean operator >=(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_GreaterThanOrEqualImplementation(A, B);

        public static Boolean operator <(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_LessThanImplementation(A, B);

        public static Boolean operator <=(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_LessThanOrEqualImplementation(A, B);

        public static FFrameTime operator +(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator -(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator %(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_RemainderImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator -(FFrameTime A)
        {
            FrameTimeImplementation.FrameTime_NegatedImplementation(A, out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator *(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator /(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_DivideImplementation(A, B, out var OutValue);

            return OutValue;
        }
    }
}