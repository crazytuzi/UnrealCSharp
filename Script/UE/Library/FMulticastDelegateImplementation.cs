using System;
using System.Reflection;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static unsafe class FMulticastDelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_RegisterImplementation(object InMonoObject, Type InType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FMulticastDelegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FMulticastDelegate_ContainsImplementation(nint InMonoObject, nint InObject,
            Type InType, MethodInfo InMethodInfo);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_AddImplementation(nint InMonoObject, nint InObject,
            Type InType, MethodInfo InMethodInfo);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_AddUniqueImplementation(nint InMonoObject, nint InObject,
            Type InType, MethodInfo InMethodInfo);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_RemoveImplementation(nint InMonoObject, nint InObject,
            Type InType, MethodInfo InMethodInfo);

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
            byte* OutBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_GenericBroadcast6Implementation(nint InMonoObject,
            byte* InBuffer, byte* OutBuffer);
    }
}