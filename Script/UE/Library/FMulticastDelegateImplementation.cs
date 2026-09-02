using System;
using System.Reflection;
using Interop;

namespace Script.Library
{
    public static unsafe partial class FMulticastDelegateImplementation
    {
        private static unsafe partial void __FMulticastDelegate_RegisterImplementation(nint InDelegate, nint InType);

        public static void FMulticastDelegate_RegisterImplementation(object InDelegate, Type InType)
        {
            __FMulticastDelegate_RegisterImplementation(HandleData.Alloc(InDelegate), HandleData.Alloc(InType));
        }

        private static unsafe partial void __FMulticastDelegate_UnRegisterImplementation(nint InDelegate);

        public static void FMulticastDelegate_UnRegisterImplementation(nint InDelegate)
        {
            __FMulticastDelegate_UnRegisterImplementation(InDelegate);
        }

        private static unsafe partial byte __FMulticastDelegate_IsBoundImplementation(nint InDelegate);

        public static unsafe bool FMulticastDelegate_IsBoundImplementation(nint InDelegate)
        {
            return __FMulticastDelegate_IsBoundImplementation(InDelegate) != 0;
        }

        private static unsafe partial byte __FMulticastDelegate_ContainsImplementation(nint InDelegate, nint InObject, nint InType, nint InMethodInfo);

        public static bool FMulticastDelegate_ContainsImplementation(nint InDelegate, nint InObject,
            Type InType, MethodInfo InMethodInfo)
        {
            return __FMulticastDelegate_ContainsImplementation(InDelegate, InObject,
                HandleData.Alloc(InType), HandleData.Alloc(InMethodInfo)) != 0;
        }

        private static unsafe partial void __FMulticastDelegate_AddImplementation(nint InDelegate, nint InObject, nint InType, nint InMethodInfo);

        public static void FMulticastDelegate_AddImplementation(nint InDelegate, nint InObject, Type InType,
            MethodInfo InMethodInfo)
        {
            __FMulticastDelegate_AddImplementation(InDelegate, InObject, HandleData.Alloc(InType),
                HandleData.Alloc(InMethodInfo));
        }

        private static unsafe partial void __FMulticastDelegate_AddUniqueImplementation(nint InDelegate, nint InObject, nint InType, nint InMethodInfo);

        public static void FMulticastDelegate_AddUniqueImplementation(nint InDelegate, nint InObject,
            Type InType, MethodInfo InMethodInfo)
        {
            __FMulticastDelegate_AddUniqueImplementation(InDelegate, InObject,
                HandleData.Alloc(InType), HandleData.Alloc(InMethodInfo));
        }

        private static unsafe partial void __FMulticastDelegate_RemoveImplementation(nint InDelegate, nint InObject, nint InType, nint InMethodInfo);

        public static void FMulticastDelegate_RemoveImplementation(nint InDelegate, nint InObject, Type InType,
            MethodInfo InMethodInfo)
        {
            __FMulticastDelegate_RemoveImplementation(InDelegate, InObject, HandleData.Alloc(InType),
                HandleData.Alloc(InMethodInfo));
        }

        private static unsafe partial void __FMulticastDelegate_RemoveAllImplementation(nint InDelegate, nint InObject);

        public static void FMulticastDelegate_RemoveAllImplementation(nint InDelegate, nint InObject)
        {
            __FMulticastDelegate_RemoveAllImplementation(InDelegate, InObject);
        }

        private static unsafe partial void __FMulticastDelegate_ClearImplementation(nint InDelegate);

        public static void FMulticastDelegate_ClearImplementation(nint InDelegate)
        {
            __FMulticastDelegate_ClearImplementation(InDelegate);
        }

        private static unsafe partial void __FMulticastDelegate_GenericBroadcast0Implementation(nint InDelegate);

        public static void FMulticastDelegate_GenericBroadcast0Implementation(nint InDelegate)
        {
            __FMulticastDelegate_GenericBroadcast0Implementation(InDelegate);
        }

        private static unsafe partial void __FMulticastDelegate_GenericBroadcast2Implementation(nint InDelegate, byte* InBuffer);

        public static void FMulticastDelegate_GenericBroadcast2Implementation(nint InDelegate, byte* InBuffer)
        {
            __FMulticastDelegate_GenericBroadcast2Implementation(InDelegate, InBuffer);
        }

        private static unsafe partial void __FMulticastDelegate_GenericBroadcast4Implementation(nint InDelegate, byte* OutBuffer);

        public static void FMulticastDelegate_GenericBroadcast4Implementation(nint InDelegate, byte* OutBuffer)
        {
            __FMulticastDelegate_GenericBroadcast4Implementation(InDelegate, OutBuffer);
        }

        private static unsafe partial void __FMulticastDelegate_GenericBroadcast6Implementation(nint InDelegate, byte* InBuffer, byte* OutBuffer);

        public static void FMulticastDelegate_GenericBroadcast6Implementation(nint InDelegate, byte* InBuffer,
            byte* OutBuffer)
        {
            __FMulticastDelegate_GenericBroadcast6Implementation(InDelegate, InBuffer, OutBuffer);
        }
    }
}