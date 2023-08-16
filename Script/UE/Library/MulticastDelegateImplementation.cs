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
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddImplementation<T>(IntPtr InMonoObject,
            T InMulticastDelegate)
            where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddUniqueImplementation<T>(IntPtr InMonoObject,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveImplementation<T>(IntPtr InMonoObject,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveAllImplementation(IntPtr InMonoObject,
            UObject InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_ClearImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_BroadcastImplementation(IntPtr InMonoObject,
            out Object[] OutValue, params Object[] InValue);
    }
}