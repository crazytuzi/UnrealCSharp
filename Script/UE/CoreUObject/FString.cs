using System;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class FString : IDisposable
    {
        public FString()
        {
        }

        ~FString() => Dispose();

        private bool bIsDisposed;

        public void Dispose()
        {
            if (!bIsDisposed)
            {
                bIsDisposed = true;

                FStringImplementation.FString_UnRegisterImplementation(HandleData.GetHandle(this));
            }

            GC.SuppressFinalize(this);
        }

        public FString(string InValue) => FStringImplementation.FString_RegisterImplementation(this, InValue);

        public static implicit operator FString(string InValue) => new(InValue);

        public static bool operator ==(FString A, FString B)
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
                   FStringImplementation.FString_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(FString A, FString B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FString;

        public override int GetHashCode() =>
            FStringImplementation.FString_GetTypeHashImplementation(HandleData.GetHandle(this));

        public override string ToString() =>
            FStringImplementation.FString_ToStringImplementation(HandleData.GetHandle(this)) ?? string.Empty;
    }
}