using Script.Library;
using Script.Common;
using Script.Engine;

namespace Script.CoreUObject
{
    public partial class UObject : IGarbageCollectionHandle
    {
        public UClass GetClass() => ObjectImplementation.Object_GetClassImplementation(GarbageCollectionHandle);

        public FString GetName() => ObjectImplementation.Object_GetNameImplementation(GarbageCollectionHandle);

        public UWorld GetWorld() => ObjectImplementation.Object_GetWorldImplementation(GarbageCollectionHandle);

        public override string ToString() => GetName().ToString();

        public bool IsValid() => ObjectImplementation.Object_IsValidImplementation(GarbageCollectionHandle);

        public bool IsA<T>() where T : UObject, IStaticClass =>
            ObjectImplementation.Object_IsAImplementation(GarbageCollectionHandle,
                T.StaticClass().GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}