#if UE_5_6_OR_LATER
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class FUtf8String
    {
        public FUtf8String()
        {
        }

        ~FUtf8String() => FUtf8StringImplementation.FUtf8String_UnRegisterImplementation(HandleData.GetHandle(this));

        public FUtf8String(string InValue) =>
            FUtf8StringImplementation.FUtf8String_RegisterImplementation(this, InValue);

        public static implicit operator FUtf8String(string InValue) => new(InValue);

        public static bool operator ==(FUtf8String A, FUtf8String B)
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
                   FUtf8StringImplementation.FUtf8String_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(FUtf8String A, FUtf8String B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FUtf8String;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public override string ToString() =>
            FUtf8StringImplementation.FUtf8String_ToStringImplementation(HandleData.GetHandle(this));
    }
}
#endif