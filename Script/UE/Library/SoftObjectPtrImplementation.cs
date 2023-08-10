using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class SoftObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPtr_RegisterImplementation<T>(TSoftObjectPtr<T> InSoftObjectPtr, T InObject)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPtr_UnRegisterImplementation(IntPtr InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPtr_GetImplementation<T>(IntPtr InSoftObjectPtr, out T OutValue)
            where T : UObject;
    }
}