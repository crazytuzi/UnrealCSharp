using Script.Library;

namespace Script.CoreUObject
{
    public class FUtf8String : IGarbageCollectionHandle
    {
        public FUtf8String()
        {
        }

        ~FUtf8String() => FUtf8StringImplementation.FUtf8String_UnRegisterImplementation(GarbageCollectionHandle);

        public FUtf8String(string InValue) => FUtf8StringImplementation.FUtf8String_RegisterImplementation(this, InValue);

        public static implicit operator FUtf8String(string InValue) => new(InValue);

        public static bool operator ==(FUtf8String A, FUtf8String B) =>
            Utils.EqualsTo(A, B, FUtf8StringImplementation.FUtf8String_IdenticalImplementation);

        public static bool operator !=(FUtf8String A, FUtf8String B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FUtf8String;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() =>
            FUtf8StringImplementation.FUtf8String_ToStringImplementation(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}