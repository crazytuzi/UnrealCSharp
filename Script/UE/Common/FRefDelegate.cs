using System;
using Script.Library;

namespace Script.Common
{
    public class FRefDelegate : FDelegateBase
    {
        public Boolean IsBound() => DelegateImplementation.Delegate_IsBoundImplementation(GetHandle());

        public void Unbind() => DelegateImplementation.Delegate_UnBindImplementation(GetHandle());

        public void Clear() => DelegateImplementation.Delegate_ClearImplementation(GetHandle());
    }
}