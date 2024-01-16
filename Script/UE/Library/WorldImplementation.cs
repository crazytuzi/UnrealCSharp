using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class WorldImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void World_SpawnActorImplementation<T>(IntPtr InWorld, IntPtr InClass,
            FTransform InTransform, IntPtr InOwner, IntPtr InInstigator,
            ESpawnActorCollisionHandlingMethod InCollisionHandlingOverride, out T OutValue) where T : UObject;
    }
}