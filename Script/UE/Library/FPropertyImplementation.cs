using Interop;

namespace Script.Library
{
    public static unsafe partial class FPropertyImplementation
    {
        private static unsafe partial void __FProperty_GetObjectPropertyImplementation(nint InObject, uint InPropertyHash, byte* ReturnBuffer);

        public static void FProperty_GetObjectPropertyImplementation(nint InObject, uint InPropertyHash,
            byte* ReturnBuffer)
        {
            __FProperty_GetObjectPropertyImplementation(InObject, InPropertyHash, ReturnBuffer);
        }

        private static unsafe partial void __FProperty_SetObjectPropertyImplementation(nint InObject, uint InPropertyHash, byte* InBuffer);

        public static void FProperty_SetObjectPropertyImplementation(nint InObject, uint InPropertyHash,
            byte* InBuffer)
        {
            __FProperty_SetObjectPropertyImplementation(InObject, InPropertyHash, InBuffer);
        }

        private static unsafe partial void __FProperty_GetStructPropertyImplementation(nint InObject, uint InPropertyHash, byte* ReturnBuffer);

        public static void FProperty_GetStructPropertyImplementation(nint InObject, uint InPropertyHash,
            byte* ReturnBuffer)
        {
            __FProperty_GetStructPropertyImplementation(InObject, InPropertyHash, ReturnBuffer);
        }

        private static unsafe partial void __FProperty_SetStructPropertyImplementation(nint InObject, uint InPropertyHash, byte* InBuffer);

        public static void FProperty_SetStructPropertyImplementation(nint InObject, uint InPropertyHash,
            byte* InBuffer)
        {
            __FProperty_SetStructPropertyImplementation(InObject, InPropertyHash, InBuffer);
        }
    }
}