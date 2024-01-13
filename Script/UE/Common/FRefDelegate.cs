using Script.Library;

namespace Script.Common
{
    public class FRefDelegate : FDelegateBase
    {
        public bool IsBound() => DelegateImplementation.Delegate_IsBoundImplementation(GarbageCollectionHandle);

        public void Unbind() => DelegateImplementation.Delegate_UnBindImplementation(GarbageCollectionHandle);

        public void Clear() => DelegateImplementation.Delegate_ClearImplementation(GarbageCollectionHandle);
    }
}