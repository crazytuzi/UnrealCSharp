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
            IntPtr InObject) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean ScriptInterface_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ScriptInterface_UnRegisterImplementation(IntPtr InScriptInterface);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object ScriptInterface_GetObjectImplementation(IntPtr InScriptInterface);
    }
}