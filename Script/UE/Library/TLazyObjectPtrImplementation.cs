using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class TLazyObjectPtrImplementation
    {
        private static unsafe partial void __TLazyObjectPtr_RegisterImplementation(nint InLazyObjectPtr, nint InObject, nint InType);

        public static unsafe void TLazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr,
            nint InObject, Type InType) where T : UObject
        {
            __TLazyObjectPtr_RegisterImplementation(HandleData.Alloc(InLazyObjectPtr), InObject,
                HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TLazyObjectPtr_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool TLazyObjectPtr_IdenticalImplementation(nint InA, nint InB)
        {
            return __TLazyObjectPtr_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TLazyObjectPtr_UnRegisterImplementation(nint InLazyObjectPtr);

        public static unsafe void TLazyObjectPtr_UnRegisterImplementation(nint InLazyObjectPtr)
        {
            __TLazyObjectPtr_UnRegisterImplementation(InLazyObjectPtr);
        }

        private static unsafe partial nint __TLazyObjectPtr_GetImplementation(nint InLazyObjectPtr);

        public static unsafe T TLazyObjectPtr_GetImplementation<T>(nint InLazyObjectPtr)
        {
            var Handle = __TLazyObjectPtr_GetImplementation(InLazyObjectPtr);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}