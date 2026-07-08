using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class TWeakObjectPtrImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void>
            __TWeakObjectPtr_RegisterImplementation;

        public static unsafe void TWeakObjectPtr_RegisterImplementation<T>(TWeakObjectPtr<T> InWeakObjectPtr,
            nint InObject, Type InType) where T : UObject
        {
            if (__TWeakObjectPtr_RegisterImplementation == null)
            {
                __TWeakObjectPtr_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TWeakObjectPtrImplementation::TWeakObjectPtr_RegisterImplementation");
            }

            __TWeakObjectPtr_RegisterImplementation(HandleData.Alloc(InWeakObjectPtr), InObject,
                HandleData.Alloc(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __TWeakObjectPtr_IdenticalImplementation;

        public static unsafe bool TWeakObjectPtr_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TWeakObjectPtr_IdenticalImplementation == null)
            {
                __TWeakObjectPtr_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TWeakObjectPtrImplementation::TWeakObjectPtr_IdenticalImplementation");
            }

            return __TWeakObjectPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TWeakObjectPtr_UnRegisterImplementation;

        public static unsafe void TWeakObjectPtr_UnRegisterImplementation(nint InWeakObjectPtr)
        {
            if (__TWeakObjectPtr_UnRegisterImplementation == null)
            {
                __TWeakObjectPtr_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TWeakObjectPtrImplementation::TWeakObjectPtr_UnRegisterImplementation");
            }

            __TWeakObjectPtr_UnRegisterImplementation(InWeakObjectPtr);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TWeakObjectPtr_GetImplementation;

        public static unsafe T TWeakObjectPtr_GetImplementation<T>(nint InWeakObjectPtr)
        {
            if (__TWeakObjectPtr_GetImplementation == null)
            {
                __TWeakObjectPtr_GetImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TWeakObjectPtrImplementation::TWeakObjectPtr_GetImplementation");
            }

            var Handle = __TWeakObjectPtr_GetImplementation(InWeakObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}