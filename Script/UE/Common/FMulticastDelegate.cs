using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public bool IsBound() =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public bool Contains(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(GarbageCollectionHandle,
                InDelegate);

        public bool Contains(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(GarbageCollectionHandle,
                InDelegate);

        public void Add(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(GarbageCollectionHandle, InDelegate);

        public void Add(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(GarbageCollectionHandle, InDelegate);

        public void AddUnique(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(GarbageCollectionHandle,
                InDelegate);

        public void AddUnique(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(GarbageCollectionHandle,
                InDelegate);

        public void Remove(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(GarbageCollectionHandle, InDelegate);

        public void Remove(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(GarbageCollectionHandle, InDelegate);

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(GarbageCollectionHandle,
                InObject);

        public void Clear() =>
            MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}