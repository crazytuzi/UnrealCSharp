#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static unsafe class FFunctionImplementation
    {
#if WITH_MONO
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
#else
        private static delegate* unmanaged[Cdecl]<nint, uint, void> __FFunction_GenericCall0Implementation;

        public static void FFunction_GenericCall0Implementation(nint InMonoObject, uint InFunctionHash)
        {
            if (__FFunction_GenericCall0Implementation == null)
            {
                __FFunction_GenericCall0Implementation = (delegate* unmanaged[Cdecl]<nint, uint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall0Implementation");
            }

            __FFunction_GenericCall0Implementation(InMonoObject, InFunctionHash);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_PrimitiveCall1Implementation;

        public static void FFunction_PrimitiveCall1Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer)
        {
            if (__FFunction_PrimitiveCall1Implementation == null)
            {
                __FFunction_PrimitiveCall1Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_PrimitiveCall1Implementation");
            }

            __FFunction_PrimitiveCall1Implementation(InMonoObject, InFunctionHash, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_CompoundCall1Implementation;

        public static void FFunction_CompoundCall1Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer)
        {
            if (__FFunction_CompoundCall1Implementation == null)
            {
                __FFunction_CompoundCall1Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_CompoundCall1Implementation");
            }

            __FFunction_CompoundCall1Implementation(InMonoObject, InFunctionHash, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_GenericCall2Implementation;

        public static void FFunction_GenericCall2Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer)
        {
            if (__FFunction_GenericCall2Implementation == null)
            {
                __FFunction_GenericCall2Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall2Implementation");
            }

            __FFunction_GenericCall2Implementation(InMonoObject, InFunctionHash, InBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>
            __FFunction_PrimitiveCall3Implementation;

        public static void FFunction_PrimitiveCall3Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_PrimitiveCall3Implementation == null)
            {
                __FFunction_PrimitiveCall3Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_PrimitiveCall3Implementation");
            }

            __FFunction_PrimitiveCall3Implementation(InMonoObject, InFunctionHash, InBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>
            __FFunction_CompoundCall3Implementation;

        public static void FFunction_CompoundCall3Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer,
            byte* ReturnBuffer)
        {
            if (__FFunction_CompoundCall3Implementation == null)
            {
                __FFunction_CompoundCall3Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_CompoundCall3Implementation");
            }

            __FFunction_CompoundCall3Implementation(InMonoObject, InFunctionHash, InBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_GenericCall4Implementation;

        public static void FFunction_GenericCall4Implementation(nint InMonoObject, uint InFunctionHash, byte* OutBuffer)
        {
            if (__FFunction_GenericCall4Implementation == null)
            {
                __FFunction_GenericCall4Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall4Implementation");
            }

            __FFunction_GenericCall4Implementation(InMonoObject, InFunctionHash, OutBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>
            __FFunction_GenericCall6Implementation;

        public static void FFunction_GenericCall6Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer,
            byte* OutBuffer)
        {
            if (__FFunction_GenericCall6Implementation == null)
            {
                __FFunction_GenericCall6Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall6Implementation");
            }

            __FFunction_GenericCall6Implementation(InMonoObject, InFunctionHash, InBuffer, OutBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>
            __FFunction_PrimitiveCall7Implementation;

        public static void FFunction_PrimitiveCall7Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_PrimitiveCall7Implementation == null)
            {
                __FFunction_PrimitiveCall7Implementation =
                    (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_PrimitiveCall7Implementation");
            }

            __FFunction_PrimitiveCall7Implementation(InMonoObject, InFunctionHash, InBuffer, OutBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>
            __FFunction_CompoundCall7Implementation;

        public static void FFunction_CompoundCall7Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer,
            byte* OutBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_CompoundCall7Implementation == null)
            {
                __FFunction_CompoundCall7Implementation =
                    (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_CompoundCall7Implementation");
            }

            __FFunction_CompoundCall7Implementation(InMonoObject, InFunctionHash, InBuffer, OutBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, void> __FFunction_GenericCall8Implementation;

        public static void FFunction_GenericCall8Implementation(nint InMonoObject, uint InFunctionHash)
        {
            if (__FFunction_GenericCall8Implementation == null)
            {
                __FFunction_GenericCall8Implementation = (delegate* unmanaged[Cdecl]<nint, uint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall8Implementation");
            }

            __FFunction_GenericCall8Implementation(InMonoObject, InFunctionHash);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_PrimitiveCall9Implementation;

        public static void FFunction_PrimitiveCall9Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer)
        {
            if (__FFunction_PrimitiveCall9Implementation == null)
            {
                __FFunction_PrimitiveCall9Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_PrimitiveCall9Implementation");
            }

            __FFunction_PrimitiveCall9Implementation(InMonoObject, InFunctionHash, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_CompoundCall9Implementation;

        public static void FFunction_CompoundCall9Implementation(nint InMonoObject, uint InFunctionHash,
            byte* ReturnBuffer)
        {
            if (__FFunction_CompoundCall9Implementation == null)
            {
                __FFunction_CompoundCall9Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_CompoundCall9Implementation");
            }

            __FFunction_CompoundCall9Implementation(InMonoObject, InFunctionHash, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_GenericCall10Implementation;

        public static void FFunction_GenericCall10Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer)
        {
            if (__FFunction_GenericCall10Implementation == null)
            {
                __FFunction_GenericCall10Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall10Implementation");
            }

            __FFunction_GenericCall10Implementation(InMonoObject, InFunctionHash, InBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>
            __FFunction_PrimitiveCall11Implementation;

        public static void FFunction_PrimitiveCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_PrimitiveCall11Implementation == null)
            {
                __FFunction_PrimitiveCall11Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_PrimitiveCall11Implementation");
            }

            __FFunction_PrimitiveCall11Implementation(InMonoObject, InFunctionHash, InBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>
            __FFunction_CompoundCall11Implementation;

        public static void FFunction_CompoundCall11Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_CompoundCall11Implementation == null)
            {
                __FFunction_CompoundCall11Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_CompoundCall11Implementation");
            }

            __FFunction_CompoundCall11Implementation(InMonoObject, InFunctionHash, InBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>
            __FFunction_GenericCall14Implementation;

        public static void FFunction_GenericCall14Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer,
            byte* OutBuffer)
        {
            if (__FFunction_GenericCall14Implementation == null)
            {
                __FFunction_GenericCall14Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall14Implementation");
            }

            __FFunction_GenericCall14Implementation(InMonoObject, InFunctionHash, InBuffer, OutBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>
            __FFunction_PrimitiveCall15Implementation;

        public static void FFunction_PrimitiveCall15Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_PrimitiveCall15Implementation == null)
            {
                __FFunction_PrimitiveCall15Implementation =
                    (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_PrimitiveCall15Implementation");
            }

            __FFunction_PrimitiveCall15Implementation(InMonoObject, InFunctionHash, InBuffer, OutBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>
            __FFunction_CompoundCall15Implementation;

        public static void FFunction_CompoundCall15Implementation(nint InMonoObject, uint InFunctionHash,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer)
        {
            if (__FFunction_CompoundCall15Implementation == null)
            {
                __FFunction_CompoundCall15Implementation =
                    (delegate* unmanaged[Cdecl]<nint, uint, byte*, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_CompoundCall15Implementation");
            }

            __FFunction_CompoundCall15Implementation(InMonoObject, InFunctionHash, InBuffer, OutBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, void> __FFunction_GenericCall16Implementation;

        public static void FFunction_GenericCall16Implementation(nint InMonoObject, uint InFunctionHash)
        {
            if (__FFunction_GenericCall16Implementation == null)
            {
                __FFunction_GenericCall16Implementation = (delegate* unmanaged[Cdecl]<nint, uint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall16Implementation");
            }

            __FFunction_GenericCall16Implementation(InMonoObject, InFunctionHash);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_GenericCall18Implementation;

        public static void FFunction_GenericCall18Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer)
        {
            if (__FFunction_GenericCall18Implementation == null)
            {
                __FFunction_GenericCall18Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall18Implementation");
            }

            __FFunction_GenericCall18Implementation(InMonoObject, InFunctionHash, InBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, void> __FFunction_GenericCall24Implementation;

        public static void FFunction_GenericCall24Implementation(nint InMonoObject, uint InFunctionHash)
        {
            if (__FFunction_GenericCall24Implementation == null)
            {
                __FFunction_GenericCall24Implementation = (delegate* unmanaged[Cdecl]<nint, uint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall24Implementation");
            }

            __FFunction_GenericCall24Implementation(InMonoObject, InFunctionHash);
        }

        private static delegate* unmanaged[Cdecl]<nint, uint, byte*, void> __FFunction_GenericCall26Implementation;

        public static void FFunction_GenericCall26Implementation(nint InMonoObject, uint InFunctionHash, byte* InBuffer)
        {
            if (__FFunction_GenericCall26Implementation == null)
            {
                __FFunction_GenericCall26Implementation = (delegate* unmanaged[Cdecl]<nint, uint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FFunctionImplementation::FFunction_GenericCall26Implementation");
            }

            __FFunction_GenericCall26Implementation(InMonoObject, InFunctionHash, InBuffer);
        }
#endif
    }
}