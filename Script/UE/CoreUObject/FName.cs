using Script.Library;

namespace Script.CoreUObject
{
    public class FName : IGarbageCollectionHandle
    {
        public FName()
        {
        }

        ~FName() => FNameImplementation.FName_UnRegisterImplementation(GarbageCollectionHandle);

        public FName(string InValue) => FNameImplementation.FName_RegisterImplementation(this, InValue);

        public static implicit operator FName(string InValue) => new(InValue);

        public static bool operator ==(FName A, FName B) =>
            Utils.EqualsTo(A, B, FNameImplementation.FName_IdenticalImplementation);

        public static bool operator !=(FName A, FName B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FName;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() => FNameImplementation.FName_ToStringImplementation(GarbageCollectionHandle);

        public static FName NAME_None => FNameImplementation.FName_NAME_NoneImplementation();

        public nint GarbageCollectionHandle { get; set; }
    }
}