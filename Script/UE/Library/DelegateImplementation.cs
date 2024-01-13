using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class DelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_RegisterImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_BindImplementation<T>(nint InMonoObject, T InDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Delegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_UnBindImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_ClearImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Delegate_Execute1Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute2Implementation(nint InMonoObject, params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Delegate_Execute3Implementation(nint InMonoObject, params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute4Implementation(nint InMonoObject, out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Delegate_Execute5Implementation(nint InMonoObject, out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute6Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Delegate_Execute7Implementation(nint InMonoObject, out object[] OutValue,
            params object[] InValue);
    }
}