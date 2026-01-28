using Script.Library;

namespace Script.CoreUObject
{
    public class TWeakObjectPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TWeakObjectPtr()
        {
        }

        ~TWeakObjectPtr() =>
            TWeakObjectPtrImplementation.TWeakObjectPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TWeakObjectPtr(T InObject) =>
            TWeakObjectPtrImplementation.TWeakObjectPtr_RegisterImplementation(this, InObject.GarbageCollectionHandle);

        public static implicit operator TWeakObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B)
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
                   TWeakObjectPtrImplementation.TWeakObjectPtr_IdenticalImplementation(
                       A.GarbageCollectionHandle,
                       B.GarbageCollectionHandle);
        }

        public static bool operator !=(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TWeakObjectPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public T Get() => TWeakObjectPtrImplementation.TWeakObjectPtr_GetImplementation<T>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}