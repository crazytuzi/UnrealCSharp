using System;
using Script.Library;

namespace Script.CoreUObject
{
    public class FDelegate<T> : FDelegateBase where T : Delegate
    {
        public void Bind(UObject InObject, T InDelegate) => FDelegateImplementation.FDelegate_BindImplementation(
            GarbageCollectionHandle,
            InObject.GarbageCollectionHandle,
            InDelegate);

        public bool IsBound() => FDelegateImplementation.FDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public void Unbind() => FDelegateImplementation.FDelegate_UnBindImplementation(GarbageCollectionHandle);

        public void Clear() => FDelegateImplementation.FDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}