using System;
using System.Runtime.CompilerServices;
using Script.Engine;
using Script.Reflection.Function;

namespace Script.Reflection.Delegate
{
    public static class MulticastDelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe Boolean MulticastDelegate_IsBoundImplementation(void* InAddress);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe Boolean MulticastDelegate_ContainsImplementation<T>(void* InAddress,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void MulticastDelegate_AddImplementation<T>(void* InAddress, T InMulticastDelegate)
            where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void MulticastDelegate_AddUniqueImplementation<T>(void* InAddress,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void MulticastDelegate_RemoveImplementation<T>(void* InAddress,
            T InMulticastDelegate) where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void MulticastDelegate_RemoveAllImplementation(void* InAddress, UObject InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void MulticastDelegate_ClearImplementation(void* InAddress);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void MulticastDelegate_BroadcastImplementation(void* InAddress,
            out ObjectList OutValue, params Object[] InValue);
    }
}