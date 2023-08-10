using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SoftClassPathImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPath_GetOrCreateIDForClassImplementation(UClass InClass,
            out FSoftClassPath OutValue);
    }
}