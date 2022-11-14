using System;
using Script.Engine;
using Script.Reflection.Function;

namespace Script.Reflection.Delegate
{
    public static class MulticastDelegateUtils
    {
        public static unsafe Boolean MulticastDelegate_IsBound(void* InAddress) =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(InAddress);

        public static unsafe Boolean MulticastDelegate_Contains<T>(void* InAddress, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(InAddress, InMulticastDelegate);

        public static unsafe void MulticastDelegate_Add<T>(void* InAddress, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(InAddress, InMulticastDelegate);

        public static unsafe void MulticastDelegate_AddUnique<T>(void* InAddress, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(InAddress, InMulticastDelegate);

        public static unsafe void MulticastDelegate_Remove<T>(void* InAddress, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(InAddress, InMulticastDelegate);

        public static unsafe void MulticastDelegate_RemoveAll(void* InAddress, UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(InAddress, InObject);

        public static unsafe void MulticastDelegate_Clear(void* InAddress) =>
            MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(InAddress);

        public static unsafe void
            MulticastDelegate_Broadcast(void* InAddress, out ObjectList OutValue, params Object[] InValue) =>
            MulticastDelegateImplementation.MulticastDelegate_BroadcastImplementation(InAddress, out OutValue, InValue);

        private static Object MulticastDelegate_GetTarget(System.Delegate InDelegate) => InDelegate.Target;

        private static Boolean MulticastDelegate_Equals(System.Delegate A, System.Delegate B) => A == B;
    }
}