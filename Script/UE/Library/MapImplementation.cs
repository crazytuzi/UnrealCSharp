using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class MapImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_RegisterImplementation<TKey, TValue>(TMap<TKey, TValue> InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_UnRegisterImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_EmptyImplementation(nint InMap, int InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Map_NumImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Map_IsEmptyImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_AddImplementation(nint InMap, object InKey, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Map_RemoveImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Map_FindKeyImplementation(nint InMap, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Map_FindImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Map_ContainsImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Map_GetImplementation(nint InMap, object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_SetImplementation(nint InMap, object InKey, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Map_GetMaxIndexImplementation(nint InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Map_IsValidIndexImplementation(nint InMap, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Map_GetEnumeratorKeyImplementation(nint InMap, int InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Map_GetEnumeratorValueImplementation(nint InMap, int InIndex);
    }
}