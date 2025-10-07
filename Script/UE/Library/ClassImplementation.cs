using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static partial class UClassImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UClass_RemoveFunctionImplementation(nint InClass, nint InName);
    }
}