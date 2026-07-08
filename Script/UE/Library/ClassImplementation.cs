using Interop;

namespace Script.Library
{
    public static partial class UClassImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, void> __UClass_RemoveFunctionImplementation;

        public static unsafe void UClass_RemoveFunctionImplementation(nint InClass, nint InName)
        {
            if (__UClass_RemoveFunctionImplementation == null)
            {
                __UClass_RemoveFunctionImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UClassImplementation::UClass_RemoveFunctionImplementation");
            }

            __UClass_RemoveFunctionImplementation(InClass, InName);
        }
    }
}