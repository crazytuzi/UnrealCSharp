using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static unsafe class FPropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_GetObjectPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_GetStructPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte* InBuffer);
    }
}