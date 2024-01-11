using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class StringImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void String_RegisterImplementation(FString InString, String InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean String_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void String_UnRegisterImplementation(IntPtr InString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern String String_ToStringImplementation(IntPtr InString);
    }
}