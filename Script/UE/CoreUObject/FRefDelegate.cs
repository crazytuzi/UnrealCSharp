using Script.Library;

namespace Script.CoreUObject
{
    public class FRefDelegate : FDelegateBase
    {
        public bool IsBound() => FDelegateImplementation.FDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public void Unbind() => FDelegateImplementation.FDelegate_UnBindImplementation(GarbageCollectionHandle);

        public void Clear() => FDelegateImplementation.FDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}