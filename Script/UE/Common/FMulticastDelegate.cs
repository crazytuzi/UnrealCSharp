using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public Boolean IsBound() => MulticastDelegateUtils.MulticastDelegate_IsBound(GetHandle());

        public Boolean Contains(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Contains(GetHandle(), InDelegate);

        public Boolean Contains(T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Contains(GetHandle(), InDelegate);

        public void Add(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Add(GetHandle(), InDelegate);

        public void Add(T InDelegate) => MulticastDelegateUtils.MulticastDelegate_Add(GetHandle(), InDelegate);

        public void AddUnique(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_AddUnique(GetHandle(), InDelegate);

        public void AddUnique(T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_AddUnique(GetHandle(), InDelegate);

        public void Remove(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Remove(GetHandle(), InDelegate);

        public void Remove(T InDelegate) => MulticastDelegateUtils.MulticastDelegate_Remove(GetHandle(), InDelegate);

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateUtils.MulticastDelegate_RemoveAll(GetHandle(), InObject);

        public void Clear() => MulticastDelegateUtils.MulticastDelegate_Clear(GetHandle());
    }
}