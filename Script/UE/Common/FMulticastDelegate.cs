using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public bool IsBound() =>
            FMulticastDelegateImplementation.FMulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public bool Contains(UObject _, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(GarbageCollectionHandle,
                InDelegate);

        public bool Contains(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(GarbageCollectionHandle,
                InDelegate);

        public void Add(UObject _, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(GarbageCollectionHandle, InDelegate);

        public void Add(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(GarbageCollectionHandle, InDelegate);

        public void AddUnique(UObject _, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(GarbageCollectionHandle,
                InDelegate);

        public void AddUnique(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(GarbageCollectionHandle,
                InDelegate);

        public void Remove(UObject _, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(GarbageCollectionHandle, InDelegate);

        public void Remove(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(GarbageCollectionHandle, InDelegate);

        public void RemoveAll(UObject InObject) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveAllImplementation(GarbageCollectionHandle,
                InObject);

        public void Clear() =>
            FMulticastDelegateImplementation.FMulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}