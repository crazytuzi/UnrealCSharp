using System;
using Script.Common;
using Script.CoreUObject;
using Script.Library;
using IntPtr = System.IntPtr;

namespace Script.Reflection.Delegate
{
    public static class MulticastDelegateUtils
    {
        public static void MulticastDelegate_Register(FDelegateBase InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RegisterImplementation(InMonoObject);

        public static void MulticastDelegate_UnRegister(IntPtr InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_UnRegisterImplementation(InMonoObject);

        public static Boolean MulticastDelegate_IsBound(IntPtr InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(InMonoObject);

        public static Boolean MulticastDelegate_Contains<T>(IntPtr InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(InMonoObject, InMulticastDelegate);

        public static void MulticastDelegate_Add<T>(IntPtr InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(InMonoObject, InMulticastDelegate);

        public static void MulticastDelegate_AddUnique<T>(IntPtr InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(InMonoObject,
                InMulticastDelegate);

        public static void MulticastDelegate_Remove<T>(IntPtr InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(InMonoObject, InMulticastDelegate);

        public static void MulticastDelegate_RemoveAll(IntPtr InMonoObject, UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(InMonoObject, InObject);

        public static void MulticastDelegate_Clear(IntPtr InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(InMonoObject);

        public static void
            MulticastDelegate_Broadcast(IntPtr InMonoObject, out ObjectList OutValue, params Object[] InValue) =>
            MulticastDelegateImplementation.MulticastDelegate_BroadcastImplementation(InMonoObject, out OutValue,
                InValue);
    }
}