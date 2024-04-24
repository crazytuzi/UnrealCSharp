using Script.Library;

namespace Script.CoreUObject
{
    public partial class UObject : IGarbageCollectionHandle
    {
        public UClass GetClass() => UObjectImplementation.UObject_GetClassImplementation(GarbageCollectionHandle);

        public FString GetName() => UObjectImplementation.UObject_GetNameImplementation(GarbageCollectionHandle);

        public override string ToString() => GetName().ToString();

        public bool IsValid() => UObjectImplementation.UObject_IsValidImplementation(GarbageCollectionHandle);

        public bool IsA<T>() where T : UObject, IStaticClass =>
            UObjectImplementation.UObject_IsAImplementation(GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}