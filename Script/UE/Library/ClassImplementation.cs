using Interop;

namespace Script.Library
{
    public static partial class UClassImplementation
    {
        private static unsafe partial void __UClass_RemoveFunctionImplementation(nint InClass, nint InName);

        public static unsafe void UClass_RemoveFunctionImplementation(nint InClass, nint InName)
        {
            __UClass_RemoveFunctionImplementation(InClass, InName);
        }
    }
}