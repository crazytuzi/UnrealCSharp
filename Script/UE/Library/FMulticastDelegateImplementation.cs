using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FMulticastDelegateImplementation
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
        public static extern void FMulticastDelegate_Broadcast0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FMulticastDelegate_Broadcast1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_Broadcast2Implementation(nint InMonoObject,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FMulticastDelegate_Broadcast3Implementation(nint InMonoObject,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_Broadcast4Implementation(nint InMonoObject, out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FMulticastDelegate_Broadcast5Implementation(nint InMonoObject,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FMulticastDelegate_Broadcast6Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FMulticastDelegate_Broadcast7Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);
    }
}