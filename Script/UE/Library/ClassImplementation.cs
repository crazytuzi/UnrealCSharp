#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static partial class UClassImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UClass_RemoveFunctionImplementation(nint InClass, nint InName);
#else
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, void> __UClass_RemoveFunctionImplementation;

        public static unsafe void UClass_RemoveFunctionImplementation(nint InClass, nint InName)
        {
            if (__UClass_RemoveFunctionImplementation == null)
            {
                __UClass_RemoveFunctionImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.ClassImplementation::UClass_RemoveFunctionImplementation");
            }

            __UClass_RemoveFunctionImplementation(InClass, InName);
        }
#endif
    }
}