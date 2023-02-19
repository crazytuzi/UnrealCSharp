using System;
using Script.Reflection.Delegate;

namespace Script.Common
{
    public class FRefDelegate : FDelegateBase
    {
        public Boolean IsBound() => DelegateUtils.Delegate_IsBound(this);

        public void Unbind() => DelegateUtils.Delegate_UnBind(this);

        public void Clear() => DelegateUtils.Delegate_Clear(this);
    }
}