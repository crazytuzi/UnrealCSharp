using Script.Library;

namespace Script.CoreUObject
{
    public class TScriptInterface<T> : IGarbageCollectionHandle where T : IInterface
    {
        public TScriptInterface()
        {
        }

        ~TScriptInterface() =>
            TScriptInterfaceImplementation.TScriptInterface_UnRegisterImplementation(GarbageCollectionHandle);

        public TScriptInterface(T InObject) =>
            TScriptInterfaceImplementation.TScriptInterface_RegisterImplementation(this,
                (InObject as UObject)!.GarbageCollectionHandle);

        public static implicit operator TScriptInterface<T>(T InObject) => new(InObject);

        public static bool operator ==(TScriptInterface<T> A, TScriptInterface<T> B) =>
            Utils.EqualsTo(A, B, TScriptInterfaceImplementation.TScriptInterface_IdenticalImplementation);

        public static bool operator !=(TScriptInterface<T> A, TScriptInterface<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TScriptInterface<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public U GetObject<U>() where U : UObject =>
            TScriptInterfaceImplementation.TScriptInterface_GetObjectImplementation<U>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}