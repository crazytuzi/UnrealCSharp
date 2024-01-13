using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TLazyObjectPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        ~TLazyObjectPtr() =>
            LazyObjectPtrImplementation.LazyObjectPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TLazyObjectPtr(T InObject) =>
            LazyObjectPtrImplementation.LazyObjectPtr_RegisterImplementation(this, InObject.GarbageCollectionHandle);

        public static implicit operator TLazyObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            LazyObjectPtrImplementation.LazyObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            !LazyObjectPtrImplementation.LazyObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TLazyObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => LazyObjectPtrImplementation.LazyObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}