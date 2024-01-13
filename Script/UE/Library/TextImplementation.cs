using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class TextImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Text_RegisterImplementation(FText InText, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Text_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Text_UnRegisterImplementation(nint InText);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string Text_ToStringImplementation(nint InText);
    }
}