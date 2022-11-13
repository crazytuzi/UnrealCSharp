using System;
using Script.Reflection.Delegate;

namespace Script.Engine
{
    public class FDelegate<T> : FDelegateBase
    {
        public unsafe void Bind(UObject _, T InDelegate)
        {
            DelegateUtils.Delegate_Bind(Address, InDelegate);
        }

        public unsafe void Bind(T InDelegate)
        {
            DelegateUtils.Delegate_Bind(Address, InDelegate);
        }

        public unsafe Boolean IsBound()
        {
            return DelegateUtils.Delegate_IsBound(Address);
        }

        public unsafe void Unbind()
        {
            DelegateUtils.Delegate_UnBind(Address);
        }

        public unsafe void Clear()
        {
            DelegateUtils.Delegate_Clear(Address);
        }
    }
}