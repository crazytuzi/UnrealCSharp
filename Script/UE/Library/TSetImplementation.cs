using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TSetImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSet_RegisterImplementation<T>(TSet<T> InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSet_UnRegisterImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSet_EmptyImplementation(nint InSet, int InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TSet_NumImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSet_IsEmptyImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TSet_GetMaxIndexImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TSet_AddImplementation(nint InSet, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int TSet_RemoveImplementation(nint InSet, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSet_ContainsImplementation(nint InSet, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TSet_IsValidIndexImplementation(nint InSet, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object TSet_GetEnumeratorImplementation(nint InSet, int Index);
    }
}