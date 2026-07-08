using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TLazyObjectPtr<T> where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        ~TLazyObjectPtr() =>
            TLazyObjectPtrImplementation.TLazyObjectPtr_UnRegisterImplementation(HandleData.GetHandle(this));

        public TLazyObjectPtr(T InObject) =>
            TLazyObjectPtrImplementation.TLazyObjectPtr_RegisterImplementation(
                this, HandleData.GetHandle(InObject), GetType());

        public static implicit operator TLazyObjectPtr<T>(T InObject) => new(InObject);

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