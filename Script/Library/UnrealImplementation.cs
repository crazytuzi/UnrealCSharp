using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class UnrealImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_NewObjectImplementation<T>(UObject Outer, UClass Class, FName Name,
            out T OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unreal_NewObjectWithClassNameImplementation<T>(UObject Outer, string Class,
            FName Name, out T OutValue) where T : UObject;
    }
}