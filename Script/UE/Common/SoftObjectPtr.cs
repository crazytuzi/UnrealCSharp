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
            SoftObjectPtrImplementation.SoftObjectPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TSoftObjectPtr(T InObject) =>
            SoftObjectPtrImplementation.SoftObjectPtr_RegisterImplementation(this, InObject.GarbageCollectionHandle);

        public static implicit operator TSoftObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) =>
            SoftObjectPtrImplementation.SoftObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) =>
            !SoftObjectPtrImplementation.SoftObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TSoftObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => SoftObjectPtrImplementation.SoftObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public T LoadSynchronous() =>
            SoftObjectPtrImplementation.SoftObjectPtr_LoadSynchronousImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}