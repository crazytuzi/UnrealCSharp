using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class TLazyObjectPtrImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void>
            __TLazyObjectPtr_RegisterImplementation;

        public static unsafe void TLazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr,
            nint InObject, Type InType) where T : UObject
        {
            if (__TLazyObjectPtr_RegisterImplementation == null)
            {
                __TLazyObjectPtr_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TLazyObjectPtrImplementation::TLazyObjectPtr_RegisterImplementation");
            }

            __TLazyObjectPtr_RegisterImplementation(HandleData.Alloc(InLazyObjectPtr), InObject,
                HandleData.Alloc(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __TLazyObjectPtr_IdenticalImplementation;

        public static unsafe bool TLazyObjectPtr_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TLazyObjectPtr_IdenticalImplementation == null)
            {
                __TLazyObjectPtr_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TLazyObjectPtrImplementation::TLazyObjectPtr_IdenticalImplementation");
            }

            return __TLazyObjectPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TLazyObjectPtr_UnRegisterImplementation;

        public static unsafe void TLazyObjectPtr_UnRegisterImplementation(nint InLazyObjectPtr)
        {
            if (__TLazyObjectPtr_UnRegisterImplementation == null)
            {
                __TLazyObjectPtr_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TLazyObjectPtrImplementation::TLazyObjectPtr_UnRegisterImplementation");
            }

            __TLazyObjectPtr_UnRegisterImplementation(InLazyObjectPtr);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TLazyObjectPtr_GetImplementation;

        public static unsafe T TLazyObjectPtr_GetImplementation<T>(nint InLazyObjectPtr)
        {
            if (__TLazyObjectPtr_GetImplementation == null)
            {
                __TLazyObjectPtr_GetImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TLazyObjectPtrImplementation::TLazyObjectPtr_GetImplementation");
            }

            var Handle = __TLazyObjectPtr_GetImplementation(InLazyObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}