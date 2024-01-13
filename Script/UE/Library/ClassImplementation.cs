using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static partial class ClassImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UObject Class_GetDefaultObjectImplementation(nint InClass, bool bCreateIfNeeded);
    }
}