using Script.CoreUObject;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static partial class UWorldImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T UWorld_SpawnActorImplementation<T>(nint InWorld, nint InClass,
            nint InTransform, nint InSpawnParameters) where T : UObject;
#else
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
#endif
    }
}