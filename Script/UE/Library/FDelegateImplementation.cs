using System;
using System.Reflection;
#if WITH_MONO
using System.Runtime.CompilerServices;
#else
using Interop;
#endif

namespace Script.Library
{
    public static unsafe class FDelegateImplementation
    {
#if WITH_MONO
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_RegisterImplementation(object InMonoObject, Type InType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_UnRegisterImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_BindImplementation(nint InMonoObject,
            nint InObject, Type InType, MethodInfo InMethodInfo);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FDelegate_IsBoundImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_UnBindImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_ClearImplementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute0Implementation(nint InMonoObject);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_PrimitiveExecute1Implementation(nint InMonoObject,
            byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_CompoundExecute1Implementation(nint InMonoObject,
            byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute2Implementation(nint InMonoObject,
            byte* InBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_PrimitiveExecute3Implementation(nint InMonoObject,
            byte* InBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_CompoundExecute3Implementation(nint InMonoObject,
            byte* InBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute4Implementation(nint InMonoObject,
            byte* OutBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_GenericExecute6Implementation(nint InMonoObject,
            byte* InBuffer, byte* OutBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_PrimitiveExecute7Implementation(nint InMonoObject,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FDelegate_CompoundExecute7Implementation(nint InMonoObject,
            byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);
#else
        private static delegate* unmanaged[Cdecl]<object, nint, void> __FDelegate_RegisterImplementation;

        public static void FDelegate_RegisterImplementation(object InMonoObject, Type InType)
        {
            if (__FDelegate_RegisterImplementation == null)
            {
                __FDelegate_RegisterImplementation = (delegate* unmanaged[Cdecl]<object, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_RegisterImplementation");
            }

            __FDelegate_RegisterImplementation(InMonoObject, HandleData.AllocImplementation(InType));
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __FDelegate_UnRegisterImplementation;

        public static void FDelegate_UnRegisterImplementation(nint InMonoObject)
        {
            if (__FDelegate_UnRegisterImplementation == null)
            {
                __FDelegate_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_UnRegisterImplementation");
            }

            __FDelegate_UnRegisterImplementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void> __FDelegate_BindImplementation;

        public static void FDelegate_BindImplementation(nint InMonoObject, nint InObject, Type InType,
            MethodInfo InMethodInfo)
        {
            if (__FDelegate_BindImplementation == null)
            {
                __FDelegate_BindImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_BindImplementation");
            }

            __FDelegate_BindImplementation(InMonoObject, InObject, HandleData.AllocImplementation(InType),
                (nint)HandleData.AllocImplementation(InMethodInfo));
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __FDelegate_IsBoundImplementation;

        public static bool FDelegate_IsBoundImplementation(nint InMonoObject)
        {
            if (__FDelegate_IsBoundImplementation == null)
            {
                __FDelegate_IsBoundImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_IsBoundImplementation");
            }

            return __FDelegate_IsBoundImplementation(InMonoObject) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __FDelegate_UnBindImplementation;

        public static void FDelegate_UnBindImplementation(nint InMonoObject)
        {
            if (__FDelegate_UnBindImplementation == null)
            {
                __FDelegate_UnBindImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_UnBindImplementation");
            }

            __FDelegate_UnBindImplementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __FDelegate_ClearImplementation;

        public static void FDelegate_ClearImplementation(nint InMonoObject)
        {
            if (__FDelegate_ClearImplementation == null)
            {
                __FDelegate_ClearImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_ClearImplementation");
            }

            __FDelegate_ClearImplementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __FDelegate_GenericExecute0Implementation;

        public static void FDelegate_GenericExecute0Implementation(nint InMonoObject)
        {
            if (__FDelegate_GenericExecute0Implementation == null)
            {
                __FDelegate_GenericExecute0Implementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_GenericExecute0Implementation");
            }

            __FDelegate_GenericExecute0Implementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void> __FDelegate_PrimitiveExecute1Implementation;

        public static void FDelegate_PrimitiveExecute1Implementation(nint InMonoObject, byte* ReturnBuffer)
        {
            if (__FDelegate_PrimitiveExecute1Implementation == null)
            {
                __FDelegate_PrimitiveExecute1Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_PrimitiveExecute1Implementation");
            }

            __FDelegate_PrimitiveExecute1Implementation(InMonoObject, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void> __FDelegate_CompoundExecute1Implementation;

        public static void FDelegate_CompoundExecute1Implementation(nint InMonoObject, byte* ReturnBuffer)
        {
            if (__FDelegate_CompoundExecute1Implementation == null)
            {
                __FDelegate_CompoundExecute1Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_CompoundExecute1Implementation");
            }

            __FDelegate_CompoundExecute1Implementation(InMonoObject, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void> __FDelegate_GenericExecute2Implementation;

        public static void FDelegate_GenericExecute2Implementation(nint InMonoObject, byte* InBuffer)
        {
            if (__FDelegate_GenericExecute2Implementation == null)
            {
                __FDelegate_GenericExecute2Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_GenericExecute2Implementation");
            }

            __FDelegate_GenericExecute2Implementation(InMonoObject, InBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>
            __FDelegate_PrimitiveExecute3Implementation;

        public static void FDelegate_PrimitiveExecute3Implementation(nint InMonoObject, byte* InBuffer,
            byte* ReturnBuffer)
        {
            if (__FDelegate_PrimitiveExecute3Implementation == null)
            {
                __FDelegate_PrimitiveExecute3Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_PrimitiveExecute3Implementation");
            }

            __FDelegate_PrimitiveExecute3Implementation(InMonoObject, InBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>
            __FDelegate_CompoundExecute3Implementation;

        public static void FDelegate_CompoundExecute3Implementation(nint InMonoObject, byte* InBuffer,
            byte* ReturnBuffer)
        {
            if (__FDelegate_CompoundExecute3Implementation == null)
            {
                __FDelegate_CompoundExecute3Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_CompoundExecute3Implementation");
            }

            __FDelegate_CompoundExecute3Implementation(InMonoObject, InBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void> __FDelegate_GenericExecute4Implementation;

        public static void FDelegate_GenericExecute4Implementation(nint InMonoObject, byte* OutBuffer)
        {
            if (__FDelegate_GenericExecute4Implementation == null)
            {
                __FDelegate_GenericExecute4Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_GenericExecute4Implementation");
            }

            __FDelegate_GenericExecute4Implementation(InMonoObject, OutBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>
            __FDelegate_GenericExecute6Implementation;

        public static void FDelegate_GenericExecute6Implementation(nint InMonoObject, byte* InBuffer,
            byte* OutBuffer)
        {
            if (__FDelegate_GenericExecute6Implementation == null)
            {
                __FDelegate_GenericExecute6Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_GenericExecute6Implementation");
            }

            __FDelegate_GenericExecute6Implementation(InMonoObject, InBuffer, OutBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, byte*, void>
            __FDelegate_PrimitiveExecute7Implementation;

        public static void FDelegate_PrimitiveExecute7Implementation(nint InMonoObject, byte* InBuffer,
            byte* OutBuffer, byte* ReturnBuffer)
        {
            if (__FDelegate_PrimitiveExecute7Implementation == null)
            {
                __FDelegate_PrimitiveExecute7Implementation =
                    (delegate* unmanaged[Cdecl]<nint, byte*, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_PrimitiveExecute7Implementation");
            }

            __FDelegate_PrimitiveExecute7Implementation(InMonoObject, InBuffer, OutBuffer, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, byte*, void>
            __FDelegate_CompoundExecute7Implementation;

        public static void FDelegate_CompoundExecute7Implementation(nint InMonoObject, byte* InBuffer,
            byte* OutBuffer, byte* ReturnBuffer)
        {
            if (__FDelegate_CompoundExecute7Implementation == null)
            {
                __FDelegate_CompoundExecute7Implementation =
                    (delegate* unmanaged[Cdecl]<nint, byte*, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FDelegateImplementation::FDelegate_CompoundExecute7Implementation");
            }

            __FDelegate_CompoundExecute7Implementation(InMonoObject, InBuffer, OutBuffer, ReturnBuffer);
        }
#endif
    }
}