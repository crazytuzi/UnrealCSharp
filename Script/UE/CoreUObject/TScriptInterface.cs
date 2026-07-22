using Script.Library;
using Interop;

namespace Script.CoreUObject
{
    public class TScriptInterface<T> where T : IInterface
    {
        public TScriptInterface()
        {
        }

        ~TScriptInterface() =>
            TScriptInterfaceImplementation.TScriptInterface_UnRegisterImplementation(HandleData.GetHandle(this));

        public TScriptInterface(T InObject) =>
            TScriptInterfaceImplementation.TScriptInterface_RegisterImplementation(
                this, HandleData.GetHandle(InObject as UObject), GetType());

        public static implicit operator TScriptInterface<T>(T InObject) => new(InObject);

        public static bool operator ==(TScriptInterface<T> A, TScriptInterface<T> B)
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
                   TScriptInterfaceImplementation.TScriptInterface_IdenticalImplementation(
                       HandleData.GetHandle(A),
                       HandleData.GetHandle(B));
        }

        public static bool operator !=(TScriptInterface<T> A, TScriptInterface<T> B) => !(A == B);

        public override bool Equals(object Other) => this == Other as TScriptInterface<T>;

        public override int GetHashCode() => (int)HandleData.GetHandle(this);

        public U GetObject<U>() where U : UObject =>
            TScriptInterfaceImplementation.TScriptInterface_GetObjectImplementation<U>(HandleData.GetHandle(this));
    }
}