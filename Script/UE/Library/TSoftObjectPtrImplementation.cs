using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TSoftObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftObjectPtr_RegisterImplementation<T>(TSoftObjectPtr<T> InSoftObjectPtr,
            nint InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSoftObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftObjectPtr_UnRegisterImplementation(nint InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TSoftObjectPtr_GetImplementation<T>(nint InSoftObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TSoftObjectPtr_LoadSynchronousImplementation<T>(nint InSoftObjectPtr);
    }
}