using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TSubclassOfImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf, nint InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSubclassOf_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSubclassOf_UnRegisterImplementation(nint InSubclassOf);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass TSubclassOf_GetImplementation(nint InSubclassOf);
    }
}