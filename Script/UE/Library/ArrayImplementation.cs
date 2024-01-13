using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class ArrayImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_RegisterImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Array_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_UnRegisterImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_GetTypeSizeImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_GetSlackImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Array_IsValidIndexImplementation(nint InArray, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_NumImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Array_IsEmptyImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_MaxImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Array_GetImplementation(nint InArray, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SetImplementation(nint InArray, int InIndex, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_FindImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_FindLastImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Array_ContainsImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_AddUninitializedImplementation(nint InArray, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_InsertZeroedImplementation(nint InArray, int InIndex, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_InsertDefaultedImplementation(nint InArray, int InIndex, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_RemoveAtImplementation(nint InArray, int InIndex, int InCount,
            bool bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_ResetImplementation(nint InArray, int InNewSize);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_EmptyImplementation(nint InArray, int InSlack);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SetNumImplementation(nint InArray, int InNewNum, bool bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_AddImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_AddZeroedImplementation(nint InArray, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_AddUniqueImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_RemoveSingleImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_RemoveImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SwapMemoryImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Array_SwapImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Array_INDEX_NONEImplementation();
    }
}