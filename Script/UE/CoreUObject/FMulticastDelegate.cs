using System;
using Script.Library;

namespace Script.CoreUObject
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public bool IsBound() =>
            FMulticastDelegateImplementation.FMulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public bool Contains(UObject InObject, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(
                GarbageCollectionHandle,
                InObject.GarbageCollectionHandle,
                InDelegate);

        public void Add(UObject InObject, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(
                GarbageCollectionHandle,
                InObject.GarbageCollectionHandle,
                InDelegate);

        public void AddUnique(UObject InObject, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(
                GarbageCollectionHandle,
                InObject.GarbageCollectionHandle,
                InDelegate);

        public void Remove(UObject InObject, T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(
                GarbageCollectionHandle,
                InObject.GarbageCollectionHandle,
                InDelegate);

        public void RemoveAll(UObject InObject) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveAllImplementation(
                GarbageCollectionHandle, InObject.GarbageCollectionHandle);

        public void Clear() =>
            FMulticastDelegateImplementation.FMulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}