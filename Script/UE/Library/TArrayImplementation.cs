using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static unsafe class TArrayImplementation
    {
        private static delegate* unmanaged[Cdecl]<nint, nint, void> __TArray_RegisterImplementation;

        public static void TArray_RegisterImplementation<T>(TArray<T> InArray, Type InType)
        {
            if (__TArray_RegisterImplementation == null)
            {
                __TArray_RegisterImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_RegisterImplementation");
            }

            __TArray_RegisterImplementation(HandleData.Alloc(InArray), HandleData.Alloc(InType));
        }

        private static delegate* unmanaged[Cdecl]<nint, nint, byte> __TArray_IdenticalImplementation;

        public static bool TArray_IdenticalImplementation(nint InA, nint InB)
        {
            if (__TArray_IdenticalImplementation == null)
            {
                __TArray_IdenticalImplementation = (delegate* unmanaged[Cdecl]<nint, nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_IdenticalImplementation");
            }

            return __TArray_IdenticalImplementation(InA, InB) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, void> __TArray_UnRegisterImplementation;

        public static void TArray_UnRegisterImplementation(nint InArray)
        {
            if (__TArray_UnRegisterImplementation == null)
            {
                __TArray_UnRegisterImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_UnRegisterImplementation");
            }

            __TArray_UnRegisterImplementation(InArray);
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TArray_GetTypeSizeImplementation;

        public static int TArray_GetTypeSizeImplementation(nint InArray)
        {
            if (__TArray_GetTypeSizeImplementation == null)
            {
                __TArray_GetTypeSizeImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_GetTypeSizeImplementation");
            }

            return __TArray_GetTypeSizeImplementation(InArray);
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TArray_GetSlackImplementation;

        public static int TArray_GetSlackImplementation(nint InArray)
        {
            if (__TArray_GetSlackImplementation == null)
            {
                __TArray_GetSlackImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_GetSlackImplementation");
            }

            return __TArray_GetSlackImplementation(InArray);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte> __TArray_IsValidIndexImplementation;

        public static bool TArray_IsValidIndexImplementation(nint InArray, int InIndex)
        {
            if (__TArray_IsValidIndexImplementation == null)
            {
                __TArray_IsValidIndexImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_IsValidIndexImplementation");
            }

            return __TArray_IsValidIndexImplementation(InArray, InIndex) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TArray_NumImplementation;

        public static int TArray_NumImplementation(nint InArray)
        {
            if (__TArray_NumImplementation == null)
            {
                __TArray_NumImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_NumImplementation");
            }

            return __TArray_NumImplementation(InArray);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte> __TArray_IsEmptyImplementation;

        public static bool TArray_IsEmptyImplementation(nint InArray)
        {
            if (__TArray_IsEmptyImplementation == null)
            {
                __TArray_IsEmptyImplementation = (delegate* unmanaged[Cdecl]<nint, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_IsEmptyImplementation");
            }

            return __TArray_IsEmptyImplementation(InArray) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, int> __TArray_MaxImplementation;

        public static int TArray_MaxImplementation(nint InArray)
        {
            if (__TArray_MaxImplementation == null)
            {
                __TArray_MaxImplementation = (delegate* unmanaged[Cdecl]<nint, int>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_MaxImplementation");
            }

            return __TArray_MaxImplementation(InArray);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte*, void> __TArray_GetImplementation;

        public static void TArray_GetImplementation(nint InArray, int InIndex, byte* ReturnBuffer)
        {
            if (__TArray_GetImplementation == null)
            {
                __TArray_GetImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_GetImplementation");
            }

            __TArray_GetImplementation(InArray, InIndex, ReturnBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte*, void> __TArray_SetImplementation;

        public static void TArray_SetImplementation(nint InArray, int InIndex, byte* InValueBuffer)
        {
            if (__TArray_SetImplementation == null)
            {
                __TArray_SetImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_SetImplementation");
            }

            __TArray_SetImplementation(InArray, InIndex, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TArray_FindImplementation;

        public static int TArray_FindImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_FindImplementation == null)
            {
                __TArray_FindImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_FindImplementation");
            }

            return __TArray_FindImplementation(InArray, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TArray_FindLastImplementation;

        public static int TArray_FindLastImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_FindLastImplementation == null)
            {
                __TArray_FindLastImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_FindLastImplementation");
            }

            return __TArray_FindLastImplementation(InArray, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, byte> __TArray_ContainsImplementation;

        public static bool TArray_ContainsImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_ContainsImplementation == null)
            {
                __TArray_ContainsImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, byte>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_ContainsImplementation");
            }

            return __TArray_ContainsImplementation(InArray, InValueBuffer) != 0;
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int> __TArray_AddUninitializedImplementation;

        public static int TArray_AddUninitializedImplementation(nint InArray, int InCount)
        {
            if (__TArray_AddUninitializedImplementation == null)
            {
                __TArray_AddUninitializedImplementation = (delegate* unmanaged[Cdecl]<nint, int, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_AddUninitializedImplementation");
            }

            return __TArray_AddUninitializedImplementation(InArray, InCount);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int, void> __TArray_InsertZeroedImplementation;

        public static void TArray_InsertZeroedImplementation(nint InArray, int InIndex, int InCount)
        {
            if (__TArray_InsertZeroedImplementation == null)
            {
                __TArray_InsertZeroedImplementation = (delegate* unmanaged[Cdecl]<nint, int, int, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_InsertZeroedImplementation");
            }

            __TArray_InsertZeroedImplementation(InArray, InIndex, InCount);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int, void> __TArray_InsertDefaultedImplementation;

        public static void TArray_InsertDefaultedImplementation(nint InArray, int InIndex, int InCount)
        {
            if (__TArray_InsertDefaultedImplementation == null)
            {
                __TArray_InsertDefaultedImplementation = (delegate* unmanaged[Cdecl]<nint, int, int, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_InsertDefaultedImplementation");
            }

            __TArray_InsertDefaultedImplementation(InArray, InIndex, InCount);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int, byte, void> __TArray_RemoveAtImplementation;

        public static void TArray_RemoveAtImplementation(nint InArray, int InIndex, int InCount,
            bool bAllowShrinking)
        {
            if (__TArray_RemoveAtImplementation == null)
            {
                __TArray_RemoveAtImplementation = (delegate* unmanaged[Cdecl]<nint, int, int, byte, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_RemoveAtImplementation");
            }

            __TArray_RemoveAtImplementation(InArray, InIndex, InCount, (byte)(bAllowShrinking ? 1 : 0));
        }

        private static delegate* unmanaged[Cdecl]<nint, int, void> __TArray_ResetImplementation;

        public static void TArray_ResetImplementation(nint InArray, int InNewSize)
        {
            if (__TArray_ResetImplementation == null)
            {
                __TArray_ResetImplementation = (delegate* unmanaged[Cdecl]<nint, int, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_ResetImplementation");
            }

            __TArray_ResetImplementation(InArray, InNewSize);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, void> __TArray_EmptyImplementation;

        public static void TArray_EmptyImplementation(nint InArray, int InSlack)
        {
            if (__TArray_EmptyImplementation == null)
            {
                __TArray_EmptyImplementation = (delegate* unmanaged[Cdecl]<nint, int, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_EmptyImplementation");
            }

            __TArray_EmptyImplementation(InArray, InSlack);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, byte, void> __TArray_SetNumImplementation;

        public static void TArray_SetNumImplementation(nint InArray, int InNewNum, bool bAllowShrinking)
        {
            if (__TArray_SetNumImplementation == null)
            {
                __TArray_SetNumImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_SetNumImplementation");
            }

            __TArray_SetNumImplementation(InArray, InNewNum, (byte)(bAllowShrinking ? 1 : 0));
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TArray_AddImplementation;

        public static int TArray_AddImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_AddImplementation == null)
            {
                __TArray_AddImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_AddImplementation");
            }

            return __TArray_AddImplementation(InArray, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int> __TArray_AddZeroedImplementation;

        public static int TArray_AddZeroedImplementation(nint InArray, int InCount)
        {
            if (__TArray_AddZeroedImplementation == null)
            {
                __TArray_AddZeroedImplementation = (delegate* unmanaged[Cdecl]<nint, int, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_AddZeroedImplementation");
            }

            return __TArray_AddZeroedImplementation(InArray, InCount);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TArray_AddUniqueImplementation;

        public static int TArray_AddUniqueImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_AddUniqueImplementation == null)
            {
                __TArray_AddUniqueImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_AddUniqueImplementation");
            }

            return __TArray_AddUniqueImplementation(InArray, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TArray_RemoveSingleImplementation;

        public static int TArray_RemoveSingleImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_RemoveSingleImplementation == null)
            {
                __TArray_RemoveSingleImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_RemoveSingleImplementation");
            }

            return __TArray_RemoveSingleImplementation(InArray, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, byte*, int> __TArray_RemoveImplementation;

        public static int TArray_RemoveImplementation(nint InArray, byte* InValueBuffer)
        {
            if (__TArray_RemoveImplementation == null)
            {
                __TArray_RemoveImplementation = (delegate* unmanaged[Cdecl]<nint, byte*, int>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_RemoveImplementation");
            }

            return __TArray_RemoveImplementation(InArray, InValueBuffer);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int, void> __TArray_SwapMemoryImplementation;

        public static void TArray_SwapMemoryImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap)
        {
            if (__TArray_SwapMemoryImplementation == null)
            {
                __TArray_SwapMemoryImplementation = (delegate* unmanaged[Cdecl]<nint, int, int, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_SwapMemoryImplementation");
            }

            __TArray_SwapMemoryImplementation(InArray, InFirstIndexToSwap, InSecondIndexToSwap);
        }

        private static delegate* unmanaged[Cdecl]<nint, int, int, void> __TArray_SwapImplementation;

        public static void TArray_SwapImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap)
        {
            if (__TArray_SwapImplementation == null)
            {
                __TArray_SwapImplementation = (delegate* unmanaged[Cdecl]<nint, int, int, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_SwapImplementation");
            }

            __TArray_SwapImplementation(InArray, InFirstIndexToSwap, InSecondIndexToSwap);
        }

        private static delegate* unmanaged[Cdecl]<int> __TArray_INDEX_NONEImplementation;

        public static int TArray_INDEX_NONEImplementation()
        {
            if (__TArray_INDEX_NONEImplementation == null)
            {
                __TArray_INDEX_NONEImplementation = (delegate* unmanaged[Cdecl]<int>)
                    MethodBridge.GetMethod(
                        "Script.Library.TArrayImplementation::TArray_INDEX_NONEImplementation");
            }

            return __TArray_INDEX_NONEImplementation();
        }

        public static T TArray_GetCompoundImplementation<T>(nint InArray, int InIndex)
        {
            if (__TArray_GetImplementation == null)
            {
                __TArray_GetImplementation = (delegate* unmanaged[Cdecl]<nint, int, byte*, void>)
                    MethodBridge.GetMethod("Script.Library.TArrayImplementation::TArray_GetImplementation");
            }

            var ValueBuffer = stackalloc byte[sizeof(nint)];

            __TArray_GetImplementation(InArray, InIndex, ValueBuffer);

            var Handle = *(nint*)ValueBuffer;

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}