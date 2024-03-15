using Script.Library;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public UObject GetDefaultObject(bool bCreateIfNeeded = true) =>
            UClassImplementation.UClass_GetDefaultObjectImplementation(GarbageCollectionHandle, bCreateIfNeeded);
    }
}