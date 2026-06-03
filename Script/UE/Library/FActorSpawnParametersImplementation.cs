#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static partial class FActorSpawnParametersImplementation
    {
#if WITH_MONO
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
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, int> __FActorSpawnParameters_GetbNoFailImplementation;

        public static unsafe bool FActorSpawnParameters_GetbNoFailImplementation(nint InObject)
        {
            if (__FActorSpawnParameters_GetbNoFailImplementation == null)
            {
                __FActorSpawnParameters_GetbNoFailImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.FActorSpawnParametersImplementation::FActorSpawnParameters_GetbNoFailImplementation");
            }

            return __FActorSpawnParameters_GetbNoFailImplementation(InObject) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, bool, void>
            __FActorSpawnParameters_SetbNoFailImplementation;

        public static unsafe void FActorSpawnParameters_SetbNoFailImplementation(nint InObject, bool InValue)
        {
            if (__FActorSpawnParameters_SetbNoFailImplementation == null)
            {
                __FActorSpawnParameters_SetbNoFailImplementation = (delegate* unmanaged[Cdecl]<nint, bool, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FActorSpawnParametersImplementation::FActorSpawnParameters_SetbNoFailImplementation");
            }

            __FActorSpawnParameters_SetbNoFailImplementation(InObject, InValue);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, int>
            __FActorSpawnParameters_GetbDeferConstructionImplementation;

        public static unsafe bool FActorSpawnParameters_GetbDeferConstructionImplementation(nint InObject)
        {
            if (__FActorSpawnParameters_GetbDeferConstructionImplementation == null)
            {
                __FActorSpawnParameters_GetbDeferConstructionImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.FActorSpawnParametersImplementation::FActorSpawnParameters_GetbDeferConstructionImplementation");
            }

            return __FActorSpawnParameters_GetbDeferConstructionImplementation(InObject) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, bool, void>
            __FActorSpawnParameters_SetbDeferConstructionImplementation;

        public static unsafe void FActorSpawnParameters_SetbDeferConstructionImplementation(nint InObject, bool InValue)
        {
            if (__FActorSpawnParameters_SetbDeferConstructionImplementation == null)
            {
                __FActorSpawnParameters_SetbDeferConstructionImplementation =
                    (delegate* unmanaged[Cdecl]<nint, bool, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FActorSpawnParametersImplementation::FActorSpawnParameters_SetbDeferConstructionImplementation");
            }

            __FActorSpawnParameters_SetbDeferConstructionImplementation(InObject, InValue);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, int>
            __FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation;

        public static unsafe bool FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation(nint InObject)
        {
            if (__FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation == null)
            {
                __FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation =
                    (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.FActorSpawnParametersImplementation::FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation");
            }

            return __FActorSpawnParameters_GetbAllowDuringConstructionScriptImplementation(InObject) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, bool, void>
            __FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation;

        public static unsafe void FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation(nint InObject,
            bool InValue)
        {
            if (__FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation == null)
            {
                __FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation =
                    (delegate* unmanaged[Cdecl]<nint, bool, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FActorSpawnParametersImplementation::FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation");
            }

            __FActorSpawnParameters_SetbAllowDuringConstructionScriptImplementation(InObject, InValue);
        }
#endif
    }
}