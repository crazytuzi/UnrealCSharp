using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class TScriptInterfaceImplementation
    {
        private static unsafe partial void __TScriptInterface_RegisterImplementation(nint InScriptInterface, nint InObject, nint InType);

        public static unsafe void TScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            nint InObject, Type InType) where T : IInterface
        {
            __TScriptInterface_RegisterImplementation(HandleData.Alloc(InScriptInterface), InObject,
                HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TScriptInterface_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool TScriptInterface_IdenticalImplementation(nint InA, nint InB)
        {
            return __TScriptInterface_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TScriptInterface_UnRegisterImplementation(nint InScriptInterface);

        public static unsafe void TScriptInterface_UnRegisterImplementation(nint InScriptInterface)
        {
            __TScriptInterface_UnRegisterImplementation(InScriptInterface);
        }

        private static unsafe partial nint __TScriptInterface_GetObjectImplementation(nint InScriptInterface);

        public static unsafe T TScriptInterface_GetObjectImplementation<T>(nint InScriptInterface)
        {
            var Handle = __TScriptInterface_GetObjectImplementation(InScriptInterface);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}