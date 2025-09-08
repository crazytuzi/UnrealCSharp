using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static partial class UObjectImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass UObject_StaticClassImplementation(string InClassName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UClass UObject_GetClassImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FString UObject_GetNameImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_IsValidImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_IsAImplementation(nint InObject, nint SomeBase);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UObject_AddToRootImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UObject_RemoveFromRootImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_IsRootedImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_AddReferenceImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UObject_RemoveReferenceImplementation(nint InObject);
    }
}