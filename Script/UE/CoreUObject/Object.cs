using Script.Library;

namespace Script.CoreUObject
{
    public partial class UObject : IGarbageCollectionHandle
    {
        public static bool operator ==(UObject A, UObject B)
        {
            if (A is null && B is null)
            {
                return true;
            }

            if (A is null || B is null)
            {
                return false;
            }

            return ReferenceEquals(A, B) ||
                   UObjectImplementation.UObject_IdenticalImplementation(
                       A.GarbageCollectionHandle,
                       B.GarbageCollectionHandle);
        }

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

        public void AddToRoot() => UObjectImplementation.UObject_AddToRootImplementation(GarbageCollectionHandle);

        public void RemoveFromRoot() =>
            UObjectImplementation.UObject_RemoveFromRootImplementation(GarbageCollectionHandle);

        public bool IsRooted() => UObjectImplementation.UObject_IsRootedImplementation(GarbageCollectionHandle);

        public bool AddReference() => UObjectImplementation.UObject_AddReferenceImplementation(GarbageCollectionHandle);

        public bool RemoveReference() =>
            UObjectImplementation.UObject_RemoveReferenceImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}