using System;
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class TSoftObjectPtrImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftObjectPtr_RegisterImplementation<T>(TSoftObjectPtr<T> InSoftObjectPtr,
            nint InObject, Type InType) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSoftObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftObjectPtr_UnRegisterImplementation(nint InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TSoftObjectPtr_GetImplementation<T>(nint InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TSoftObjectPtr_LoadSynchronousImplementation<T>(nint InSoftObjectPtr);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void>
            __TSoftObjectPtr_RegisterImplementation;

        public static unsafe void TSoftObjectPtr_RegisterImplementation<T>(TSoftObjectPtr<T> InSoftObjectPtr,
            nint InObject, Type InType) where T : UObject
        {
            if (__TSoftObjectPtr_RegisterImplementation == null)
            {
                __TSoftObjectPtr_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftObjectPtrImplementation::TSoftObjectPtr_RegisterImplementation");
            }

            var Handle = HandleData.AllocImplementation(InSoftObjectPtr);

            InSoftObjectPtr.GarbageCollectionHandle = Handle;

            __TSoftObjectPtr_RegisterImplementation(Handle, InObject, HandleData.AllocImplementation(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __TSoftObjectPtr_IdenticalImplementation;

        public static unsafe bool TSoftObjectPtr_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TSoftObjectPtr_IdenticalImplementation == null)
            {
                __TSoftObjectPtr_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftObjectPtrImplementation::TSoftObjectPtr_IdenticalImplementation");
            }

            return __TSoftObjectPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TSoftObjectPtr_UnRegisterImplementation;

        public static unsafe void TSoftObjectPtr_UnRegisterImplementation(nint InSoftObjectPtr)
        {
            if (__TSoftObjectPtr_UnRegisterImplementation == null)
            {
                __TSoftObjectPtr_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftObjectPtrImplementation::TSoftObjectPtr_UnRegisterImplementation");
            }

            __TSoftObjectPtr_UnRegisterImplementation(InSoftObjectPtr);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TSoftObjectPtr_GetImplementation;

        public static unsafe T TSoftObjectPtr_GetImplementation<T>(nint InSoftObjectPtr)
        {
            if (__TSoftObjectPtr_GetImplementation == null)
            {
                __TSoftObjectPtr_GetImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftObjectPtrImplementation::TSoftObjectPtr_GetImplementation");
            }

            var Handle = __TSoftObjectPtr_GetImplementation(InSoftObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TSoftObjectPtr_LoadSynchronousImplementation;

        public static unsafe T TSoftObjectPtr_LoadSynchronousImplementation<T>(nint InSoftObjectPtr)
        {
            if (__TSoftObjectPtr_LoadSynchronousImplementation == null)
            {
                __TSoftObjectPtr_LoadSynchronousImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSoftObjectPtrImplementation::TSoftObjectPtr_LoadSynchronousImplementation");
            }

            var Handle = __TSoftObjectPtr_LoadSynchronousImplementation(InSoftObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
#endif
    }
}