using System;
using Script.Common;
using Script.Library;

namespace Script.Reflection.Container
{
    public static class ArrayUtils
    {
        public static void Array_Register<T>(TArray<T> InArray) =>
            ArrayImplementation.Array_RegisterImplementation(InArray);

        public static void Array_UnRegister(IntPtr InArray) =>
            ArrayImplementation.Array_UnRegisterImplementation(InArray);

        public static Int32 Array_GetTypeSize(IntPtr InArray) =>
            ArrayImplementation.Array_GetTypeSizeImplementation(InArray);

        public static Int32 Array_GetSlack(IntPtr InArray) =>
            ArrayImplementation.Array_GetSlackImplementation(InArray);

        public static Boolean Array_IsValidIndex(IntPtr InArray) =>
            ArrayImplementation.Array_IsValidIndexImplementation(InArray);

        public static Int32 Array_Num(IntPtr InArray) =>
            ArrayImplementation.Array_NumImplementation(InArray);

        public static Int32 Array_Max(IntPtr InArray) =>
            ArrayImplementation.Array_MaxImplementation(InArray);

        public static T Array_Get<T>(IntPtr InArray, Int32 InIndex)
        {
            ArrayImplementation.Array_GetImplementation(InArray, InIndex, out var OutValue);

            return (T)OutValue;
        }

        public static void Array_Set<T>(IntPtr InArray, Int32 InIndex, T InValue) =>
            ArrayImplementation.Array_SetImplementation(InArray, InIndex, InValue);

        public static Int32 Array_Find<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_FindImplementation(InArray, InValue);

        public static Int32 Array_FindLast<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_FindLastImplementation(InArray, InValue);

        public static Boolean Array_Contains<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_ContainsImplementation(InArray, InValue);

        public static Int32 Array_AddUninitialized(IntPtr InArray, Int32 InCount) =>
            ArrayImplementation.Array_AddUninitializedImplementation(InArray, InCount);

        public static void Array_InsertZeroed(IntPtr InArray, Int32 InIndex, Int32 InCount) =>
            ArrayImplementation.Array_InsertZeroedImplementation(InArray, InIndex, InCount);

        public static void Array_InsertDefaulted(IntPtr InArray, Int32 InIndex, Int32 InCount) =>
            ArrayImplementation.Array_InsertDefaultedImplementation(InArray, InIndex, InCount);

        public static void
            Array_RemoveAt(IntPtr InArray, Int32 InIndex, Int32 InCount, Boolean bAllowShrinking) =>
            ArrayImplementation.Array_RemoveAtImplementation(InArray, InIndex, InCount, bAllowShrinking);

        public static void Array_Reset(IntPtr InArray, Int32 InNewSize) =>
            ArrayImplementation.Array_ResetImplementation(InArray, InNewSize);

        public static void Array_Empty(IntPtr InArray, Int32 InSlack) =>
            ArrayImplementation.Array_EmptyImplementation(InArray, InSlack);

        public static void Array_SetNum(IntPtr InArray, Int32 InNewNum, Boolean bAllowShrinking) =>
            ArrayImplementation.Array_SetNumImplementation(InArray, InNewNum, bAllowShrinking);

        public static Int32 Array_Add<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_AddImplementation(InArray, InValue);

        public static Int32 Array_AddZeroed(IntPtr InArray, Int32 InCount) =>
            ArrayImplementation.Array_AddZeroedImplementation(InArray, InCount);

        public static Int32 Array_AddUnique<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_AddUniqueImplementation(InArray, InValue);

        public static Int32 Array_RemoveSingle<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_RemoveSingleImplementation(InArray, InValue);

        public static Int32 Array_Remove<T>(IntPtr InArray, T InValue) =>
            ArrayImplementation.Array_RemoveImplementation(InArray, InValue);

        public static void Array_SwapMemory(IntPtr InArray, Int32 InFirstIndexToSwap,
            Int32 InSecondIndexToSwap) =>
            ArrayImplementation.Array_SwapMemoryImplementation(InArray, InFirstIndexToSwap, InSecondIndexToSwap);

        public static void Array_Swap(IntPtr InArray, Int32 InFirstIndexToSwap, Int32 InSecondIndexToSwap) =>
            ArrayImplementation.Array_SwapImplementation(InArray, InFirstIndexToSwap, InSecondIndexToSwap);
    }
}