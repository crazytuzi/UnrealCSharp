using Script.CoreUObject;
using Script.Library;

namespace Script.Common
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
            TSoftObjectPtrImplementation.TSoftObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) =>
            !TSoftObjectPtrImplementation.TSoftObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TSoftObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => TSoftObjectPtrImplementation.TSoftObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public T LoadSynchronous() =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_LoadSynchronousImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}