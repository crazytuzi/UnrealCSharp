using System.Text;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class FStringImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, void> __FString_RegisterImplementation;

        public static unsafe void FString_RegisterImplementation(FString InString, string InValue)
        {
            if (__FString_RegisterImplementation == null)
            {
                __FString_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FStringImplementation::FString_RegisterImplementation");
            }

            var UTF8 = InValue != null ? Encoding.UTF8.GetBytes(InValue + '\0') : [0];

            fixed (byte* Ptr = UTF8)
            {
                __FString_RegisterImplementation(HandleData.Alloc(InString), Ptr);
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __FString_IdenticalImplementation;

        public static unsafe bool FString_IdenticalImplementation(nint InA, nint InB)
        {
            if (__FString_IdenticalImplementation == null)
            {
                __FString_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.FStringImplementation::FString_IdenticalImplementation");
            }

            return __FString_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __FString_UnRegisterImplementation;

        public static unsafe void FString_UnRegisterImplementation(nint InString)
        {
            if (__FString_UnRegisterImplementation == null)
            {
                __FString_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FStringImplementation::FString_UnRegisterImplementation");
            }

            __FString_UnRegisterImplementation(InString);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __FString_ToStringImplementation;

        public static unsafe string FString_ToStringImplementation(nint InString)
        {
            if (__FString_ToStringImplementation == null)
            {
                __FString_ToStringImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.FStringImplementation::FString_ToStringImplementation");
            }

            var Handle = __FString_ToStringImplementation(InString);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}