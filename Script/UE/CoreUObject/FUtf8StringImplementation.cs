using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FUtf8StringImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FUtf8String_RegisterImplementation(FUtf8String InString, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FUtf8String_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FUtf8String_UnRegisterImplementation(nint InString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FUtf8String_ToStringImplementation(nint InString);
    }
}