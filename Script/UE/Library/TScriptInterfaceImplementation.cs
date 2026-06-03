using System;
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class TScriptInterfaceImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            nint InObject, Type InType) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TScriptInterface_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TScriptInterface_UnRegisterImplementation(nint InScriptInterface);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TScriptInterface_GetObjectImplementation<T>(nint InScriptInterface);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void>
            __TScriptInterface_RegisterImplementation;

        public static unsafe void TScriptInterface_RegisterImplementation<T>(TScriptInterface<T> InScriptInterface,
            nint InObject, Type InType) where T : IInterface
        {
            if (__TScriptInterface_RegisterImplementation == null)
            {
                __TScriptInterface_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TScriptInterfaceImplementation::TScriptInterface_RegisterImplementation");
            }

            var Handle = HandleData.AllocImplementation(InScriptInterface);

            InScriptInterface.GarbageCollectionHandle = Handle;

            __TScriptInterface_RegisterImplementation(Handle, InObject, HandleData.AllocImplementation(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __TScriptInterface_IdenticalImplementation;

        public static unsafe bool TScriptInterface_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TScriptInterface_IdenticalImplementation == null)
            {
                __TScriptInterface_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TScriptInterfaceImplementation::TScriptInterface_IdenticalImplementation");
            }

            return __TScriptInterface_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TScriptInterface_UnRegisterImplementation;

        public static unsafe void TScriptInterface_UnRegisterImplementation(nint InScriptInterface)
        {
            if (__TScriptInterface_UnRegisterImplementation == null)
            {
                __TScriptInterface_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TScriptInterfaceImplementation::TScriptInterface_UnRegisterImplementation");
            }

            __TScriptInterface_UnRegisterImplementation(InScriptInterface);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TScriptInterface_GetObjectImplementation;

        public static unsafe T TScriptInterface_GetObjectImplementation<T>(nint InScriptInterface)
        {
            if (__TScriptInterface_GetObjectImplementation == null)
            {
                __TScriptInterface_GetObjectImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TScriptInterfaceImplementation::TScriptInterface_GetObjectImplementation");
            }

            var Handle = __TScriptInterface_GetObjectImplementation(InScriptInterface);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
#endif
    }
}