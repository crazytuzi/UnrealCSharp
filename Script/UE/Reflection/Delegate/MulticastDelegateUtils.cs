using System;
using Script.Common;
using Script.CoreUObject;
using Script.Library;

namespace Script.Reflection.Delegate
{
    public static class MulticastDelegateUtils
    {
        public static void MulticastDelegate_Register(FDelegateBase InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RegisterImplementation(InMonoObject);

        public static void MulticastDelegate_UnRegister(FDelegateBase InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_UnRegisterImplementation(InMonoObject);

        public static Boolean MulticastDelegate_IsBound(FDelegateBase InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(InMonoObject);

        public static Boolean MulticastDelegate_Contains<T>(FDelegateBase InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(InMonoObject, InMulticastDelegate);

        public static void MulticastDelegate_Add<T>(FDelegateBase InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(InMonoObject, InMulticastDelegate);

        public static void MulticastDelegate_AddUnique<T>(FDelegateBase InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(InMonoObject,
                InMulticastDelegate);

        public static void MulticastDelegate_Remove<T>(FDelegateBase InMonoObject, T InMulticastDelegate)
            where T : System.Delegate =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(InMonoObject, InMulticastDelegate);

        public static void MulticastDelegate_RemoveAll(FDelegateBase InMonoObject, UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(InMonoObject, InObject);

        public static void MulticastDelegate_Clear(FDelegateBase InMonoObject) =>
            MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(InMonoObject);

        public static void
            MulticastDelegate_Broadcast(FDelegateBase InMonoObject, out ObjectList OutValue, params Object[] InValue) =>
            MulticastDelegateImplementation.MulticastDelegate_BroadcastImplementation(InMonoObject, out OutValue,
                InValue);
    }
}