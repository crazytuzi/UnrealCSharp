using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Reflection.Container
{
    public static class ArrayImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_RegisterImplementation<T>(TArray<T> InArray, Type InType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_UnRegisterImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_GetTypeSizeImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_GetSlackImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Array_IsValidIndexImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_NumImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_MaxImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_GetImplementation<T>(TArray<T> InArray, Int32 InIndex, out Object OutVlue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SetImplementation<T>(TArray<T> InArray, Int32 InIndex, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_FindImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_FindLastImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Array_ContainsImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddUninitializedImplementation<T>(TArray<T> InArray, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_InsertZeroedImplementation<T>(TArray<T> InArray, Int32 InIndex, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_InsertDefaultedImplementation<T>(TArray<T> InArray, Int32 InIndex,
            Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_RemoveAtImplementation<T>(TArray<T> InArray, Int32 InIndex, Int32 InCount,
            Boolean bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_ResetImplementation<T>(TArray<T> InArray, Int32 InNewSize);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_EmptyImplementation<T>(TArray<T> InArray, Int32 InSlack);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SetNumImplementation<T>(TArray<T> InArray, Int32 InNewNum,
            Boolean bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddZeroedImplementation<T>(TArray<T> InArray, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddUniqueImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_RemoveSingleImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_RemoveImplementation<T>(TArray<T> InArray, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_SwapMemoryImplementation<T>(TArray<T> InArray, Int32 InFirstIndexToSwap,
            Int32 InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_SwapImplementation<T>(TArray<T> InArray, Int32 InFirstIndexToSwap,
            Int32 InSecondIndexToSwap);
    }
}