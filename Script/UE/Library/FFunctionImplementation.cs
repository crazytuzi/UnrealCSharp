using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static unsafe class FFunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall0Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall1Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall1Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall2Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall4Implementation(nint InMonoObject, uint InFunctionHash,
            byte* OutBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall15Implementation(nint InMonoObject, uint InFunctionHash,
            byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall15Implementation(nint InMonoObject, uint InFunctionHash,
            byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall6Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall7Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall7Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall8Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall9Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall9Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall10Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall14Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_PrimitiveCall15Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_CompoundCall15Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall16Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall18Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall24Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FFunction_GenericCall26Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer);
    }
}