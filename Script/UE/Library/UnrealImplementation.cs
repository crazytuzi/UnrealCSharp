using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class UnrealImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_NewObjectImplementation<T>(IntPtr Outer, IntPtr Class, FName Name,
            out T OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_DuplicateObjectImplementation<T>(IntPtr SourceObject, IntPtr Outer, FName Name,
            out T OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_LoadObjectImplementation<T>(IntPtr Outer, string Name, out T OutValue)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_LoadClassImplementation(IntPtr Outer, string Name, out UClass OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_GWorldImplementation(out UWorld OutValue);
    }
}