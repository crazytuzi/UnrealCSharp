using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FNameImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FName_RegisterImplementation(FName InName, string InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FName_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FName_UnRegisterImplementation(nint InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FName_ToStringImplementation(nint InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FName FName_NAME_NoneImplementation();
    }
}