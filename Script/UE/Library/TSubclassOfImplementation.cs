using Script.CoreUObject;
using System;
using Interop;

namespace Script.Library
{
    public static partial class TSubclassOfImplementation
    {
        private static unsafe partial void __TSubclassOf_RegisterImplementation(nint InSubclassOf, nint InClass, nint InType);

        public static unsafe void TSubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf,
            nint InClass, Type InType) where T : UObject
        {
            __TSubclassOf_RegisterImplementation(HandleData.Alloc(InSubclassOf), InClass,
                HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TSubclassOf_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool TSubclassOf_IdenticalImplementation(nint InA, nint InB)
        {
            return __TSubclassOf_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TSubclassOf_UnRegisterImplementation(nint InSubclassOf);

        public static unsafe void TSubclassOf_UnRegisterImplementation(nint InSubclassOf)
        {
            __TSubclassOf_UnRegisterImplementation(InSubclassOf);
        }

        private static unsafe partial nint __TSubclassOf_GetImplementation(nint InSubclassOf);

        public static unsafe UClass TSubclassOf_GetImplementation(nint InSubclassOf)
        {
            var Handle = __TSubclassOf_GetImplementation(InSubclassOf);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }
    }
}