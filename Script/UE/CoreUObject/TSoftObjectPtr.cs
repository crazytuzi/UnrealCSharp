using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TSoftObjectPtr<T> where T : UObject
    {
        public TSoftObjectPtr()
        {
        }

        ~TSoftObjectPtr() =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_UnRegisterImplementation(HandleData.GetHandle(this));

        public TSoftObjectPtr(T InObject) =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_RegisterImplementation(
                this, HandleData.GetHandle(InObject), GetType());

        public static implicit operator TSoftObjectPtr<T>(T InObject) => new(InObject);

        public static bool operator ==(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B)
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
                   TSoftObjectPtrImplementation.TSoftObjectPtr_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TSoftObjectPtr<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public T Get() => TSoftObjectPtrImplementation.TSoftObjectPtr_GetImplementation<T>(HandleData.GetHandle(this));

        public T LoadSynchronous() =>
            TSoftObjectPtrImplementation.TSoftObjectPtr_LoadSynchronousImplementation<T>(HandleData.GetHandle(this));
    }
}