using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class NameImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Name_RegisterImplementation(FName InName, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Name_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Name_UnRegisterImplementation(nint InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string Name_ToStringImplementation(nint InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FName Name_NAME_NoneImplementation();
    }
}