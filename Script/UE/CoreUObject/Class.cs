using Script.Library;

namespace Script.CoreUObject
{
    public partial class UClass
    {
        public void RemoveFunction(FName InName) =>
            UClassImplementation.UClass_RemoveFunctionImplementation(GarbageCollectionHandle,
                InName.GarbageCollectionHandle);
    }
}