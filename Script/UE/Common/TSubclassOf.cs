using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSubclassOf<T> : IGarbageCollectionHandle where T : UObject
    {
        public TSubclassOf()
        {
        }

        ~TSubclassOf() => TSubclassOfImplementation.TSubclassOf_UnRegisterImplementation(GarbageCollectionHandle);

        public TSubclassOf(UClass InClass) =>
            TSubclassOfImplementation.TSubclassOf_RegisterImplementation(this, InClass.GarbageCollectionHandle);

        public static implicit operator TSubclassOf<T>(UClass InClass) => new(InClass);

        public static bool operator ==(TSubclassOf<T> A, TSubclassOf<T> B) =>
            TSubclassOfImplementation.TSubclassOf_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TSubclassOf<T> A, TSubclassOf<T> B) =>
            !TSubclassOfImplementation.TSubclassOf_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TSubclassOf<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public UClass Get() => TSubclassOfImplementation.TSubclassOf_GetImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}