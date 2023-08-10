using System;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FRefDelegate : FDelegateBase
    {
        public Boolean IsBound() => DelegateUtils.Delegate_IsBound(GetHandle());

        public void Unbind() => DelegateUtils.Delegate_UnBind(GetHandle());

        public void Clear() => DelegateUtils.Delegate_Clear(GetHandle());
    }
}