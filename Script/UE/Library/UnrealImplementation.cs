using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class UnrealImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_NewObjectImplementation<T>(System.IntPtr Outer, System.IntPtr Class,
            FName Name,
            out T OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_DuplicateObjectImplementation<T>(System.IntPtr SourceObject,
            System.IntPtr Outer,
            FName Name, out T OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_LoadObjectImplementation<T>(System.IntPtr Outer, string Name, out T OutValue)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_LoadClassImplementation(System.IntPtr Outer, string Name, out UClass OutValue);
    }
}