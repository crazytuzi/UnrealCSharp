using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public unsafe void Bind(UObject _, T InDelegate) => DelegateUtils.Delegate_Bind(Address, InDelegate);

        public unsafe void Bind(T InDelegate) => DelegateUtils.Delegate_Bind(Address, InDelegate);

        public unsafe Boolean IsBound() => DelegateUtils.Delegate_IsBound(Address);

        public unsafe void Unbind() => DelegateUtils.Delegate_UnBind(Address);

        public unsafe void Clear() => DelegateUtils.Delegate_Clear(Address);
    }
}