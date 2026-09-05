using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class TSoftClassPtrImplementation
    {
        private static unsafe partial void __TSoftClassPtr_RegisterImplementation(nint InSoftClassPtr, nint InClass, nint InType);

        public static unsafe void TSoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            nint InClass, Type InType) where T : UObject
        {
            __TSoftClassPtr_RegisterImplementation(HandleData.Alloc(InSoftClassPtr), InClass,
                HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TSoftClassPtr_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool TSoftClassPtr_IdenticalImplementation(nint InA, nint InB)
        {
            return __TSoftClassPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TSoftClassPtr_UnRegisterImplementation(nint InSoftClassPtr);

        public static unsafe void TSoftClassPtr_UnRegisterImplementation(nint InSoftClassPtr)
        {
            __TSoftClassPtr_UnRegisterImplementation(InSoftClassPtr);
        }

        private static unsafe partial nint __TSoftClassPtr_GetImplementation(nint InSoftClassPtr);

        public static unsafe UClass TSoftClassPtr_GetImplementation(nint InSoftClassPtr)
        {
            var Handle = __TSoftClassPtr_GetImplementation(InSoftClassPtr);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __TSoftClassPtr_LoadSynchronousImplementation(nint InSoftClassPtr);

        public static unsafe UClass TSoftClassPtr_LoadSynchronousImplementation(nint InSoftClassPtr)
        {
            var Handle = __TSoftClassPtr_LoadSynchronousImplementation(InSoftClassPtr);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }
    }
}