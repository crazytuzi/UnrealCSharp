#if UE_5_6_OR_LATER
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class FUtf8StringImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, void> __FUtf8String_RegisterImplementation;

        public static unsafe void FUtf8String_RegisterImplementation(FUtf8String InString, string InValue)
        {
            if (__FUtf8String_RegisterImplementation == null)
            {
                __FUtf8String_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FUtf8StringImplementation::FUtf8String_RegisterImplementation");
            }

            var UTF8 = InValue != null ? System.Text.Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FUtf8String_RegisterImplementation(HandleData.Alloc(InString), Ptr);
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __FUtf8String_IdenticalImplementation;

        public static unsafe bool FUtf8String_IdenticalImplementation(nint InA, nint InB)
        {
            if (__FUtf8String_IdenticalImplementation == null)
            {
                __FUtf8String_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.FUtf8StringImplementation::FUtf8String_IdenticalImplementation");
            }

            return __FUtf8String_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __FUtf8String_UnRegisterImplementation;

        public static unsafe void FUtf8String_UnRegisterImplementation(nint InString)
        {
            if (__FUtf8String_UnRegisterImplementation == null)
            {
                __FUtf8String_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FUtf8StringImplementation::FUtf8String_UnRegisterImplementation");
            }

            __FUtf8String_UnRegisterImplementation(InString);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __FUtf8String_ToStringImplementation;

        public static unsafe string FUtf8String_ToStringImplementation(nint InString)
        {
            if (__FUtf8String_ToStringImplementation == null)
            {
                __FUtf8String_ToStringImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.FUtf8StringImplementation::FUtf8String_ToStringImplementation");
            }

            var Handle = __FUtf8String_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}
#endif