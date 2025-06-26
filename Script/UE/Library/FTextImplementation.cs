using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FTextImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FText_RegisterImplementation(FText InText, string InBuffer, string InTextNamespace,
            string InPackageNamespace, bool bRequiresQuotes);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FText_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FText_UnRegisterImplementation(nint InText);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern string FText_ToStringImplementation(nint InText);
    }
}