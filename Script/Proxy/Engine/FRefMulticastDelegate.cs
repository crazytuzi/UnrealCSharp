using System;
using Script.Reflection.Delegate;

namespace Script.Engine
{
    public class FRefMulticastDelegate : FMulticastDelegateBase
    {
        public unsafe Boolean IsBound() => MulticastDelegateUtils.MulticastDelegate_IsBound(Address);

        public unsafe void RemoveAll(UObject InObject) =>
            MulticastDelegateUtils.MulticastDelegate_RemoveAll(Address, InObject);

        public unsafe void Clear() => MulticastDelegateUtils.MulticastDelegate_Clear(Address);
    }
}