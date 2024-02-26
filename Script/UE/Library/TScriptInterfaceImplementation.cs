using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TScriptInterfaceImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            nint InObject) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TScriptInterface_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TScriptInterface_UnRegisterImplementation(nint InScriptInterface);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TScriptInterface_GetObjectImplementation<T>(nint InScriptInterface);
    }
}