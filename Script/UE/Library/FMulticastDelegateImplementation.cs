using System;
using System.Reflection;
using Interop;

namespace Script.Library
{
    public static unsafe class FMulticastDelegateImplementation
    {
        private static delegate* unmanaged[Cdecl]<nint, nint, void>
            __FMulticastDelegate_RegisterImplementation;

        public static void FMulticastDelegate_RegisterImplementation(object InMonoObject, Type InType)
        {
            if (__FMulticastDelegate_RegisterImplementation == null)
            {
                __FMulticastDelegate_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_RegisterImplementation");
            }

            __FMulticastDelegate_RegisterImplementation(HandleData.Alloc(InMonoObject), HandleData.Alloc(InType));
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __FMulticastDelegate_UnRegisterImplementation;

        public static void FMulticastDelegate_UnRegisterImplementation(nint InMonoObject)
        {
            if (__FMulticastDelegate_UnRegisterImplementation == null)
            {
                __FMulticastDelegate_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_UnRegisterImplementation");
            }

            __FMulticastDelegate_UnRegisterImplementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte> __FMulticastDelegate_IsBoundImplementation;

        public static unsafe bool FMulticastDelegate_IsBoundImplementation(nint InMonoObject)
        {
            if (__FMulticastDelegate_IsBoundImplementation == null)
            {
                __FMulticastDelegate_IsBoundImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_IsBoundImplementation");
            }

            return __FMulticastDelegate_IsBoundImplementation(InMonoObject) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, nint, nint, byte>
            __FMulticastDelegate_ContainsImplementation;

        public static bool FMulticastDelegate_ContainsImplementation(nint InMonoObject, nint InObject,
            Type InType, MethodInfo InMethodInfo)
        {
            if (__FMulticastDelegate_ContainsImplementation == null)
            {
                __FMulticastDelegate_ContainsImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_ContainsImplementation");
            }

            return __FMulticastDelegate_ContainsImplementation(InMonoObject, InObject,
                HandleData.Alloc(InType), HandleData.Alloc(InMethodInfo)) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __FMulticastDelegate_AddImplementation;

        public static void FMulticastDelegate_AddImplementation(nint InMonoObject, nint InObject, Type InType,
            MethodInfo InMethodInfo)
        {
            if (__FMulticastDelegate_AddImplementation == null)
            {
                __FMulticastDelegate_AddImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_AddImplementation");
            }

            __FMulticastDelegate_AddImplementation(InMonoObject, InObject, HandleData.Alloc(InType),
                HandleData.Alloc(InMethodInfo));
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __FMulticastDelegate_AddUniqueImplementation;

        public static void FMulticastDelegate_AddUniqueImplementation(nint InMonoObject, nint InObject,
            Type InType, MethodInfo InMethodInfo)
        {
            if (__FMulticastDelegate_AddUniqueImplementation == null)
            {
                __FMulticastDelegate_AddUniqueImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_AddUniqueImplementation");
            }

            __FMulticastDelegate_AddUniqueImplementation(InMonoObject, InObject,
                HandleData.Alloc(InType), HandleData.Alloc(InMethodInfo));
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __FMulticastDelegate_RemoveImplementation;

        public static void FMulticastDelegate_RemoveImplementation(nint InMonoObject, nint InObject, Type InType,
            MethodInfo InMethodInfo)
        {
            if (__FMulticastDelegate_RemoveImplementation == null)
            {
                __FMulticastDelegate_RemoveImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_RemoveImplementation");
            }

            __FMulticastDelegate_RemoveImplementation(InMonoObject, InObject, HandleData.Alloc(InType),
                HandleData.Alloc(InMethodInfo));
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, void> __FMulticastDelegate_RemoveAllImplementation;

        public static void FMulticastDelegate_RemoveAllImplementation(nint InMonoObject, nint InObject)
        {
            if (__FMulticastDelegate_RemoveAllImplementation == null)
            {
                __FMulticastDelegate_RemoveAllImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_RemoveAllImplementation");
            }

            __FMulticastDelegate_RemoveAllImplementation(InMonoObject, InObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __FMulticastDelegate_ClearImplementation;

        public static void FMulticastDelegate_ClearImplementation(nint InMonoObject)
        {
            if (__FMulticastDelegate_ClearImplementation == null)
            {
                __FMulticastDelegate_ClearImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_ClearImplementation");
            }

            __FMulticastDelegate_ClearImplementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, void>
            __FMulticastDelegate_GenericBroadcast0Implementation;

        public static void FMulticastDelegate_GenericBroadcast0Implementation(nint InMonoObject)
        {
            if (__FMulticastDelegate_GenericBroadcast0Implementation == null)
            {
                __FMulticastDelegate_GenericBroadcast0Implementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_GenericBroadcast0Implementation");
            }

            __FMulticastDelegate_GenericBroadcast0Implementation(InMonoObject);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void>
            __FMulticastDelegate_GenericBroadcast2Implementation;

        public static void FMulticastDelegate_GenericBroadcast2Implementation(nint InMonoObject, byte* InBuffer)
        {
            if (__FMulticastDelegate_GenericBroadcast2Implementation == null)
            {
                __FMulticastDelegate_GenericBroadcast2Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_GenericBroadcast2Implementation");
            }

            __FMulticastDelegate_GenericBroadcast2Implementation(InMonoObject, InBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void>
            __FMulticastDelegate_GenericBroadcast4Implementation;

        public static void FMulticastDelegate_GenericBroadcast4Implementation(nint InMonoObject, byte* OutBuffer)
        {
            if (__FMulticastDelegate_GenericBroadcast4Implementation == null)
            {
                __FMulticastDelegate_GenericBroadcast4Implementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_GenericBroadcast4Implementation");
            }

            __FMulticastDelegate_GenericBroadcast4Implementation(InMonoObject, OutBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>
            __FMulticastDelegate_GenericBroadcast6Implementation;

        public static void FMulticastDelegate_GenericBroadcast6Implementation(nint InMonoObject, byte* InBuffer,
            byte* OutBuffer)
        {
            if (__FMulticastDelegate_GenericBroadcast6Implementation == null)
            {
                __FMulticastDelegate_GenericBroadcast6Implementation =
                    (delegate* unmanaged[Cdecl]<nint, byte*, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.FMulticastDelegateImplementation::FMulticastDelegate_GenericBroadcast6Implementation");
            }

            __FMulticastDelegate_GenericBroadcast6Implementation(InMonoObject, InBuffer, OutBuffer);
        }
    }
}