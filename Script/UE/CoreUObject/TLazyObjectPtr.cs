using Script.Library;

namespace Script.CoreUObject
{
    public class TLazyObjectPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        ~TLazyObjectPtr() =>
            TLazyObjectPtrImplementation.TLazyObjectPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TLazyObjectPtr(T InObject) =>
            TLazyObjectPtrImplementation.TLazyObjectPtr_RegisterImplementation(this, InObject.GarbageCollectionHandle);

        public static implicit operator TLazyObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            TLazyObjectPtrImplementation.TLazyObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            !TLazyObjectPtrImplementation.TLazyObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TLazyObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => TLazyObjectPtrImplementation.TLazyObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}