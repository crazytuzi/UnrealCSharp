using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static partial class UClassImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UObject UClass_GetDefaultObjectImplementation(nint InClass, bool bCreateIfNeeded);
    }
}