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
        public static extern void MulticastDelegate_UnRegisterImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean MulticastDelegate_IsBoundImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean MulticastDelegate_ContainsImplementation<T>(FDelegateBase InMonoObject,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddImplementation<T>(FDelegateBase InMonoObject,
            T InMulticastDelegate)
            where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_AddUniqueImplementation<T>(FDelegateBase InMonoObject,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveImplementation<T>(FDelegateBase InMonoObject,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_RemoveAllImplementation(FDelegateBase InMonoObject,
            UObject InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_ClearImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void MulticastDelegate_BroadcastImplementation(FDelegateBase InMonoObject,
            out ObjectList OutValue, params Object[] InValue);
    }
}