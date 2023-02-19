using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Reflection.Delegate
{
    public static class DelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_BindImplementation<T>(FDelegateBase InMonoObject, T InDelegate)
            where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Delegate_IsBoundImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_UnBindImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_ClearImplementation(FDelegateBase InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Delegate_ExecuteImplementation<T>(FDelegateBase InMonoObject, out T ReturnValue,
            out ObjectList OutValue, params Object[] InValue);
    }
}