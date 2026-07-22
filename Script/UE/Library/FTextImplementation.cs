using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static class FTextImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, byte*, byte*, byte*, byte, void>
            __FText_RegisterImplementation;

        public static unsafe void FText_RegisterImplementation(FText InText, string InBuffer, string InTextNamespace,
            string InPackageNamespace, bool bRequiresQuotes)
        {
            if (__FText_RegisterImplementation == null)
            {
                __FText_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, byte*, byte, void>)
                    MethodBridge.GetMethod("Script.Library.FTextImplementation::FText_RegisterImplementation");
            }

            var Buffer = InBuffer != null ? System.Text.Encoding.UTF8.GetBytes(InBuffer + '\0') : [0];

            var TextNamespace = InTextNamespace != null
                ? System.Text.Encoding.UTF8.GetBytes(InTextNamespace + '\0')
                : [0];

            var PackageNamespace = InPackageNamespace != null
                ? System.Text.Encoding.UTF8.GetBytes(InPackageNamespace + '\0')
                : [0];

            fixed (byte* BufferPtr = Buffer, TextNamespacePtr = TextNamespace, PackageNamespacePtr = PackageNamespace)
            {
                __FText_RegisterImplementation(HandleData.Alloc(InText), BufferPtr, TextNamespacePtr,
                    PackageNamespacePtr, (byte)(bRequiresQuotes ? 1 : 0));
            }
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, byte> __FText_IdenticalImplementation;

        public static unsafe bool FText_IdenticalImplementation(nint InA, nint InB)
        {
            if (__FText_IdenticalImplementation == null)
            {
                __FText_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.FTextImplementation::FText_IdenticalImplementation");
            }

            return __FText_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __FText_UnRegisterImplementation;

        public static unsafe void FText_UnRegisterImplementation(nint InText)
        {
            if (__FText_UnRegisterImplementation == null)
            {
                __FText_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FTextImplementation::FText_UnRegisterImplementation");
            }

            __FText_UnRegisterImplementation(InText);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint> __FText_ToStringImplementation;

        public static unsafe string FText_ToStringImplementation(nint InText)
        {
            if (__FText_ToStringImplementation == null)
            {
                __FText_ToStringImplementation = (delegate* unmanaged[Cdecl]<nint, nint>)
                    MethodBridge.GetMethod("Script.Library.FTextImplementation::FText_ToStringImplementation");
            }

            var Handle = __FText_ToStringImplementation(InText);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}