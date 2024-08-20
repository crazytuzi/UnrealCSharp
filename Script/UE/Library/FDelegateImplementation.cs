using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static unsafe class FDelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_RegisterImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_BindImplementation<T>(nint InMonoObject, nint InObject, T InDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FDelegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_UnBindImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_ClearImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FDelegate_ByteExecute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FDelegate_ByteExecute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FDelegate_ByteExecute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FDelegate_UInt16Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FDelegate_UInt16Execute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FDelegate_UInt16Execute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FDelegate_UInt32Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FDelegate_UInt32Execute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FDelegate_UInt32Execute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FDelegate_UInt64Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FDelegate_UInt64Execute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FDelegate_UInt64Execute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FDelegate_SByteExecute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FDelegate_SByteExecute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FDelegate_SByteExecute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FDelegate_Int16Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FDelegate_Int16Execute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FDelegate_Int16Execute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FDelegate_Int32Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FDelegate_Int32Execute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FDelegate_Int32Execute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FDelegate_Int64Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FDelegate_Int64Execute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FDelegate_Int64Execute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FDelegate_BooleanExecute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FDelegate_BooleanExecute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FDelegate_BooleanExecute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FDelegate_SingleExecute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FDelegate_SingleExecute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FDelegate_SingleExecute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_GenericExecute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute2Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_GenericExecute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute4Implementation(nint InMonoObject,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute6Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_GenericExecute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FDelegate_DoubleExecute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FDelegate_DoubleExecute3Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FDelegate_DoubleExecute7Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);
    }
}