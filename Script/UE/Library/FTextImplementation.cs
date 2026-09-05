using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static partial class FTextImplementation
    {
        private static unsafe partial void __FText_RegisterImplementation(nint InText, byte* InBuffer, byte* InTextNamespace, byte* InPackageNamespace, byte bRequiresQuotes);

        public static unsafe void FText_RegisterImplementation(FText InText, string InBuffer, string InTextNamespace,
            string InPackageNamespace, bool bRequiresQuotes)
        {
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

        private static unsafe partial byte __FText_IdenticalImplementation(nint InA, nint InB);

        public static unsafe bool FText_IdenticalImplementation(nint InA, nint InB)
        {
            return __FText_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __FText_UnRegisterImplementation(nint InText);

        public static unsafe void FText_UnRegisterImplementation(nint InText)
        {
            __FText_UnRegisterImplementation(InText);
        }

        private static unsafe partial nint __FText_ToStringImplementation(nint InText);

        public static unsafe string FText_ToStringImplementation(nint InText)
        {
            var Handle = __FText_ToStringImplementation(InText);

            return Handle != 0 ? (string)HandleData.GetObject(Handle) : null;
        }
    }
}