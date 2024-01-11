using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public Boolean IsBound() =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(GetHandle());

        public Boolean Contains(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(GetHandle(), InDelegate);

        public Boolean Contains(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_ContainsImplementation(GetHandle(), InDelegate);

        public void Add(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(GetHandle(), InDelegate);

        public void Add(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddImplementation(GetHandle(), InDelegate);

        public void AddUnique(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(GetHandle(), InDelegate);

        public void AddUnique(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_AddUniqueImplementation(GetHandle(), InDelegate);

        public void Remove(UObject _, T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(GetHandle(), InDelegate);

        public void Remove(T InDelegate) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveImplementation(GetHandle(), InDelegate);

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(GetHandle(), InObject);

        public void Clear() => MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(GetHandle());
    }
}