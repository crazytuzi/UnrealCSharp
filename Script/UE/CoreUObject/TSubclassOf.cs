using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TSubclassOf<T> where T : UObject
    {
        public TSubclassOf()
        {
        }

        ~TSubclassOf() => TSubclassOfImplementation.TSubclassOf_UnRegisterImplementation(HandleData.GetHandle(this));

        public TSubclassOf(UClass InClass) =>
            TSubclassOfImplementation.TSubclassOf_RegisterImplementation(
                this, HandleData.GetHandle(InClass), GetType());

        public static implicit operator TSubclassOf<T>(UClass InClass) => new(InClass);

        public static bool operator ==(TSubclassOf<T> A, TSubclassOf<T> B)
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
                   TSubclassOfImplementation.TSubclassOf_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TSubclassOf<T> A, TSubclassOf<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TSubclassOf<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public UClass Get() => TSubclassOfImplementation.TSubclassOf_GetImplementation(HandleData.GetHandle(this));
    }
}