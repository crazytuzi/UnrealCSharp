using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FStringImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FString_RegisterImplementation(FString InString, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FString_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FString_UnRegisterImplementation(nint InString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FString_ToStringImplementation(nint InString);
    }
}