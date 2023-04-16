using System;
using Script.CoreUObject;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FRefMulticastDelegate : FDelegateBase
    {
        public Boolean IsBound() => MulticastDelegateUtils.MulticastDelegate_IsBound(this);

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateUtils.MulticastDelegate_RemoveAll(this, InObject);

        public void Clear() => MulticastDelegateUtils.MulticastDelegate_Clear(this);
    }
}