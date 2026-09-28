using System;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class FText : IDisposable
    {
        public FText()
        {
        }

        ~FText() => Dispose();

        private bool bIsDisposed;

        public void Dispose()
        {
            if (!bIsDisposed)
            {
                bIsDisposed = true;

                FTextImplementation.FText_UnRegisterImplementation(HandleData.GetHandle(this));
            }

            GC.SuppressFinalize(this);
        }

        public FText(string InBuffer, string InTextNamespace = null, string InPackageNamespace = null,
            bool bRequiresQuotes = false) =>
            FTextImplementation.FText_RegisterImplementation(this, InBuffer, InTextNamespace, InPackageNamespace,
                bRequiresQuotes);

        public static implicit operator FText(string InValue) => new(InValue);

        public static bool operator ==(FText A, FText B)
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
                   FTextImplementation.FText_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(FText A, FText B) => !(A == B);

        public override bool Equals(object Other) => this == Other as FText;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public override string ToString() =>
            FTextImplementation.FText_ToStringImplementation(HandleData.GetHandle(this)) ?? string.Empty;
    }
}