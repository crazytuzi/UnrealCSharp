using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class ObjectImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass Object_StaticClassImplementation(string InClassName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass Object_GetClassImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FString Object_GetNameImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UWorld Object_GetWorldImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Object_IsValidImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Object_IsAImplementation(nint InObject, nint SomeBase);
    }
}