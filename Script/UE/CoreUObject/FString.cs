using Script.Library;

namespace Script.CoreUObject
{
    public class FString : IGarbageCollectionHandle
    {
        public FString()
        {
        }

        ~FString() => FStringImplementation.FString_UnRegisterImplementation(GarbageCollectionHandle);

        public FString(string InValue) => FStringImplementation.FString_RegisterImplementation(this, InValue);

        public static implicit operator FString(string InValue) => new(InValue);

        public static bool operator ==(FString A, FString B) =>
            FStringImplementation.FString_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(FString A, FString B) =>
            !FStringImplementation.FString_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as FString;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() =>
            FStringImplementation.FString_ToStringImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}