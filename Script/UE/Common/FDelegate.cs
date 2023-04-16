using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public void Bind(UObject _, T InDelegate) => DelegateUtils.Delegate_Bind(this, InDelegate);

        public void Bind(T InDelegate) => DelegateUtils.Delegate_Bind(this, InDelegate);

        public Boolean IsBound() => DelegateUtils.Delegate_IsBound(this);

        public void Unbind() => DelegateUtils.Delegate_UnBind(this);

        public void Clear() => DelegateUtils.Delegate_Clear(this);
    }
}