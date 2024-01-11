using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class WorldImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object World_SpawnActorImplementation(IntPtr InWorld, IntPtr InClass,
            IntPtr InTransform, IntPtr InSpawnParameters);
    }
}