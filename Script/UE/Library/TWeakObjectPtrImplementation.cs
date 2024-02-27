using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TWeakObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TWeakObjectPtr_RegisterImplementation<T>(TWeakObjectPtr<T> InWeakObjectPtr,
            nint InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TWeakObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TWeakObjectPtr_UnRegisterImplementation(nint InWeakObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TWeakObjectPtr_GetImplementation<T>(nint InWeakObjectPtr);
    }
}