using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public void Bind(UObject _, T InDelegate) => DelegateUtils.Delegate_Bind(GetHandle(), InDelegate);

        public void Bind(T InDelegate) => DelegateUtils.Delegate_Bind(GetHandle(), InDelegate);

        public Boolean IsBound() => DelegateUtils.Delegate_IsBound(GetHandle());

        public void Unbind() => DelegateUtils.Delegate_UnBind(GetHandle());

        public void Clear() => DelegateUtils.Delegate_Clear(GetHandle());
    }
}