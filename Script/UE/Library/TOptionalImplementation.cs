#if UE_5_3_OR_LATER
using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class TOptionalImplementation
    {
        private static unsafe partial void __TOptional_Register1Implementation(nint InOptional, nint InType);

        public static unsafe void TOptional_Register1Implementation<T>(TOptional<T> InOptional, Type InType)
        {
            __TOptional_Register1Implementation(HandleData.Alloc(InOptional), HandleData.Alloc(InType));
        }

        private static unsafe partial void __TOptional_Register2Implementation(nint InOptional, nint InValue, nint InType);

        public static unsafe void TOptional_Register2Implementation<T>(TOptional<T> InOptional, T InValue, Type InType)
        {
            __TOptional_Register2Implementation(HandleData.Alloc(InOptional),
                HandleData.Alloc(InValue), HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TOptional_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool TOptional_IdenticalImplementation(nint InA, nint InB)
        {
            return __TOptional_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TOptional_UnRegisterImplementation(nint InOptional);

        public static unsafe void TOptional_UnRegisterImplementation(nint InOptional)
        {
            __TOptional_UnRegisterImplementation(InOptional);
        }

        private static unsafe partial void __TOptional_ResetImplementation(nint InOptional);

        public static unsafe void TOptional_ResetImplementation(nint InOptional)
        {
            __TOptional_ResetImplementation(InOptional);
        }

        private static unsafe partial byte __TOptional_IsSetImplementation(nint InOptional);

        public static unsafe bool TOptional_IsSetImplementation(nint InOptional)
        {
            return __TOptional_IsSetImplementation(InOptional) != 0;
        }

        private static unsafe partial nint __TOptional_GetImplementation(nint InOptional);

        public static unsafe object TOptional_GetImplementation(nint InOptional)
        {
            var Handle = __TOptional_GetImplementation(InOptional);

            return Handle != 0 ? HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial void __TOptional_SetImplementation(nint InOptional, nint InValue);

        public static unsafe void TOptional_SetImplementation<T>(nint InOptional, T InValue)
        {
            __TOptional_SetImplementation(InOptional, HandleData.Alloc(InValue));
        }
    }
}
#endif