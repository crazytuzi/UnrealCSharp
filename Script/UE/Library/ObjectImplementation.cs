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
        public static extern UClass Object_StaticClassImplementation(String InClassName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass Object_GetClassImplementation(IntPtr InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FString Object_GetNameImplementation(IntPtr InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UWorld Object_GetWorldImplementation(IntPtr InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Object_IsValidImplementation(IntPtr InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Object_IsAImplementation(IntPtr InObject, IntPtr SomeBase);
    }
}