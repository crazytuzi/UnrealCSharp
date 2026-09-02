#if UE_5_6_OR_LATER
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class FUtf8StringImplementation
    {
        private static unsafe partial void __FUtf8String_RegisterImplementation(nint InString, byte* InValue);

        public static unsafe void FUtf8String_RegisterImplementation(FUtf8String InString, string InValue)
        {
            var UTF8 = InValue != null ? System.Text.Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FUtf8String_RegisterImplementation(HandleData.Alloc(InString), Ptr);
            }
        }

        private static unsafe partial byte __FUtf8String_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool FUtf8String_IdenticalImplementation(nint InA, nint InB)
        {
            return __FUtf8String_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __FUtf8String_UnRegisterImplementation(nint InString);

        public static unsafe void FUtf8String_UnRegisterImplementation(nint InString)
        {
            __FUtf8String_UnRegisterImplementation(InString);
        }

        private static unsafe partial nint __FUtf8String_ToStringImplementation(nint InString);

        public static unsafe string FUtf8String_ToStringImplementation(nint InString)
        {
            var Handle = __FUtf8String_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}
#endif