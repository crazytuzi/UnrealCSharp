using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TWeakObjectPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TWeakObjectPtr()
        {
        }

        ~TWeakObjectPtr() =>
            WeakObjectPtrImplementation.WeakObjectPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TWeakObjectPtr(T InObject) =>
            WeakObjectPtrImplementation.WeakObjectPtr_RegisterImplementation(this, InObject.GarbageCollectionHandle);

        public static implicit operator TWeakObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B) =>
            WeakObjectPtrImplementation.WeakObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B) =>
            !WeakObjectPtrImplementation.WeakObjectPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TWeakObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => WeakObjectPtrImplementation.WeakObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}