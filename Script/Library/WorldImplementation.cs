using System.Runtime.CompilerServices;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static class WorldImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void World_SpawnActorImplementation<T>(UWorld InWorld, UClass Class, FTransform Transform,
            out T OutValue) where T : UObject;
    }
}