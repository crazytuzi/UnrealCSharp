using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class ScriptInterfaceImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            T InObject) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_UnRegisterImplementation<T>(TScriptInterface<T> InScriptInterface)
            where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_GetObjectImplementation<T, U>(TScriptInterface<T> InScriptInterface,
            out U OutValue) where T : IInterface where U : UObject;
    }
}