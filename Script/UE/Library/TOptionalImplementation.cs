#if UE_5_3_OR_LATER
using System;
using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static class TOptionalImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_Register1Implementation<T>(TOptional<T> InOptional, Type InType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_Register2Implementation<T>(TOptional<T> InOptional,
            object InValue, Type InType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TOptional_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_UnRegisterImplementation(nint InOptional);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_ResetImplementation(nint InOptional);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TOptional_IsSetImplementation(nint InOptional);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TOptional_GetImplementation(nint InOptional);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_SetImplementation<T>(nint InOptional, T InValue, Type InType);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, void> __TOptional_Register1Implementation;

        public static unsafe void TOptional_Register1Implementation<T>(TOptional<T> InOptional, Type InType)
        {
            if (__TOptional_Register1Implementation == null)
            {
                __TOptional_Register1Implementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_Register1Implementation");
            }

            var Handle = HandleData.AllocImplementation(InOptional);

            InOptional.GarbageCollectionHandle = Handle;

            __TOptional_Register1Implementation(Handle, HandleData.AllocImplementation(InType));
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

            var Handle = HandleData.AllocImplementation(InOptional);

            InOptional.GarbageCollectionHandle = Handle;

            __TOptional_Register2Implementation(Handle, HandleData.AllocImplementation(InValue),
                HandleData.AllocImplementation(InType));
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, int> __TOptional_IdenticalImplementation;

        public static unsafe bool TOptional_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TOptional_IdenticalImplementation == null)
            {
                __TOptional_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, int>)
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

        private static unsafe delegate* unmanaged[Cdecl]<nint, int> __TOptional_IsSetImplementation;

        public static unsafe bool TOptional_IsSetImplementation(nint InOptional)
        {
            if (__TOptional_IsSetImplementation == null)
            {
                __TOptional_IsSetImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
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

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, void> __TOptional_SetImplementation;

        public static unsafe void TOptional_SetImplementation<T>(nint InOptional, T InValue, Type InType)
        {
            if (__TOptional_SetImplementation == null)
            {
                __TOptional_SetImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TOptionalImplementation::TOptional_SetImplementation");
            }

            __TOptional_SetImplementation(InOptional, HandleData.AllocImplementation(InValue),
                HandleData.AllocImplementation(InType));
        }
#endif
    }
}
#endif