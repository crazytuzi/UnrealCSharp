﻿using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FRefMulticastDelegate : FDelegateBase
    {
        public bool IsBound() =>
            FMulticastDelegateImplementation.FMulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public void RemoveAll(UObject InObject) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveAllImplementation(GarbageCollectionHandle,
                InObject);

        public void Clear() =>
            FMulticastDelegateImplementation.FMulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}