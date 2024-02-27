using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FDelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_RegisterImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_BindImplementation<T>(nint InMonoObject, T InDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FDelegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_UnBindImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_ClearImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_Execute0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_Execute2Implementation(nint InMonoObject, params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_Execute3Implementation(nint InMonoObject, params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_Execute4Implementation(nint InMonoObject, out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_Execute5Implementation(nint InMonoObject, out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_Execute6Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FDelegate_Execute7Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);
    }
}