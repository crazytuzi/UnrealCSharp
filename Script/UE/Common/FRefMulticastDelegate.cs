using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FRefMulticastDelegate : FDelegateBase
    {
        public Boolean IsBound() =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(GetHandle());

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(GetHandle(), InObject);

        public void Clear() => MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(GetHandle());
    }
}