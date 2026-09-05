using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class TSoftObjectPtrImplementation
    {
        private static unsafe partial void __TSoftObjectPtr_RegisterImplementation(nint InSoftObjectPtr, nint InObject, nint InType);

        public static unsafe void TSoftObjectPtr_RegisterImplementation<T>(TSoftObjectPtr<T> InSoftObjectPtr,
            nint InObject, Type InType) where T : UObject
        {
            __TSoftObjectPtr_RegisterImplementation(HandleData.Alloc(InSoftObjectPtr), InObject,
                HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TSoftObjectPtr_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool TSoftObjectPtr_IdenticalImplementation(nint InA, nint InB)
        {
            return __TSoftObjectPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TSoftObjectPtr_UnRegisterImplementation(nint InSoftObjectPtr);

        public static unsafe void TSoftObjectPtr_UnRegisterImplementation(nint InSoftObjectPtr)
        {
            __TSoftObjectPtr_UnRegisterImplementation(InSoftObjectPtr);
        }

        private static unsafe partial nint __TSoftObjectPtr_GetImplementation(nint InSoftObjectPtr);

        public static unsafe T TSoftObjectPtr_GetImplementation<T>(nint InSoftObjectPtr)
        {
            var Handle = __TSoftObjectPtr_GetImplementation(InSoftObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }

        private static unsafe partial nint __TSoftObjectPtr_LoadSynchronousImplementation(nint InSoftObjectPtr);

        public static unsafe T TSoftObjectPtr_LoadSynchronousImplementation<T>(nint InSoftObjectPtr)
        {
            var Handle = __TSoftObjectPtr_LoadSynchronousImplementation(InSoftObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}