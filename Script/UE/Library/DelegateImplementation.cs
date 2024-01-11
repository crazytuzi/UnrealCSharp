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
        public static extern void Delegate_UnRegisterImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_BindImplementation<T>(IntPtr InMonoObject, T InDelegate) where T : Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Delegate_IsBoundImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_UnBindImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_ClearImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute0Implementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Delegate_Execute1Implementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute2Implementation(IntPtr InMonoObject, params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Delegate_Execute3Implementation(IntPtr InMonoObject, params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute4Implementation(IntPtr InMonoObject, out Object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Delegate_Execute5Implementation(IntPtr InMonoObject, out Object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_Execute6Implementation(IntPtr InMonoObject, out Object[] OutValue,
            params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Delegate_Execute7Implementation(IntPtr InMonoObject, out Object[] OutValue,
            params Object[] InValue);
    }
}