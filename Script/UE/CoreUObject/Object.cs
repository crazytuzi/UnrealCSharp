using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public partial class UObject
    {
        public static bool operator ==(UObject A, UObject B)
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
                   UObjectImplementation.UObject_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(UObject A, UObject B) => !(A == B);

        public override bool Equals(object Other) => this == Other as UObject;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public UClass GetClass() => UObjectImplementation.UObject_GetClassImplementation(HandleData.GetHandle(this));

        public FString GetName() => UObjectImplementation.UObject_GetNameImplementation(HandleData.GetHandle(this));

        public override string ToString() => GetName().ToString();

        public bool IsValid() => UObjectImplementation.UObject_IsValidImplementation(HandleData.GetHandle(this));

        public bool IsA<T>() where T : UObject, IStaticClass =>
            UObjectImplementation.UObject_IsAImplementation(HandleData.GetHandle(this),
                HandleData.GetHandle(T.StaticClass()));

        public void AddToRoot() => UObjectImplementation.UObject_AddToRootImplementation(HandleData.GetHandle(this));

        public void RemoveFromRoot() =>
            UObjectImplementation.UObject_RemoveFromRootImplementation(HandleData.GetHandle(this));

        public bool IsRooted() => UObjectImplementation.UObject_IsRootedImplementation(HandleData.GetHandle(this));

        public bool AddReference() =>
            UObjectImplementation.UObject_AddReferenceImplementation(HandleData.GetHandle(this));

        public bool RemoveReference() =>
            UObjectImplementation.UObject_RemoveReferenceImplementation(HandleData.GetHandle(this));
    }
}