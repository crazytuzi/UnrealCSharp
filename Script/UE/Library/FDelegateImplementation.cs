using System;
using System.Reflection;
using Interop;

namespace Script.Library
{
    public static unsafe partial class FDelegateImplementation
    {
        private static unsafe partial void __FDelegate_RegisterImplementation(nint InDelegate, nint InType);

        public static void FDelegate_RegisterImplementation(object InDelegate, Type InType)
        {
            __FDelegate_RegisterImplementation(HandleData.Alloc(InDelegate), HandleData.Alloc(InType));
        }

        private static unsafe partial void __FDelegate_UnRegisterImplementation(nint InDelegate);

        public static void FDelegate_UnRegisterImplementation(nint InDelegate)
        {
            __FDelegate_UnRegisterImplementation(InDelegate);
        }

        private static unsafe partial void __FDelegate_BindImplementation(nint InDelegate, nint InObject, nint InType, nint InMethodInfo);

        public static void FDelegate_BindImplementation(nint InDelegate, nint InObject, Type InType,
            MethodInfo InMethodInfo)
        {
            __FDelegate_BindImplementation(InDelegate, InObject, HandleData.Alloc(InType),
                HandleData.Alloc(InMethodInfo));
        }

        private static unsafe partial byte __FDelegate_IsBoundImplementation(nint InDelegate);

        public static bool FDelegate_IsBoundImplementation(nint InDelegate)
        {
            return __FDelegate_IsBoundImplementation(InDelegate) != 0;
        }

        private static unsafe partial void __FDelegate_UnBindImplementation(nint InDelegate);

        public static void FDelegate_UnBindImplementation(nint InDelegate)
        {
            __FDelegate_UnBindImplementation(InDelegate);
        }

        private static unsafe partial void __FDelegate_ClearImplementation(nint InDelegate);

        public static void FDelegate_ClearImplementation(nint InDelegate)
        {
            __FDelegate_ClearImplementation(InDelegate);
        }

        private static unsafe partial void __FDelegate_GenericExecute0Implementation(nint InDelegate);

        public static void FDelegate_GenericExecute0Implementation(nint InDelegate)
        {
            __FDelegate_GenericExecute0Implementation(InDelegate);
        }

        private static unsafe partial void __FDelegate_PrimitiveExecute1Implementation(nint InDelegate, byte* ReturnBuffer);

        public static void FDelegate_PrimitiveExecute1Implementation(nint InDelegate, byte* ReturnBuffer)
        {
            __FDelegate_PrimitiveExecute1Implementation(InDelegate, ReturnBuffer);
        }

        private static unsafe partial void __FDelegate_CompoundExecute1Implementation(nint InDelegate, byte* ReturnBuffer);

        public static void FDelegate_CompoundExecute1Implementation(nint InDelegate, byte* ReturnBuffer)
        {
            __FDelegate_CompoundExecute1Implementation(InDelegate, ReturnBuffer);
        }

        private static unsafe partial void __FDelegate_GenericExecute2Implementation(nint InDelegate, byte* InBuffer);

        public static void FDelegate_GenericExecute2Implementation(nint InDelegate, byte* InBuffer)
        {
            __FDelegate_GenericExecute2Implementation(InDelegate, InBuffer);
        }

        private static unsafe partial void __FDelegate_PrimitiveExecute3Implementation(nint InDelegate, byte* InBuffer, byte* ReturnBuffer);

        public static void FDelegate_PrimitiveExecute3Implementation(nint InDelegate, byte* InBuffer,
            byte* ReturnBuffer)
        {
            __FDelegate_PrimitiveExecute3Implementation(InDelegate, InBuffer, ReturnBuffer);
        }

        private static unsafe partial void __FDelegate_CompoundExecute3Implementation(nint InDelegate, byte* InBuffer, byte* ReturnBuffer);

        public static void FDelegate_CompoundExecute3Implementation(nint InDelegate, byte* InBuffer,
            byte* ReturnBuffer)
        {
            __FDelegate_CompoundExecute3Implementation(InDelegate, InBuffer, ReturnBuffer);
        }

        private static unsafe partial void __FDelegate_GenericExecute4Implementation(nint InDelegate, byte* OutBuffer);

        public static void FDelegate_GenericExecute4Implementation(nint InDelegate, byte* OutBuffer)
        {
            __FDelegate_GenericExecute4Implementation(InDelegate, OutBuffer);
        }

        private static unsafe partial void __FDelegate_GenericExecute6Implementation(nint InDelegate, byte* InBuffer, byte* OutBuffer);

        public static void FDelegate_GenericExecute6Implementation(nint InDelegate, byte* InBuffer,
            byte* OutBuffer)
        {
            __FDelegate_GenericExecute6Implementation(InDelegate, InBuffer, OutBuffer);
        }

        private static unsafe partial void __FDelegate_PrimitiveExecute7Implementation(nint InDelegate, byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        public static void FDelegate_PrimitiveExecute7Implementation(nint InDelegate, byte* InBuffer,
            byte* OutBuffer, byte* ReturnBuffer)
        {
            __FDelegate_PrimitiveExecute7Implementation(InDelegate, InBuffer, OutBuffer, ReturnBuffer);
        }

        private static unsafe partial void __FDelegate_CompoundExecute7Implementation(nint InDelegate, byte* InBuffer, byte* OutBuffer, byte* ReturnBuffer);

        public static void FDelegate_CompoundExecute7Implementation(nint InDelegate, byte* InBuffer,
            byte* OutBuffer, byte* ReturnBuffer)
        {
            __FDelegate_CompoundExecute7Implementation(InDelegate, InBuffer, OutBuffer, ReturnBuffer);
        }
    }
}