#if UE_5_6_OR_LATER
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class FAnsiStringImplementation
    {
        private static unsafe partial void __FAnsiString_RegisterImplementation(nint InString, byte* InValue);

        public static unsafe void FAnsiString_RegisterImplementation(FAnsiString InString, string InValue)
        {
            var UTF8 = InValue != null ? System.Text.Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FAnsiString_RegisterImplementation(HandleData.Alloc(InString), Ptr);
            }
        }

        private static unsafe partial byte __FAnsiString_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool FAnsiString_IdenticalImplementation(nint InA, nint InB)
        {
            return __FAnsiString_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __FAnsiString_UnRegisterImplementation(nint InString);

        public static unsafe void FAnsiString_UnRegisterImplementation(nint InString)
        {
            __FAnsiString_UnRegisterImplementation(InString);
        }

        private static unsafe partial nint __FAnsiString_ToStringImplementation(nint InString);

        public static unsafe string FAnsiString_ToStringImplementation(nint InString)
        {
            var Handle = __FAnsiString_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}
#endif