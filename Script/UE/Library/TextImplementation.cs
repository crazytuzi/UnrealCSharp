using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class TextImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Text_RegisterImplementation(FText InText, String InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Text_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Text_UnRegisterImplementation(IntPtr InText);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern String Text_ToStringImplementation(IntPtr InText);
    }
}