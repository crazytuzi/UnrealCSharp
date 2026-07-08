using Interop;

namespace Script.Library
{
    public static unsafe class FPropertyImplementation
    {
        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FProperty_GetObjectPropertyImplementation;

        public static void FProperty_GetObjectPropertyImplementation(nint InMonoObject, uint InPropertyHash,
            byte* ReturnBuffer)
        {
            if (__FProperty_GetObjectPropertyImplementation == null)
            {
                __FProperty_GetObjectPropertyImplementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FPropertyImplementation::FProperty_GetObjectPropertyImplementation");
            }

            __FProperty_GetObjectPropertyImplementation(InMonoObject, InPropertyHash, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FProperty_SetObjectPropertyImplementation;

        public static void FProperty_SetObjectPropertyImplementation(nint InMonoObject, uint InPropertyHash,
            byte* InBuffer)
        {
            if (__FProperty_SetObjectPropertyImplementation == null)
            {
                __FProperty_SetObjectPropertyImplementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FPropertyImplementation::FProperty_SetObjectPropertyImplementation");
            }

            __FProperty_SetObjectPropertyImplementation(InMonoObject, InPropertyHash, InBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FProperty_GetStructPropertyImplementation;

        public static void FProperty_GetStructPropertyImplementation(nint InMonoObject, uint InPropertyHash,
            byte* ReturnBuffer)
        {
            if (__FProperty_GetStructPropertyImplementation == null)
            {
                __FProperty_GetStructPropertyImplementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FPropertyImplementation::FProperty_GetStructPropertyImplementation");
            }

            __FProperty_GetStructPropertyImplementation(InMonoObject, InPropertyHash, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FProperty_SetStructPropertyImplementation;

        public static void FProperty_SetStructPropertyImplementation(nint InMonoObject, uint InPropertyHash,
            byte* InBuffer)
        {
            if (__FProperty_SetStructPropertyImplementation == null)
            {
                __FProperty_SetStructPropertyImplementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FPropertyImplementation::FProperty_SetStructPropertyImplementation");
            }

            __FProperty_SetStructPropertyImplementation(InMonoObject, InPropertyHash, InBuffer);
        }
    }
}