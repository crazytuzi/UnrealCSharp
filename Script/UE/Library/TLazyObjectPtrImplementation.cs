using System;
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class TLazyObjectPtrImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TLazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr,
            nint InObject, Type InType) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TLazyObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TLazyObjectPtr_UnRegisterImplementation(nint InLazyObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TLazyObjectPtr_GetImplementation<T>(nint InLazyObjectPtr);
#else
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

            var Handle = HandleData.AllocImplementation(InLazyObjectPtr);

            InLazyObjectPtr.GarbageCollectionHandle = Handle;

            __TLazyObjectPtr_RegisterImplementation(Handle, InObject, HandleData.AllocImplementation(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __TLazyObjectPtr_IdenticalImplementation;

        public static unsafe bool TLazyObjectPtr_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TLazyObjectPtr_IdenticalImplementation == null)
            {
                __TLazyObjectPtr_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
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
#endif
    }
}