using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TScriptInterface<T> where T : IInterface
    {
        public TScriptInterface()
        {
        }

        ~TScriptInterface() => ScriptInterfaceImplementation.ScriptInterface_UnRegisterImplementation(this);

        public TScriptInterface(T InObject) =>
            ScriptInterfaceImplementation.ScriptInterface_RegisterImplementation(this, InObject,
                Utils.GetPathName(typeof(T)));

        public static implicit operator TScriptInterface<T>(T InObject) => new TScriptInterface<T>(InObject);

        public U GetObject<U>() where U : UObject
        {
            ScriptInterfaceImplementation.ScriptInterface_GetObjectImplementation<T, U>(this, out var OutValue);

            return OutValue;
        }
    }
}