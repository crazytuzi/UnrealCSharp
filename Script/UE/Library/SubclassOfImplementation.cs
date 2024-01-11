using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SubclassOfImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf, IntPtr InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SubclassOf_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_UnRegisterImplementation(IntPtr InSubclassOf);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass SubclassOf_GetImplementation(IntPtr InSubclassOf);
    }
}