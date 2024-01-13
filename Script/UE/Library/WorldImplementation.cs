using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class WorldImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T World_SpawnActorImplementation<T>(nint InWorld, nint InClass,
            nint InTransform, nint InSpawnParameters);
    }
}