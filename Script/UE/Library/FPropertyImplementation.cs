using Interop;

namespace Script.Library
{
    public static unsafe partial class FPropertyImplementation
    {
        private static unsafe partial void __FProperty_GetObjectPropertyImplementation(nint InDelegate, uint InPropertyHash, byte* ReturnBuffer);

        public static void FProperty_GetObjectPropertyImplementation(nint InDelegate, uint InPropertyHash,
            byte* ReturnBuffer)
        {
            __FProperty_GetObjectPropertyImplementation(InDelegate, InPropertyHash, ReturnBuffer);
        }

        private static unsafe partial void __FProperty_SetObjectPropertyImplementation(nint InDelegate, uint InPropertyHash, byte* InBuffer);

        public static void FProperty_SetObjectPropertyImplementation(nint InDelegate, uint InPropertyHash,
            byte* InBuffer)
        {
            __FProperty_SetObjectPropertyImplementation(InDelegate, InPropertyHash, InBuffer);
        }

        private static unsafe partial void __FProperty_GetStructPropertyImplementation(nint InDelegate, uint InPropertyHash, byte* ReturnBuffer);

        public static void FProperty_GetStructPropertyImplementation(nint InDelegate, uint InPropertyHash,
            byte* ReturnBuffer)
        {
            __FProperty_GetStructPropertyImplementation(InDelegate, InPropertyHash, ReturnBuffer);
        }

        private static unsafe partial void __FProperty_SetStructPropertyImplementation(nint InDelegate, uint InPropertyHash, byte* InBuffer);

        public static void FProperty_SetStructPropertyImplementation(nint InDelegate, uint InPropertyHash,
            byte* InBuffer)
        {
            __FProperty_SetStructPropertyImplementation(InDelegate, InPropertyHash, InBuffer);
        }
    }
}