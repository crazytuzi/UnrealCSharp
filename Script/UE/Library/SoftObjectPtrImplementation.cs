using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SoftObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPtr_RegisterImplementation<T>(TSoftObjectPtr<T> InSoftObjectPtr,
            nint InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool SoftObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPtr_UnRegisterImplementation(nint InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T SoftObjectPtr_GetImplementation<T>(nint InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T SoftObjectPtr_LoadSynchronousImplementation<T>(nint InSoftObjectPtr);
    }
}