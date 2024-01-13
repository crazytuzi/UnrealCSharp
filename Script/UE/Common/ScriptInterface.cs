using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TScriptInterface<T> : IGarbageCollectionHandle where T : IInterface
    {
        public TScriptInterface()
        {
        }

        ~TScriptInterface() =>
            ScriptInterfaceImplementation.ScriptInterface_UnRegisterImplementation(GarbageCollectionHandle);

        public TScriptInterface(T InObject) =>
            ScriptInterfaceImplementation.ScriptInterface_RegisterImplementation(this,
                (InObject as UObject)!.GarbageCollectionHandle);

        public static implicit operator TScriptInterface<T>(T InObject) => new(InObject);

        public static bool operator ==(TScriptInterface<T> A, TScriptInterface<T> B) =>
            ScriptInterfaceImplementation.ScriptInterface_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public static bool operator !=(TScriptInterface<T> A, TScriptInterface<T> B) =>
            !ScriptInterfaceImplementation.ScriptInterface_IdenticalImplementation(
                A?.GarbageCollectionHandle ?? nint.Zero, B?.GarbageCollectionHandle ?? nint.Zero);

        public override bool Equals(object Other) => this == Other as TScriptInterface<T>;

        public override int GetHashCode() => (int)GarbageCollectionHandle;

        public U GetObject<U>() where U : UObject =>
            ScriptInterfaceImplementation.ScriptInterface_GetObjectImplementation<U>(GarbageCollectionHandle);

        public nint GarbageCollectionHandle { get; set; }
    }
}