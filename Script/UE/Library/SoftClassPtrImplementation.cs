using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SoftClassPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            UClass InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_UnRegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_GetImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            out UClass OutValue)
            where T : UObject;
    }
}