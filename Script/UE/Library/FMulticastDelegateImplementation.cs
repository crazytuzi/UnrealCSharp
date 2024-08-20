using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static unsafe class FMulticastDelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_RegisterImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FMulticastDelegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FMulticastDelegate_ContainsImplementation<T>(nint InMonoObject, nint InObject,
            T InMulticastDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_AddImplementation<T>(nint InMonoObject, nint InObject,
            T InMulticastDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_AddUniqueImplementation<T>(nint InMonoObject, nint InObject,
            T InMulticastDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_RemoveImplementation<T>(nint InMonoObject, nint InObject,
            T InMulticastDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_RemoveAllImplementation(nint InMonoObject, nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_ClearImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_GenericBroadcast0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_GenericBroadcast2Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_GenericBroadcast4Implementation(nint InMonoObject,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_GenericBroadcast6Implementation(nint InMonoObject,
            out object[] OutValue, byte* InBuffer);
    }
}