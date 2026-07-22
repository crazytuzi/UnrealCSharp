using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static unsafe class TSetImplementation
    {
        private static delegate* unmanaged[Cdecl]<nint, nint, void> __TSet_RegisterImplementation;

        public static void TSet_RegisterImplementation<T>(TSet<T> InSet, Type InType)
        {
            if (__TSet_RegisterImplementation == null)
            {
                __TSet_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_RegisterImplementation");
            }

            __TSet_RegisterImplementation(HandleData.Alloc(InSet), HandleData.Alloc(InType));
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __TSet_UnRegisterImplementation;

        public static void TSet_UnRegisterImplementation(nint InSet)
        {
            if (__TSet_UnRegisterImplementation == null)
            {
                __TSet_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_UnRegisterImplementation");
            }

            __TSet_UnRegisterImplementation(InSet);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, void> __TSet_EmptyImplementation;

        public static void TSet_EmptyImplementation(nint InSet, int InExpectedNumElements)
        {
            if (__TSet_EmptyImplementation == null)
            {
                __TSet_EmptyImplementation = (delegate* unmanaged[Cdecl]<nint, int, void>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_EmptyImplementation");
            }

            __TSet_EmptyImplementation(InSet, InExpectedNumElements);
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TSet_NumImplementation;

        public static int TSet_NumImplementation(nint InSet)
        {
            if (__TSet_NumImplementation == null)
            {
                __TSet_NumImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_NumImplementation");
            }

            return __TSet_NumImplementation(InSet);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte> __TSet_IsEmptyImplementation;

        public static bool TSet_IsEmptyImplementation(nint InSet)
        {
            if (__TSet_IsEmptyImplementation == null)
            {
                __TSet_IsEmptyImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_IsEmptyImplementation");
            }

            return __TSet_IsEmptyImplementation(InSet) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TSet_GetMaxIndexImplementation;

        public static int TSet_GetMaxIndexImplementation(nint InSet)
        {
            if (__TSet_GetMaxIndexImplementation == null)
            {
                __TSet_GetMaxIndexImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSetImplementation::TSet_GetMaxIndexImplementation");
            }

            return __TSet_GetMaxIndexImplementation(InSet);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte> __TSet_IsValidIndexImplementation;

        public static bool TSet_IsValidIndexImplementation(nint InSet, int InIndex)
        {
            if (__TSet_IsValidIndexImplementation == null)
            {
                __TSet_IsValidIndexImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSetImplementation::TSet_IsValidIndexImplementation");
            }

            return __TSet_IsValidIndexImplementation(InSet, InIndex) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, void> __TSet_AddImplementation;

        public static void TSet_AddImplementation(nint InSet, byte* InValueBuffer)
        {
            if (__TSet_AddImplementation == null)
            {
                __TSet_AddImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_AddImplementation");
            }

            __TSet_AddImplementation(InSet, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TSet_RemoveImplementation;

        public static int TSet_RemoveImplementation(nint InSet, byte* InValueBuffer)
        {
            if (__TSet_RemoveImplementation == null)
            {
                __TSet_RemoveImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_RemoveImplementation");
            }

            return __TSet_RemoveImplementation(InSet, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte> __TSet_ContainsImplementation;

        public static bool TSet_ContainsImplementation(nint InSet, byte* InValueBuffer)
        {
            if (__TSet_ContainsImplementation == null)
            {
                __TSet_ContainsImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte>)
                    MethodBridge.GetMethod("Script.Library.TSetImplementation::TSet_ContainsImplementation");
            }

            return __TSet_ContainsImplementation(InSet, InValueBuffer) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte*, void> __TSet_GetEnumeratorImplementation;

        public static void TSet_GetEnumeratorImplementation(nint InSet, int InIndex, byte* ReturnBuffer)
        {
            if (__TSet_GetEnumeratorImplementation == null)
            {
                __TSet_GetEnumeratorImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSetImplementation::TSet_GetEnumeratorImplementation");
            }

            __TSet_GetEnumeratorImplementation(InSet, InIndex, ReturnBuffer);
        }

        public static T TSet_GetEnumeratorCompoundImplementation<T>(nint InSet, int InIndex)
        {
            if (__TSet_GetEnumeratorImplementation == null)
            {
                __TSet_GetEnumeratorImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TSetImplementation::TSet_GetEnumeratorImplementation");
            }

            var ReturnBuffer = stackalloc byte[sizeof(nint)];

            __TSet_GetEnumeratorImplementation(InSet, InIndex, ReturnBuffer);

            var Handle = *(nint*)ReturnBuffer;

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}