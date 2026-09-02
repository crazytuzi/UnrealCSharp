using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class UWorldImplementation
    {
        private static unsafe partial nint __UWorld_SpawnActorImplementation(nint InWorld, nint InClass, nint InTransform, nint InSpawnParameters);

        public static unsafe T UWorld_SpawnActorImplementation<T>(nint InWorld, nint InClass,
            nint InTransform, nint InSpawnParameters) where T : UObject
        {
            var Handle = __UWorld_SpawnActorImplementation(InWorld, InClass, InTransform, InSpawnParameters);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : null;
        }
    }
}