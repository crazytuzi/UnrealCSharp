using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class MulticastDelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RegisterImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool MulticastDelegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool MulticastDelegate_ContainsImplementation<T>(nint InMonoObject, T InMulticastDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddImplementation<T>(nint InMonoObject, T InMulticastDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddUniqueImplementation<T>(nint InMonoObject, T InMulticastDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveImplementation<T>(nint InMonoObject, T InMulticastDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveAllImplementation(nint InMonoObject, UObject InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_ClearImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object MulticastDelegate_Broadcast1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast2Implementation(nint InMonoObject,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object MulticastDelegate_Broadcast3Implementation(nint InMonoObject,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast4Implementation(nint InMonoObject, out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object MulticastDelegate_Broadcast5Implementation(nint InMonoObject,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast6Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object MulticastDelegate_Broadcast7Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);
    }
}