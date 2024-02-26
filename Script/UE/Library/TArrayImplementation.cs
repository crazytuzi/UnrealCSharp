using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TArrayImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_RegisterImplementation<T>(TArray<T> InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TArray_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_UnRegisterImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_GetTypeSizeImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_GetSlackImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TArray_IsValidIndexImplementation(nint InArray, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_NumImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TArray_IsEmptyImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_MaxImplementation(nint InArray);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TArray_GetImplementation(nint InArray, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_SetImplementation(nint InArray, int InIndex, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_FindImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_FindLastImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TArray_ContainsImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_AddUninitializedImplementation(nint InArray, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_InsertZeroedImplementation(nint InArray, int InIndex, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_InsertDefaultedImplementation(nint InArray, int InIndex, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_RemoveAtImplementation(nint InArray, int InIndex, int InCount,
            bool bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_ResetImplementation(nint InArray, int InNewSize);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_EmptyImplementation(nint InArray, int InSlack);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_SetNumImplementation(nint InArray, int InNewNum, bool bAllowShrinking);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_AddImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_AddZeroedImplementation(nint InArray, int InCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_AddUniqueImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_RemoveSingleImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_RemoveImplementation(nint InArray, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_SwapMemoryImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TArray_SwapImplementation(nint InArray, int InFirstIndexToSwap,
            int InSecondIndexToSwap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TArray_INDEX_NONEImplementation();
    }
}