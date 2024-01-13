using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FName : IGarbageCollectionHandle
    {
        public FName()
        {
        }

        ~FName() => NameImplementation.Name_UnRegisterImplementation(GarbageCollectionHandle);

        public FName(string InValue) => NameImplementation.Name_RegisterImplementation(this, InValue);

        public static implicit operator FName(string InValue) => new(InValue);

        public static bool operator ==(FName A, FName B) =>
            NameImplementation.Name_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(FName A, FName B) =>
            !NameImplementation.Name_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as FName;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public override string ToString() => NameImplementation.Name_ToStringImplementation(GarbageCollectionHandle);

        public static FName NAME_None => NameImplementation.Name_NAME_NoneImplementation();

        public nint GarbageCollectionHandle { get; set; }
    }
}