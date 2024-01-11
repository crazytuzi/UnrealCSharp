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
        public static extern void MulticastDelegate_UnRegisterImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean MulticastDelegate_IsBoundImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean MulticastDelegate_ContainsImplementation<T>(IntPtr InMonoObject,
            T InMulticastDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddImplementation<T>(IntPtr InMonoObject, T InMulticastDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddUniqueImplementation<T>(IntPtr InMonoObject,
            T InMulticastDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveImplementation<T>(IntPtr InMonoObject, T InMulticastDelegate)
            where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveAllImplementation(IntPtr InMonoObject, UObject InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_ClearImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast0Implementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object MulticastDelegate_Broadcast1Implementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast2Implementation(IntPtr InMonoObject,
            params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object MulticastDelegate_Broadcast3Implementation(IntPtr InMonoObject,
            params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            MulticastDelegate_Broadcast4Implementation(IntPtr InMonoObject, out Object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object MulticastDelegate_Broadcast5Implementation(IntPtr InMonoObject,
            out Object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_Broadcast6Implementation(IntPtr InMonoObject, out Object[] OutValue,
            params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object MulticastDelegate_Broadcast7Implementation(IntPtr InMonoObject,
            out Object[] OutValue, params Object[] InValue);
    }
}