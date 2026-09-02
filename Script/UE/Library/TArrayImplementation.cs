using System;
using Script.CoreUObject;
using Interop;

namespace Script.Library
{
    public static unsafe partial class TArrayImplementation
    {
        private static unsafe partial void __TArray_RegisterImplementation(nint InArray, nint InType);

        public static void TArray_RegisterImplementation<T>(TArray<T> InArray, Type InType)
        {
            __TArray_RegisterImplementation(HandleData.Alloc(InArray), HandleData.Alloc(InType));
        }

        private static unsafe partial byte __TArray_IdenticalImplementation(nint InA, nint InB);

        public static bool TArray_IdenticalImplementation(nint InA, nint InB)
        {
            return __TArray_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TArray_UnRegisterImplementation(nint InArray);

        public static void TArray_UnRegisterImplementation(nint InArray)
        {
            __TArray_UnRegisterImplementation(InArray);
        }

        private static unsafe partial int __TArray_GetTypeSizeImplementation(nint InArray);

        public static int TArray_GetTypeSizeImplementation(nint InArray)
        {
            return __TArray_GetTypeSizeImplementation(InArray);
        }

        private static unsafe partial int __TArray_GetSlackImplementation(nint InArray);

        public static int TArray_GetSlackImplementation(nint InArray)
        {
            return __TArray_GetSlackImplementation(InArray);
        }

        private static unsafe partial byte __TArray_IsValidIndexImplementation(nint InArray, int InIndex);

        public static bool TArray_IsValidIndexImplementation(nint InArray, int InIndex)
        {
            return __TArray_IsValidIndexImplementation(InArray, InIndex) != 0;
        }

        private static unsafe partial int __TArray_NumImplementation(nint InArray);

        public static int TArray_NumImplementation(nint InArray)
        {
            return __TArray_NumImplementation(InArray);
        }

        private static unsafe partial byte __TArray_IsEmptyImplementation(nint InArray);

        public static bool TArray_IsEmptyImplementation(nint InArray)
        {
            return __TArray_IsEmptyImplementation(InArray) != 0;
        }

        private static unsafe partial int __TArray_MaxImplementation(nint InArray);

        public static int TArray_MaxImplementation(nint InArray)
        {
            return __TArray_MaxImplementation(InArray);
        }

        private static unsafe partial void __TArray_GetImplementation(nint InArray, int InIndex, byte* ReturnBuffer);

        public static void TArray_GetImplementation(nint InArray, int InIndex, byte* ReturnBuffer)
        {
            __TArray_GetImplementation(InArray, InIndex, ReturnBuffer);
        }

        private static unsafe partial void __TArray_SetImplementation(nint InArray, int InIndex, byte* InValueBuffer);

        public static void TArray_SetImplementation(nint InArray, int InIndex, byte* InValueBuffer)
        {
            __TArray_SetImplementation(InArray, InIndex, InValueBuffer);
        }

        private static unsafe partial int __TArray_FindImplementation(nint InArray, byte* InValueBuffer);

        public static int TArray_FindImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_FindImplementation(InArray, InValueBuffer);
        }

        private static unsafe partial int __TArray_FindLastImplementation(nint InArray, byte* InValueBuffer);

        public static int TArray_FindLastImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_FindLastImplementation(InArray, InValueBuffer);
        }

        private static unsafe partial byte __TArray_ContainsImplementation(nint InArray, byte* InValueBuffer);

        public static bool TArray_ContainsImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_ContainsImplementation(InArray, InValueBuffer) != 0;
        }

        private static unsafe partial int __TArray_AddUninitializedImplementation(nint InArray, int InCount);

        public static int TArray_AddUninitializedImplementation(nint InArray, int InCount)
        {
            return __TArray_AddUninitializedImplementation(InArray, InCount);
        }

        private static unsafe partial void __TArray_InsertZeroedImplementation(nint InArray, int InIndex, int InCount);

        public static void TArray_InsertZeroedImplementation(nint InArray, int InIndex, int InCount)
        {
            __TArray_InsertZeroedImplementation(InArray, InIndex, InCount);
        }

        private static unsafe partial void __TArray_InsertDefaultedImplementation(nint InArray, int InIndex, int InCount);

        public static void TArray_InsertDefaultedImplementation(nint InArray, int InIndex, int InCount)
        {
            __TArray_InsertDefaultedImplementation(InArray, InIndex, InCount);
        }

        private static unsafe partial void __TArray_RemoveAtImplementation(nint InArray, int InIndex, int InCount, byte bAllowShrinking);

        public static void TArray_RemoveAtImplementation(nint InArray, int InIndex, int InCount,
            bool bAllowShrinking)
        {
            __TArray_RemoveAtImplementation(InArray, InIndex, InCount, (byte)(bAllowShrinking ? 1 : 0));
        }

        private static unsafe partial void __TArray_ResetImplementation(nint InArray, int InNewSize);

        public static void TArray_ResetImplementation(nint InArray, int InNewSize)
        {
            __TArray_ResetImplementation(InArray, InNewSize);
        }

        private static unsafe partial void __TArray_EmptyImplementation(nint InArray, int InSlack);

        public static void TArray_EmptyImplementation(nint InArray, int InSlack)
        {
            __TArray_EmptyImplementation(InArray, InSlack);
        }

        private static unsafe partial void __TArray_SetNumImplementation(nint InArray, int InNewNum, byte bAllowShrinking);

        public static void TArray_SetNumImplementation(nint InArray, int InNewNum, bool bAllowShrinking)
        {
            __TArray_SetNumImplementation(InArray, InNewNum, (byte)(bAllowShrinking ? 1 : 0));
        }

        private static unsafe partial int __TArray_AddImplementation(nint InArray, byte* InValueBuffer);

        public static int TArray_AddImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_AddImplementation(InArray, InValueBuffer);
        }

        private static unsafe partial int __TArray_AddZeroedImplementation(nint InArray, int InCount);

        public static int TArray_AddZeroedImplementation(nint InArray, int InCount)
        {
            return __TArray_AddZeroedImplementation(InArray, InCount);
        }

        private static unsafe partial int __TArray_AddUniqueImplementation(nint InArray, byte* InValueBuffer);

        public static int TArray_AddUniqueImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_AddUniqueImplementation(InArray, InValueBuffer);
        }

        private static unsafe partial int __TArray_RemoveSingleImplementation(nint InArray, byte* InValueBuffer);

        public static int TArray_RemoveSingleImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_RemoveSingleImplementation(InArray, InValueBuffer);
        }

        private static unsafe partial int __TArray_RemoveImplementation(nint InArray, byte* InValueBuffer);

        public static int TArray_RemoveImplementation(nint InArray, byte* InValueBuffer)
        {
            return __TArray_RemoveImplementation(InArray, InValueBuffer);
        }

        private static unsafe partial void __TArray_SwapMemoryImplementation(nint InArray, int InFirstIndexToSwap, int InSecondIndexToSwap);

        public static void TArray_SwapMemoryImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap)
        {
            __TArray_SwapMemoryImplementation(InArray, InFirstIndexToSwap, InSecondIndexToSwap);
        }

        private static unsafe partial void __TArray_SwapImplementation(nint InArray, int InFirstIndexToSwap, int InSecondIndexToSwap);

        public static void TArray_SwapImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap)
        {
            __TArray_SwapImplementation(InArray, InFirstIndexToSwap, InSecondIndexToSwap);
        }

        private static unsafe partial int __TArray_INDEX_NONEImplementation();

        public static int TArray_INDEX_NONEImplementation()
        {
            return __TArray_INDEX_NONEImplementation();
        }

        public static T TArray_GetCompoundImplementation<T>(nint InArray, int InIndex)
        {
            var ValueBuffer = stackalloc byte[sizeof(nint)];

            __TArray_GetImplementation(InArray, InIndex, ValueBuffer);

            var Handle = *(nint*)ValueBuffer;

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : default;
        }
    }
}