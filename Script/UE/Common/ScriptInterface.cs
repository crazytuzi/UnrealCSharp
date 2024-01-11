using System;
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
            ScriptInterfaceImplementation.ScriptInterface_RegisterImplementation(this, InObject.GetHashCode());

        public static implicit operator TScriptInterface<T>(T InObject) => new(InObject);

        public static Boolean operator ==(TScriptInterface<T> A, TScriptInterface<T> B) =>
            ScriptInterfaceImplementation.ScriptInterface_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TScriptInterface<T> A, TScriptInterface<T> B) =>
            !ScriptInterfaceImplementation.ScriptInterface_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TScriptInterface<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public U GetObject<U>() where U : UObject
        {
            return ScriptInterfaceImplementation.ScriptInterface_GetObjectImplementation(GetHandle()) as U;
        }

        public unsafe void SetHandle(void* InGCHandle)
        {
            GCHandle = new IntPtr(InGCHandle);
        }

        public IntPtr GetHandle()
        {
            return GCHandle;
        }

        private IntPtr GCHandle;
    }
}