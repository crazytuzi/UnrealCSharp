using Script.CoreUObject;
using System;
using Interop;

namespace Script.Library
{
    public static class TSubclassOfImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void> __TSubclassOf_RegisterImplementation;

        public static unsafe void TSubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf,
            nint InClass, Type InType) where T : UObject
        {
            if (__TSubclassOf_RegisterImplementation == null)
            {
                __TSubclassOf_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSubclassOfImplementation::TSubclassOf_RegisterImplementation");
            }

            __TSubclassOf_RegisterImplementation(HandleData.Alloc(InSubclassOf), InClass,
                HandleData.Alloc(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __TSubclassOf_IdenticalImplementation;

        public static unsafe bool TSubclassOf_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TSubclassOf_IdenticalImplementation == null)
            {
                __TSubclassOf_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSubclassOfImplementation::TSubclassOf_IdenticalImplementation");
            }

            return __TSubclassOf_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TSubclassOf_UnRegisterImplementation;

        public static unsafe void TSubclassOf_UnRegisterImplementation(nint InSubclassOf)
        {
            if (__TSubclassOf_UnRegisterImplementation == null)
            {
                __TSubclassOf_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSubclassOfImplementation::TSubclassOf_UnRegisterImplementation");
            }

            __TSubclassOf_UnRegisterImplementation(InSubclassOf);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TSubclassOf_GetImplementation;

        public static unsafe UClass TSubclassOf_GetImplementation(nint InSubclassOf)
        {
            if (__TSubclassOf_GetImplementation == null)
            {
                __TSubclassOf_GetImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSubclassOfImplementation::TSubclassOf_GetImplementation");
            }

            var Handle = __TSubclassOf_GetImplementation(InSubclassOf);

            return Handle != 0 ? (UClass)HandleData.GetObject(Handle) : null;
        }
    }
}