using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class ScriptInterfaceImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            T InObject, string InInterfaceName) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_UnRegisterImplementation(IntPtr InScriptInterface);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_GetObjectImplementation<U>(IntPtr InScriptInterface,
            out U OutValue) where U : UObject;
    }
}