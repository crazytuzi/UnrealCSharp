using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSoftClassPtr<T> : IGarbageCollectionHandle where T : UObject
    {
        public TSoftClassPtr()
        {
        }

        ~TSoftClassPtr() => SoftClassPtrImplementation.SoftClassPtr_UnRegisterImplementation(GarbageCollectionHandle);

        public TSoftClassPtr(UClass InClass) =>
            SoftClassPtrImplementation.SoftClassPtr_RegisterImplementation(this, InClass.GarbageCollectionHandle);

        public static implicit operator TSoftClassPtr<T>(UClass InClass) => new(InClass);

        public static bool operator ==(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            SoftClassPtrImplementation.SoftClassPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            !SoftClassPtrImplementation.SoftClassPtr_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TSoftClassPtr<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public UClass Get() => SoftClassPtrImplementation.SoftClassPtr_GetImplementation(GarbageCollectionHandle);

        public UClass LoadSynchronous() =>
            SoftClassPtrImplementation.SoftClassPtr_LoadSynchronousImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}