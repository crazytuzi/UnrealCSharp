using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static unsafe class FFunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FFunction_ByteCall1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FFunction_ByteCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FFunction_ByteCall7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FFunction_ByteCall9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FFunction_ByteCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FFunction_ByteCall15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FFunction_UInt16Call1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FFunction_UInt16Call3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FFunction_UInt16Call7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FFunction_UInt16Call9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FFunction_UInt16Call11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FFunction_UInt16Call15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FFunction_UInt32Call1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FFunction_UInt32Call3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FFunction_UInt32Call7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FFunction_UInt32Call9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FFunction_UInt32Call11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FFunction_UInt32Call15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_UInt64Call1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_UInt64Call3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_UInt64Call7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_UInt64Call9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_UInt64Call11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_UInt64Call15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FFunction_SByteCall1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FFunction_SByteCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FFunction_SByteCall7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FFunction_SByteCall9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FFunction_SByteCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FFunction_SByteCall15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FFunction_Int16Call1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FFunction_Int16Call3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FFunction_Int16Call7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FFunction_Int16Call9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FFunction_Int16Call11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FFunction_Int16Call15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FFunction_Int32Call1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FFunction_Int32Call3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FFunction_Int32Call7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FFunction_Int32Call9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FFunction_Int32Call11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FFunction_Int32Call15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FFunction_Int64Call1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FFunction_Int64Call3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FFunction_Int64Call7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FFunction_Int64Call9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FFunction_Int64Call11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FFunction_Int64Call15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FFunction_BooleanCall1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FFunction_BooleanCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FFunction_BooleanCall7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FFunction_BooleanCall9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FFunction_BooleanCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FFunction_BooleanCall15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FFunction_SingleCall1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FFunction_SingleCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FFunction_SingleCall7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FFunction_SingleCall9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FFunction_SingleCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FFunction_SingleCall15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall0Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FFunction_GenericCall1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall2Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FFunction_GenericCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall4Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall6Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FFunction_GenericCall7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall8Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FFunction_GenericCall9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall10Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FFunction_GenericCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall14Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FFunction_GenericCall15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall24Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall26Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FFunction_DoubleCall1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FFunction_DoubleCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FFunction_DoubleCall7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FFunction_DoubleCall9Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FFunction_DoubleCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FFunction_DoubleCall15Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, byte* InBuffer);
    }
}