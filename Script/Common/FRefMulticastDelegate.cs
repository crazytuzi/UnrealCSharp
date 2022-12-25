using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FRefMulticastDelegate : FMulticastDelegateBase
    {
        public unsafe Boolean IsBound() => MulticastDelegateUtils.MulticastDelegate_IsBound(Address);

        public unsafe void RemoveAll(UObject InObject) =>
            MulticastDelegateUtils.MulticastDelegate_RemoveAll(Address, InObject);

        public unsafe void Clear() => MulticastDelegateUtils.MulticastDelegate_Clear(Address);
    }
}