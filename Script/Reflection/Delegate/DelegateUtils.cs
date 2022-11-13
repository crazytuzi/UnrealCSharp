using System;
using Script.Reflection.Function;

namespace Script.Reflection.Delegate
{
    public static class DelegateUtils
    {
        public static unsafe void Delegate_Bind<T>(void* InAddress, T InDelegate) where T : System.Delegate =>
            DelegateImplementation.Delegate_BindImplementation(InAddress, InDelegate);

        public static unsafe Boolean Delegate_IsBound(void* InAddress) =>
            DelegateImplementation.Delegate_IsBoundImplementation(InAddress);

        public static unsafe void Delegate_UnBind(void* InAddress) =>
            DelegateImplementation.Delegate_UnBindImplementation(InAddress);

        public static unsafe void Delegate_Clear(void* InAddress) =>
            DelegateImplementation.Delegate_ClearImplementation(InAddress);

        public static unsafe void Delegate_Execute<T>(void* InAddress, out T ReturnValue, out ObjectList OutValue,
            params Object[] InValue) =>
            DelegateImplementation.Delegate_ExecuteImplementation(InAddress, out ReturnValue, out OutValue, InValue);
    }
}