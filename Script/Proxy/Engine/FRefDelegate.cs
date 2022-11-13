using System;
using Script.Reflection.Delegate;

namespace Script.Engine
{
    public class FRefDelegate : FDelegateBase
    {
        public unsafe Boolean IsBound()
        {
            return DelegateUtils.Delegate_IsBound(Address);
        }

        public unsafe void Unbind()
        {
            DelegateUtils.Delegate_UnBind(Address);
        }

        public unsafe void Clear()
        {
            DelegateUtils.Delegate_Clear(Address);
        }
    }
}