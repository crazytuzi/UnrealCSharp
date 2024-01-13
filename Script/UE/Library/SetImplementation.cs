using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class SetImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_RegisterImplementation<T>(TSet<T> InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_UnRegisterImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_EmptyImplementation(nint InSet, int InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Set_NumImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Set_IsEmptyImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Set_GetMaxIndexImplementation(nint InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_AddImplementation(nint InSet, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Set_RemoveImplementation(nint InSet, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Set_ContainsImplementation(nint InSet, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Set_IsValidIndexImplementation(nint InSet, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Set_GetEnumeratorImplementation(nint InSet, int Index);
    }
}