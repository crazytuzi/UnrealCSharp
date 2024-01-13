using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FString : IGarbageCollectionHandle
    {
        public FString()
        {
        }

        ~FString() => StringImplementation.String_UnRegisterImplementation(GarbageCollectionHandle);

        public FString(string InValue) => StringImplementation.String_RegisterImplementation(this, InValue);

        public static implicit operator FString(string InValue) => new(InValue);

        public static bool operator ==(FString A, FString B) =>
            StringImplementation.String_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(FString A, FString B) =>
            !StringImplementation.String_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as FString;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() =>
            StringImplementation.String_ToStringImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}