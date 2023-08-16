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
        public static extern void Delegate_BindImplementation<T>(IntPtr InMonoObject, T InDelegate)
            where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Delegate_IsBoundImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_UnBindImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_ClearImplementation(IntPtr InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_ExecuteImplementation<T>(IntPtr InMonoObject, out T ReturnValue,
            out Object[] OutValue, params Object[] InValue);
    }
}