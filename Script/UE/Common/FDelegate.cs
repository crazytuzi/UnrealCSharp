using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public void Bind(UObject _, T InDelegate) =>
            FDelegateImplementation.FDelegate_BindImplementation(GarbageCollectionHandle, InDelegate);

        public void Bind(T InDelegate) =>
            FDelegateImplementation.FDelegate_BindImplementation(GarbageCollectionHandle, InDelegate);

        public bool IsBound() => FDelegateImplementation.FDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public void Unbind() => FDelegateImplementation.FDelegate_UnBindImplementation(GarbageCollectionHandle);

        public void Clear() => FDelegateImplementation.FDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}