using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TScriptInterface<T> : IGCHandle where T : IInterface
    {
        public TScriptInterface()
        {
        }

        ~TScriptInterface() => ScriptInterfaceImplementation.ScriptInterface_UnRegisterImplementation(GetHandle());

        public TScriptInterface(T InObject) =>
            ScriptInterfaceImplementation.ScriptInterface_RegisterImplementation(this, InObject,
                Utils.GetPathName(typeof(T)));

        public static implicit operator TScriptInterface<T>(T InObject) => new TScriptInterface<T>(InObject);

        public U GetObject<U>() where U : UObject
        {
            ScriptInterfaceImplementation.ScriptInterface_GetObjectImplementation<U>(GetHandle(), out var OutValue);

            return OutValue;
        }

        public unsafe void SetHandle(void* InGCHandle)
        {
            GCHandle = new System.IntPtr(InGCHandle);
        }

        public System.IntPtr GetHandle()
        {
            return GCHandle;
        }

        private System.IntPtr GCHandle;
    }
}