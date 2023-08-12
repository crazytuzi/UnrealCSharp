using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static partial class ClassImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Class_GetDefaultObjectImplementation(IntPtr InClass, Boolean bCreateIfNeeded,
            out UObject OutValue);
    }
}