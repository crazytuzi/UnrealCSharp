using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public void Bind(UObject _, T InDelegate) =>
            DelegateImplementation.Delegate_BindImplementation(GarbageCollectionHandle, InDelegate);

        public void Bind(T InDelegate) =>
            DelegateImplementation.Delegate_BindImplementation(GarbageCollectionHandle, InDelegate);

        public bool IsBound() => DelegateImplementation.Delegate_IsBoundImplementation(GarbageCollectionHandle);

        public void Unbind() => DelegateImplementation.Delegate_UnBindImplementation(GarbageCollectionHandle);

        public void Clear() => DelegateImplementation.Delegate_ClearImplementation(GarbageCollectionHandle);
    }
}