using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FAnsiStringImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FAnsiString_RegisterImplementation(FAnsiString InString, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FAnsiString_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FAnsiString_UnRegisterImplementation(nint InString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FAnsiString_ToStringImplementation(nint InString);
    }
}