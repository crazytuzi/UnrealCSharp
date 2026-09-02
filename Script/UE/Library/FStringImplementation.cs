using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class FStringImplementation
    {
        private static unsafe partial void __FString_RegisterImplementation(nint InString, byte* InValue);

        public static unsafe void FString_RegisterImplementation(FString InString, string InValue)
        {
            var UTF8 = InValue != null ? Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FString_RegisterImplementation(HandleData.Alloc(InString), Ptr);
            }
        }

        private static unsafe partial byte __FString_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool FString_IdenticalImplementation(nint InA, nint InB)
        {
            return __FString_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __FString_UnRegisterImplementation(nint InString);

        public static unsafe void FString_UnRegisterImplementation(nint InString)
        {
            __FString_UnRegisterImplementation(InString);
        }

        private static unsafe partial nint __FString_ToStringImplementation(nint InString);

        public static unsafe string FString_ToStringImplementation(nint InString)
        {
            var Handle = __FString_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}