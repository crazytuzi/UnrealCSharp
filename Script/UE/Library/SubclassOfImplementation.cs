using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SubclassOfImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf, nint InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool SubclassOf_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_UnRegisterImplementation(nint InSubclassOf);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass SubclassOf_GetImplementation(nint InSubclassOf);
    }
}