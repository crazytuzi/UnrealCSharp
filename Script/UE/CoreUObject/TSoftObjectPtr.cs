using Script.Library;

namespace Script.CoreUObject
{
    public class TSoftObjectPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TSoftObjectPtr()
        {
        }

        ~TSoftObjectPtr() =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TSoftObjectPtr(T InObject) =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_RegisterImplementation(this, InObject.GarbageCollectionHandle);

        public static implicit operator TSoftObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) =>
            Utils.EqualsTo(A, B, TSoftObjectPtrImplementation.TSoftObjectPtr_IdenticalImplementation);

        public static bool operator !=(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TSoftObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => TSoftObjectPtrImplementation.TSoftObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public T LoadSynchronous() =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_LoadSynchronousImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}