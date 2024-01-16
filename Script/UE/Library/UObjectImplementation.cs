using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class UObjectImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass UObject_StaticClassImplementation(string InClassName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass UObject_GetClassImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FString UObject_GetNameImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UWorld UObject_GetWorldImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_IsValidImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_IsAImplementation(nint InObject, nint SomeBase);
    }
}