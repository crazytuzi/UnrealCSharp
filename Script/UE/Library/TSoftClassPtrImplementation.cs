using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class TSoftClassPtrImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void> __TSoftClassPtr_RegisterImplementation;

        public static unsafe void TSoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            nint InClass, Type InType) where T : UObject
        {
            if (__TSoftClassPtr_RegisterImplementation == null)
            {
                __TSoftClassPtr_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftClassPtrImplementation::TSoftClassPtr_RegisterImplementation");
            }

            __TSoftClassPtr_RegisterImplementation(HandleData.Alloc(InSoftClassPtr), InClass,
                HandleData.Alloc(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __TSoftClassPtr_IdenticalImplementation;

        public static unsafe bool TSoftClassPtr_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TSoftClassPtr_IdenticalImplementation == null)
            {
                __TSoftClassPtr_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftClassPtrImplementation::TSoftClassPtr_IdenticalImplementation");
            }

            return __TSoftClassPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TSoftClassPtr_UnRegisterImplementation;

        public static unsafe void TSoftClassPtr_UnRegisterImplementation(nint InSoftClassPtr)
        {
            if (__TSoftClassPtr_UnRegisterImplementation == null)
            {
                __TSoftClassPtr_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftClassPtrImplementation::TSoftClassPtr_UnRegisterImplementation");
            }

            __TSoftClassPtr_UnRegisterImplementation(InSoftClassPtr);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TSoftClassPtr_GetImplementation;

        public static unsafe UClass TSoftClassPtr_GetImplementation(nint InSoftClassPtr)
        {
            if (__TSoftClassPtr_GetImplementation == null)
            {
                __TSoftClassPtr_GetImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftClassPtrImplementation::TSoftClassPtr_GetImplementation");
            }

            var Handle = __TSoftClassPtr_GetImplementation(InSoftClassPtr);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TSoftClassPtr_LoadSynchronousImplementation;

        public static unsafe UClass TSoftClassPtr_LoadSynchronousImplementation(nint InSoftClassPtr)
        {
            if (__TSoftClassPtr_LoadSynchronousImplementation == null)
            {
                __TSoftClassPtr_LoadSynchronousImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftClassPtrImplementation::TSoftClassPtr_LoadSynchronousImplementation");
            }

            var Handle = __TSoftClassPtr_LoadSynchronousImplementation(InSoftClassPtr);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }
    }
}