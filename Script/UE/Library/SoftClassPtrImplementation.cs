using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SoftClassPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            nint InClass) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool SoftClassPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_UnRegisterImplementation(nint InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass SoftClassPtr_GetImplementation(nint InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass SoftClassPtr_LoadSynchronousImplementation(nint InSoftClassPtr);
    }
}