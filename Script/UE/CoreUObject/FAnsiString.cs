#if UE_5_6_OR_LATER
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class FAnsiString
    {
        public FAnsiString()
        {
        }

        ~FAnsiString() => FAnsiStringImplementation.FAnsiString_UnRegisterImplementation(HandleData.GetHandle(this));

        public FAnsiString(string InValue) =>
            FAnsiStringImplementation.FAnsiString_RegisterImplementation(this, InValue);

        public static implicit operator FAnsiString(string InValue) => new(InValue);

        public static bool operator ==(FAnsiString A, FAnsiString B)
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
                   FAnsiStringImplementation.FAnsiString_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(FAnsiString A, FAnsiString B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FAnsiString;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public override string ToString() =>
            FAnsiStringImplementation.FAnsiString_ToStringImplementation(HandleData.GetHandle(this));
    }
}
#endif