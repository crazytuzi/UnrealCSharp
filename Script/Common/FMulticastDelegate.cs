using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FMulticastDelegate<T> : FDelegateBase where T : Delegate
    {
        public Boolean IsBound() => MulticastDelegateUtils.MulticastDelegate_IsBound(this);

        public Boolean Contains(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Contains(this, InDelegate);

        public Boolean Contains(T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Contains(this, InDelegate);

        public void Add(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Add(this, InDelegate);

        public void Add(T InDelegate) => MulticastDelegateUtils.MulticastDelegate_Add(this, InDelegate);

        public void AddUnique(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_AddUnique(this, InDelegate);

        public void AddUnique(T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_AddUnique(this, InDelegate);

        public void Remove(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Remove(this, InDelegate);

        public void Remove(T InDelegate) => MulticastDelegateUtils.MulticastDelegate_Remove(this, InDelegate);

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateUtils.MulticastDelegate_RemoveAll(this, InObject);

        public void Clear() => MulticastDelegateUtils.MulticastDelegate_Clear(this);
    }
}