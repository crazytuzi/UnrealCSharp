using Script.Library;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public UObject GetDefaultObject(bool bCreateIfNeeded = true) =>
            ClassImplementation.Class_GetDefaultObjectImplementation(GarbageCollectionHandle, bCreateIfNeeded);
    }
}