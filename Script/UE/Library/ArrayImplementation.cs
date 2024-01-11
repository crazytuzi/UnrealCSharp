using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class ArrayImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_RegisterImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Array_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_UnRegisterImplementation(IntPtr InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_GetTypeSizeImplementation(IntPtr InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_GetSlackImplementation(IntPtr InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Array_IsValidIndexImplementation(IntPtr InArray, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_NumImplementation(IntPtr InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Array_IsEmptyImplementation(IntPtr InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_MaxImplementation(IntPtr InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Array_GetImplementation(IntPtr InArray, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SetImplementation(IntPtr InArray, Int32 InIndex, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_FindImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_FindLastImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Array_ContainsImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddUninitializedImplementation(IntPtr InArray, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_InsertZeroedImplementation(IntPtr InArray, Int32 InIndex, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_InsertDefaultedImplementation(IntPtr InArray, Int32 InIndex, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_RemoveAtImplementation(IntPtr InArray, Int32 InIndex, Int32 InCount,
            Boolean bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_ResetImplementation(IntPtr InArray, Int32 InNewSize);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_EmptyImplementation(IntPtr InArray, Int32 InSlack);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SetNumImplementation(IntPtr InArray, Int32 InNewNum, Boolean bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddZeroedImplementation(IntPtr InArray, Int32 InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_AddUniqueImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_RemoveSingleImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_RemoveImplementation(IntPtr InArray, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SwapMemoryImplementation(IntPtr InArray, Int32 InFirstIndexToSwap,
            Int32 InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SwapImplementation(IntPtr InArray, Int32 InFirstIndexToSwap,
            Int32 InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Array_INDEX_NONEImplementation();
    }
}