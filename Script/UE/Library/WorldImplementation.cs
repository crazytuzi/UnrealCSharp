using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class WorldImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void World_SpawnActorImplementation<T>(IntPtr InWorld, IntPtr Class, FTransform Transform,
            out T OutValue) where T : UObject;
    }
}