using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class UStructImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<byte*, nint> __UStruct_StaticStructImplementation;

        public static unsafe UScriptStruct UStruct_StaticStructImplementation(string InStructName)
        {
            if (__UStruct_StaticStructImplementation == null)
            {
                __UStruct_StaticStructImplementation = (delegate* unmanaged[Cdecl]<byte*, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UStructImplementation::UStruct_StaticStructImplementation");
            }

            nint Handle;

            var UTF8 = InStructName != null ? Encoding.UTF8.GetBytes(InStructName + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                Handle = __UStruct_StaticStructImplementation(Ptr);
            }

            return Handle != 0 ? (UScriptStruct)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, void> __UStruct_RegisterImplementation;

        public static unsafe void UStruct_RegisterImplementation(object InMonoObject, string InStructName)
        {
            if (__UStruct_RegisterImplementation == null)
            {
                __UStruct_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UStructImplementation::UStruct_RegisterImplementation");
            }

            var UTF8 = InStructName != null ? Encoding.UTF8.GetBytes(InStructName + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __UStruct_RegisterImplementation(HandleData.Alloc(InMonoObject), Ptr);
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, byte> __UStruct_IdenticalImplementation;

        public static unsafe bool UStruct_IdenticalImplementation(nint InScriptStruct, nint InA, nint InB)
        {
            if (__UStruct_IdenticalImplementation == null)
            {
                __UStruct_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.UStructImplementation::UStruct_IdenticalImplementation");
            }

            return __UStruct_IdenticalImplementation(InScriptStruct, InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __UStruct_UnRegisterImplementation;

        public static unsafe void UStruct_UnRegisterImplementation(nint InMonoObject)
        {
            if (__UStruct_UnRegisterImplementation == null)
            {
                __UStruct_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UStructImplementation::UStruct_UnRegisterImplementation");
            }

            __UStruct_UnRegisterImplementation(InMonoObject);
        }
    }
}