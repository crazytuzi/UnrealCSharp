using System;
using Script.Library;
using Script.Reflection.Property;
using Interop;

namespace Script.CoreUObject
{
    public class TFieldPath<T> : IDisposable where T : FField
    {
        public TFieldPath() =>
            TFieldPathImplementation.TFieldPath_Register1Implementation(HandleData.Alloc(this, true));

        public TFieldPath(T InObject) => TFieldPathImplementation.TFieldPath_Register2Implementation(
            HandleData.Alloc(this, true), HandleData.GetHandle(InObject));

        ~TFieldPath() => Dispose();

        private bool bIsDisposed;

        public void Dispose()
        {
            if (!bIsDisposed)
            {
                bIsDisposed = true;

                TFieldPathImplementation.TFieldPath_UnRegisterImplementation(HandleData.GetHandle(this));
            }

            GC.SuppressFinalize(this);
        }

        public static bool operator ==(TFieldPath<T> A, TFieldPath<T> B)
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
                   TFieldPathImplementation.TFieldPath_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TFieldPath<T> A, TFieldPath<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TFieldPath<T>;

        public override int GetHashCode() => 0;

        public bool IsValid() => TFieldPathImplementation.TFieldPath_IsValidImplementation(HandleData.GetHandle(this));

        public T Get() =>
            (T)HandleData.GetObject(TFieldPathImplementation.TFieldPath_GetImplementation(HandleData.GetHandle(this)));

        public void Set(T InObject) => TFieldPathImplementation.TFieldPath_SetImplementation(
            HandleData.GetHandle(this), HandleData.GetHandle(InObject));

        public void Reset() => TFieldPathImplementation.TFieldPath_ResetImplementation(HandleData.GetHandle(this));
    }
}