using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FFrameTime
    {
        public FFrameNumber GetFrame()
        {
            FrameTimeImplementation.FrameTime_GetFrameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Single GetSubFrame() =>
            FrameTimeImplementation.FrameTime_GetSubFrameImplementation(GetHandle());

        public FFrameNumber FloorToFrame()
        {
            FrameTimeImplementation.FrameTime_FloorToFrameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FFrameNumber CeilToFrame()
        {
            FrameTimeImplementation.FrameTime_CeilToFrameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FFrameNumber RoundToFrame()
        {
            FrameTimeImplementation.FrameTime_RoundToFrameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Double AsDecimal() =>
            FrameTimeImplementation.FrameTime_AsDecimalImplementation(GetHandle());

        public static FFrameTime FromDecimal(Double InDecimalFrame)
        {
            FrameTimeImplementation.FrameTime_FromDecimalImplementation(InDecimalFrame, out var OutValue);

            return OutValue;
        }

        public static Boolean operator >(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_GreaterThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >=(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_GreaterThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_LessThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <=(FFrameTime A, FFrameTime B) =>
            FrameTimeImplementation.FrameTime_LessThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static FFrameTime operator +(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator -(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator %(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_RemainderImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator -(FFrameTime A)
        {
            FrameTimeImplementation.FrameTime_NegatedImplementation(A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator *(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FFrameTime operator /(FFrameTime A, FFrameTime B)
        {
            FrameTimeImplementation.FrameTime_DivideImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }
    }
}