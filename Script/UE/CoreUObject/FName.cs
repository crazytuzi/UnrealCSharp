using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class FName
    {
        public FName()
        {
        }

        ~FName() => FNameImplementation.FName_UnRegisterImplementation(HandleData.GetHandle(this));

        public FName(string InValue) => FNameImplementation.FName_RegisterImplementation(this, InValue);

        public static implicit operator FName(string InValue) => new(InValue);

        public static bool operator ==(FName A, FName B)
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
                   FNameImplementation.FName_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(FName A, FName B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FName;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public override string ToString() =>
            FNameImplementation.FName_ToStringImplementation(HandleData.GetHandle(this));

        public static FName NAME_None => FNameImplementation.FName_NAME_NoneImplementation();
    }
}