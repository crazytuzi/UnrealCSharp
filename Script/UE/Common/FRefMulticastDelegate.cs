using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FRefMulticastDelegate : FDelegateBase
    {
        public bool IsBound() =>
            MulticastDelegateImplementation.MulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public void RemoveAll(UObject InObject) =>
            MulticastDelegateImplementation.MulticastDelegate_RemoveAllImplementation(GarbageCollectionHandle,
                InObject);

        public void Clear() =>
            MulticastDelegateImplementation.MulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}