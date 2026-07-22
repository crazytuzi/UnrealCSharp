using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TSoftClassPtr<T> where T : UObject
    {
        public TSoftClassPtr()
        {
        }

        ~TSoftClassPtr() =>
            TSoftClassPtrImplementation.TSoftClassPtr_UnRegisterImplementation(HandleData.GetHandle(this));

        public TSoftClassPtr(UClass InClass) =>
            TSoftClassPtrImplementation.TSoftClassPtr_RegisterImplementation(
                this, HandleData.GetHandle(InClass), GetType());

        public static implicit operator TSoftClassPtr<T>(UClass InClass) => new(InClass);

        public static bool operator ==(TSoftClassPtr<T> A, TSoftClassPtr<T> B)
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
                   TSoftClassPtrImplementation.TSoftClassPtr_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TSoftClassPtr<T> A, TSoftClassPtr<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TSoftClassPtr<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public UClass Get() => TSoftClassPtrImplementation.TSoftClassPtr_GetImplementation(HandleData.GetHandle(this));

        public UClass LoadSynchronous() =>
            TSoftClassPtrImplementation.TSoftClassPtr_LoadSynchronousImplementation(HandleData.GetHandle(this));
    }
}