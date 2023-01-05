using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class ClassImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Class_GetClassDefaultObjectImplementation(UClass InClass, out UObject OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Class_GetDefaultObjectImplementation(UClass InClass, Boolean bCreateIfNeeded,
            out UObject OutValue);
    }
}