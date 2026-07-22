#if UE_5_3_OR_LATER
using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class TOptionalImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, void> __TOptional_Register1Implementation;

        public static unsafe void TOptional_Register1Implementation<T>(TOptional<T> InOptional, Type InType)
        {
            if (__TOptional_Register1Implementation == null)
            {
                __TOptional_Register1Implementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_Register1Implementation");
            }

            __TOptional_Register1Implementation(HandleData.Alloc(InOptional), HandleData.Alloc(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void> __TOptional_Register2Implementation;

        public static unsafe void TOptional_Register2Implementation<T>(TOptional<T> InOptional, T InValue, Type InType)
        {
            if (__TOptional_Register2Implementation == null)
            {
                __TOptional_Register2Implementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_Register2Implementation");
            }

            __TOptional_Register2Implementation(HandleData.Alloc(InOptional),
                HandleData.Alloc(InValue), HandleData.Alloc(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __TOptional_IdenticalImplementation;

        public static unsafe bool TOptional_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TOptional_IdenticalImplementation == null)
            {
                __TOptional_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_IdenticalImplementation");
            }

            return __TOptional_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TOptional_UnRegisterImplementation;

        public static unsafe void TOptional_UnRegisterImplementation(nint InOptional)
        {
            if (__TOptional_UnRegisterImplementation == null)
            {
                __TOptional_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_UnRegisterImplementation");
            }

            __TOptional_UnRegisterImplementation(InOptional);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __TOptional_ResetImplementation;

        public static unsafe void TOptional_ResetImplementation(nint InOptional)
        {
            if (__TOptional_ResetImplementation == null)
            {
                __TOptional_ResetImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_ResetImplementation");
            }

            __TOptional_ResetImplementation(InOptional);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, byte> __TOptional_IsSetImplementation;

        public static unsafe bool TOptional_IsSetImplementation(nint InOptional)
        {
            if (__TOptional_IsSetImplementation == null)
            {
                __TOptional_IsSetImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_IsSetImplementation");
            }

            return __TOptional_IsSetImplementation(InOptional) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __TOptional_GetImplementation;

        public static unsafe object TOptional_GetImplementation(nint InOptional)
        {
            if (__TOptional_GetImplementation == null)
            {
                __TOptional_GetImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_GetImplementation");
            }

            var Handle = __TOptional_GetImplementation(InOptional);

            return Handle != 0 ? HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, void> __TOptional_SetImplementation;

        public static unsafe void TOptional_SetImplementation<T>(nint InOptional, T InValue)
        {
            if (__TOptional_SetImplementation == null)
            {
                __TOptional_SetImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_SetImplementation");
            }

            __TOptional_SetImplementation(InOptional, HandleData.Alloc(InValue));
        }
    }
}
#endif