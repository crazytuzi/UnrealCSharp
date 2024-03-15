using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class UWorldImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T UWorld_SpawnActorImplementation<T>(nint InWorld, nint InClass,
            nint InTransform, nint InSpawnParameters);
    }
}