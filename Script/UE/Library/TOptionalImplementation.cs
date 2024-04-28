#if UE_5_3_OR_LATER
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TOptionalImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_Register1Implementation<T>(TOptional<T> InOptional);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TOptional_Register2Implementation<T>(TOptional<T> InOptional, object InValue);

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
        public static extern void TOptional_SetImplementation(nint InOptional, object InValue);
    }
}
#endif