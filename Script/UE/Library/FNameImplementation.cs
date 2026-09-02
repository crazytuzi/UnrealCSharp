using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class FNameImplementation
    {
        private static unsafe partial void __FName_RegisterImplementation(nint InName, byte* InValue);

        public static unsafe void FName_RegisterImplementation(FName InName, string InValue)
        {
            var UTF8 = InValue != null ? Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FName_RegisterImplementation(HandleData.Alloc(InName), Ptr);
            }
        }

        private static unsafe partial byte __FName_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool FName_IdenticalImplementation(nint InA, nint InB)
        {
            return __FName_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __FName_UnRegisterImplementation(nint InName);

        public static unsafe void FName_UnRegisterImplementation(nint InName)
        {
            __FName_UnRegisterImplementation(InName);
        }

        private static unsafe partial nint __FName_ToStringImplementation(nint InName);

        public static unsafe string FName_ToStringImplementation(nint InName)
        {
            var Handle = __FName_ToStringImplementation(InName);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __FName_NAME_NoneImplementation();

        public static unsafe FName FName_NAME_NoneImplementation()
        {
            var Handle = __FName_NAME_NoneImplementation();

            return Handle != 0 ? (FName)HandleData.GetObject(Handle) : null;
        }
    }
}