using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FMulticastDelegate<T> : FMulticastDelegateBase where T : Delegate
    {
        public unsafe Boolean IsBound() => MulticastDelegateUtils.MulticastDelegate_IsBound(Address);

        public unsafe Boolean Contains(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Contains(Address, InDelegate);

        public unsafe Boolean Contains(T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Contains(Address, InDelegate);

        public unsafe void Add(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Add(Address, InDelegate);

        public unsafe void Add(T InDelegate) => MulticastDelegateUtils.MulticastDelegate_Add(Address, InDelegate);

        public unsafe void AddUnique(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_AddUnique(Address, InDelegate);

        public unsafe void AddUnique(T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_AddUnique(Address, InDelegate);

        public unsafe void Remove(UObject _, T InDelegate) =>
            MulticastDelegateUtils.MulticastDelegate_Remove(Address, InDelegate);

        public unsafe void Remove(T InDelegate) => MulticastDelegateUtils.MulticastDelegate_Remove(Address, InDelegate);

        public unsafe void RemoveAll(UObject InObject) =>
            MulticastDelegateUtils.MulticastDelegate_RemoveAll(Address, InObject);

        public unsafe void Clear() => MulticastDelegateUtils.MulticastDelegate_Clear(Address);
    }
}