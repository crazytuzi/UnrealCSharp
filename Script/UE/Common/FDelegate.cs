using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public void Bind(UObject _, T InDelegate) =>
            DelegateImplementation.Delegate_BindImplementation(GetHandle(), InDelegate);

        public void Bind(T InDelegate) => DelegateImplementation.Delegate_BindImplementation(GetHandle(), InDelegate);

        public Boolean IsBound() => DelegateImplementation.Delegate_IsBoundImplementation(GetHandle());

        public void Unbind() => DelegateImplementation.Delegate_UnBindImplementation(GetHandle());

        public void Clear() => DelegateImplementation.Delegate_ClearImplementation(GetHandle());
    }
}