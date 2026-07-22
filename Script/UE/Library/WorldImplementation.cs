using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class UWorldImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, nint>
            __UWorld_SpawnActorImplementation;

        public static unsafe T UWorld_SpawnActorImplementation<T>(nint InWorld, nint InClass,
            nint InTransform, nint InSpawnParameters) where T : UObject
        {
            if (__UWorld_SpawnActorImplementation == null)
            {
                __UWorld_SpawnActorImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UWorldImplementation::UWorld_SpawnActorImplementation");
            }

            var Handle = __UWorld_SpawnActorImplementation(InWorld, InClass, InTransform, InSpawnParameters);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : null;
        }
    }
}