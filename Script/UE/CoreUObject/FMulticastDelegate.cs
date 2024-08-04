using System;
using Script.Library;

namespace Script.CoreUObject
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public bool IsBound() =>
            FMulticastDelegateImplementation.FMulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public bool Contains(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_ContainsImplementation(
                GarbageCollectionHandle,
                (InDelegate.Target as UObject)?.GarbageCollectionHandle ?? nint.Zero,
                InDelegate);

        public void Add(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddImplementation(
                GarbageCollectionHandle,
                (InDelegate.Target as UObject)?.GarbageCollectionHandle ?? nint.Zero,
                InDelegate);

        public void AddUnique(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_AddUniqueImplementation(
                GarbageCollectionHandle,
                (InDelegate.Target as UObject)?.GarbageCollectionHandle ?? nint.Zero,
                InDelegate);

        public void Remove(T InDelegate) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveImplementation(
                GarbageCollectionHandle,
                (InDelegate.Target as UObject)?.GarbageCollectionHandle ?? nint.Zero,
                InDelegate);

        public void RemoveAll(UObject InObject) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveAllImplementation(
                GarbageCollectionHandle, InObject.GarbageCollectionHandle);

        public void Clear() =>
            FMulticastDelegateImplementation.FMulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}