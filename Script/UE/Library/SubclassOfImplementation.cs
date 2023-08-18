using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SubclassOfImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf, UClass InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_UnRegisterImplementation(IntPtr InSubclassOf);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_GetImplementation(IntPtr InSubclassOf, out UClass OutValue);
    }
}