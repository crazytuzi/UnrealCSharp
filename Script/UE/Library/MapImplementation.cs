using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class MapImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_RegisterImplementation<TKey, TValue>(TMap<TKey, TValue> InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_UnRegisterImplementation(IntPtr InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_EmptyImplementation(IntPtr InMap, Int32 InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Map_NumImplementation(IntPtr InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Map_IsEmptyImplementation(IntPtr InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_AddImplementation(IntPtr InMap, Object InKey, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Map_RemoveImplementation(IntPtr InMap, Object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Map_FindKeyImplementation(IntPtr InMap, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Map_FindImplementation(IntPtr InMap, Object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Map_ContainsImplementation(IntPtr InMap, Object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Map_GetImplementation(IntPtr InMap, Object InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_SetImplementation(IntPtr InMap, Object InKey, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Map_GetMaxIndexImplementation(IntPtr InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Map_IsValidIndexImplementation(IntPtr InMap, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Map_GetEnumeratorKeyImplementation(IntPtr InMap, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Map_GetEnumeratorValueImplementation(IntPtr InMap, Int32 InIndex);
    }
}