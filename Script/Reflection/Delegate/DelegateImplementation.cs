using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Reflection.Delegate
{
    public static class DelegateImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void Delegate_BindImplementation<T>(void* InAddress, T InDelegate)
            where T : System.Delegate;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe Boolean Delegate_IsBoundImplementation(void* InAddress);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void Delegate_UnBindImplementation(void* InAddress);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void Delegate_ClearImplementation(void* InAddress);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern unsafe void Delegate_ExecuteImplementation<T>(void* InAddress, out T ReturnValue,
            out ObjectList OutValue, params Object[] InValue);
    }
}