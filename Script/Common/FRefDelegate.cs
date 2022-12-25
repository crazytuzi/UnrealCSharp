using System;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FRefDelegate : FDelegateBase
    {
        public unsafe Boolean IsBound() => DelegateUtils.Delegate_IsBound(Address);

        public unsafe void Unbind() => DelegateUtils.Delegate_UnBind(Address);

        public unsafe void Clear() => DelegateUtils.Delegate_Clear(Address);
    }
}