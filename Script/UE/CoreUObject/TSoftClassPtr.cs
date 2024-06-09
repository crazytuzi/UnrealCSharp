using Script.Library;

namespace Script.CoreUObject
{
    public class TSoftClassPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TSoftClassPtr()
        {
        }

        ~TSoftClassPtr() => TSoftClassPtrImplementation.TSoftClassPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TSoftClassPtr(UClass InClass) =>
            TSoftClassPtrImplementation.TSoftClassPtr_RegisterImplementation(this, InClass.GarbageCollectionHandle);

        public static implicit operator TSoftClassPtr<T>(UClass InClass) => new(InClass);

        public static bool operator ==(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            Utils.EqualsTo(A, B, TSoftClassPtrImplementation.TSoftClassPtr_IdenticalImplementation);

        public static bool operator !=(TSoftClassPtr<T> A, TSoftClassPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TSoftClassPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public UClass Get() => TSoftClassPtrImplementation.TSoftClassPtr_GetImplementation(GarbageCollectionHandle);

        public UClass LoadSynchronous() =>
            TSoftClassPtrImplementation.TSoftClassPtr_LoadSynchronousImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}