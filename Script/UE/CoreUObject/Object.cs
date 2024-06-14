using Script.Library;

namespace Script.CoreUObject
{
    public partial class UObject : IGarbageCollectionHandle
    {
        public static bool operator ==(UObject A, UObject B) =>
            Utils.EqualsTo(A, B, UObjectImplementation.UObject_IdenticalImplementation);

        public static bool operator !=(UObject A, UObject B) => !(A == B);

        public override bool Equals(object Other) => this == Other as UObject;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

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