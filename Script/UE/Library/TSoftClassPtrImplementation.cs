using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TSoftClassPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            nint InClass) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSoftClassPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSoftClassPtr_UnRegisterImplementation(nint InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass TSoftClassPtr_GetImplementation(nint InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass TSoftClassPtr_LoadSynchronousImplementation(nint InSoftClassPtr);
    }
}