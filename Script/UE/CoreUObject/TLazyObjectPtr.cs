using System;
using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TLazyObjectPtr<T> : IDisposable where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        ~TLazyObjectPtr() => Dispose();

        private bool bIsDisposed;

        public void Dispose()
        {
            if (!bIsDisposed)
            {
                bIsDisposed = true;

                TLazyObjectPtrImplementation.TLazyObjectPtr_UnRegisterImplementation(HandleData.GetHandle(this));
            }

            GC.SuppressFinalize(this);
        }

        public TLazyObjectPtr(T InObject) =>
            TLazyObjectPtrImplementation.TLazyObjectPtr_RegisterImplementation(
                this, HandleData.GetHandle(InObject), GetType());

        public static explicit operator TLazyObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B)
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
                   TLazyObjectPtrImplementation.TLazyObjectPtr_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TLazyObjectPtr<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public T Get() => TLazyObjectPtrImplementation.TLazyObjectPtr_GetImplementation<T>(HandleData.GetHandle(this));
    }
}