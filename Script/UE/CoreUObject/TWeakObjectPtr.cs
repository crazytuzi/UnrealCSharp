using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TWeakObjectPtr<T> where T : UObject
    {
        public TWeakObjectPtr()
        {
        }

        ~TWeakObjectPtr() =>
            TWeakObjectPtrImplementation.TWeakObjectPtr_UnRegisterImplementation(HandleData.GetHandle(this));

        public TWeakObjectPtr(T InObject) =>
            TWeakObjectPtrImplementation.TWeakObjectPtr_RegisterImplementation(
                this, HandleData.GetHandle(InObject), GetType());

        public static implicit operator TWeakObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B)
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
                   TWeakObjectPtrImplementation.TWeakObjectPtr_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TWeakObjectPtr<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public T Get() => TWeakObjectPtrImplementation.TWeakObjectPtr_GetImplementation<T>(HandleData.GetHandle(this));
    }
}