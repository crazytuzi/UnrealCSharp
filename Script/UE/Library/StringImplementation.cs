using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class StringImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void String_RegisterImplementation(FString InString, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool String_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void String_UnRegisterImplementation(nint InString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string String_ToStringImplementation(nint InString);
    }
}