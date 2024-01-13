using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class ScriptInterfaceImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            nint InObject) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool ScriptInterface_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_UnRegisterImplementation(nint InScriptInterface);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T ScriptInterface_GetObjectImplementation<T>(nint InScriptInterface);
    }
}