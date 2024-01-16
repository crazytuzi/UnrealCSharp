using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class ObjectImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_StaticClassImplementation(string InClassName, out UClass OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_GetClassImplementation(IntPtr InObject, out UClass OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_GetNameImplementation(IntPtr InObject, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_GetWorldImplementation(IntPtr InObject, out UWorld OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Object_IsValidImplementation(IntPtr InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Object_IsAImplementation(IntPtr InObject, IntPtr SomeBase);
    }
}