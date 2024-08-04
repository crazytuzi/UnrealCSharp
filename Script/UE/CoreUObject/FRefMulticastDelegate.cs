using Script.Library;

namespace Script.CoreUObject
{
    public class FRefMulticastDelegate : FDelegateBase
    {
        public bool IsBound() =>
            FMulticastDelegateImplementation.FMulticastDelegate_IsBoundImplementation(GarbageCollectionHandle);

        public void RemoveAll(UObject InObject) =>
            FMulticastDelegateImplementation.FMulticastDelegate_RemoveAllImplementation(
                GarbageCollectionHandle, InObject.GarbageCollectionHandle);

        public void Clear() =>
            FMulticastDelegateImplementation.FMulticastDelegate_ClearImplementation(GarbageCollectionHandle);
    }
}