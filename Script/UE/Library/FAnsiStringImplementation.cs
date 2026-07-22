#if UE_5_6_OR_LATER
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class FAnsiStringImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, void> __FAnsiString_RegisterImplementation;

        public static unsafe void FAnsiString_RegisterImplementation(FAnsiString InString, string InValue)
        {
            if (__FAnsiString_RegisterImplementation == null)
            {
                __FAnsiString_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_RegisterImplementation");
            }

            var UTF8 = InValue != null ? System.Text.Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FAnsiString_RegisterImplementation(HandleData.Alloc(InString), Ptr);
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __FAnsiString_IdenticalImplementation;

        public static unsafe bool FAnsiString_IdenticalImplementation(nint InA, nint InB)
        {
            if (__FAnsiString_IdenticalImplementation == null)
            {
                __FAnsiString_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_IdenticalImplementation");
            }

            return __FAnsiString_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __FAnsiString_UnRegisterImplementation;

        public static unsafe void FAnsiString_UnRegisterImplementation(nint InString)
        {
            if (__FAnsiString_UnRegisterImplementation == null)
            {
                __FAnsiString_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_UnRegisterImplementation");
            }

            __FAnsiString_UnRegisterImplementation(InString);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __FAnsiString_ToStringImplementation;

        public static unsafe string FAnsiString_ToStringImplementation(nint InString)
        {
            if (__FAnsiString_ToStringImplementation == null)
            {
                __FAnsiString_ToStringImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.FAnsiStringImplementation::FAnsiString_ToStringImplementation");
            }

            var Handle = __FAnsiString_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}
#endif