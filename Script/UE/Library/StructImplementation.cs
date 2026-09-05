using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class UStructImplementation
    {
        private static unsafe partial nint __UStruct_StaticStructImplementation(byte* InStructName);

        public static unsafe UScriptStruct UStruct_StaticStructImplementation(string InStructName)
        {
            nint Handle;

            var UTF8 = InStructName != null ? Encoding.UTF8.GetBytes(InStructName + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                Handle = __UStruct_StaticStructImplementation(Ptr);
            }

            return Handle != 0 ? (UScriptStruct)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial void __UStruct_RegisterImplementation(nint InDelegate, byte* InStructName);

        public static unsafe void UStruct_RegisterImplementation(object InDelegate, string InStructName)
        {
            var UTF8 = InStructName != null ? Encoding.UTF8.GetBytes(InStructName + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __UStruct_RegisterImplementation(HandleData.Alloc(InDelegate), Ptr);
            }
        }

        private static unsafe partial byte __UStruct_IdenticalImplementation(nint InScriptStruct, nint InA, nint InB);

        public static unsafe bool UStruct_IdenticalImplementation(nint InScriptStruct, nint InA, nint InB)
        {
            return __UStruct_IdenticalImplementation(InScriptStruct, InA, InB) != 0;
        }

        private static unsafe partial void __UStruct_UnRegisterImplementation(nint InDelegate);

        public static unsafe void UStruct_UnRegisterImplementation(nint InDelegate)
        {
            __UStruct_UnRegisterImplementation(InDelegate);
        }
    }
}