using System;
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class TSoftClassPtrImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            nint InClass, Type InType) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSoftClassPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftClassPtr_UnRegisterImplementation(nint InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass TSoftClassPtr_GetImplementation(nint InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass TSoftClassPtr_LoadSynchronousImplementation(nint InSoftClassPtr);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void> __TSoftClassPtr_RegisterImplementation;

        public static unsafe void TSoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            nint InObject, Type InType) where T : UObject
        {
            if (__TSoftClassPtr_RegisterImplementation == null)
            {
                __TSoftClassPtr_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftClassPtrImplementation::TSoftClassPtr_RegisterImplementation");
            }

            var Handle = HandleData.AllocImplementation(InSoftClassPtr);

            InSoftClassPtr.GarbageCollectionHandle = Handle;

            __TSoftClassPtr_RegisterImplementation(Handle, InObject, HandleData.AllocImplementation(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __TSoftClassPtr_IdenticalImplementation;

        public static unsafe bool TSoftClassPtr_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TSoftClassPtr_IdenticalImplementation == null)
            {
                __TSoftClassPtr_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
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
#endif
    }
}