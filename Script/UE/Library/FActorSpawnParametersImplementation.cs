using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static partial class FActorSpawnParametersImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FActorSpawnParameters_GetbNoFailImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FActorSpawnParameters_SetbNoFailImplementation(nint InObject, bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FActorSpawnParameters_GetbDeferConstructionImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FActorSpawnParameters_SetbDeferConstructionImplementation(nint InObject,
            bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation(nint InObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation(nint InObject,
            bool InValue);
    }
}