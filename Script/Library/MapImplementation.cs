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
        public static extern void Map_UnRegisterImplementation<TKey, TValue>(TMap<TKey, TValue> InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_EmptyImplementation<TKey, TValue>(TMap<TKey, TValue> InMap,
            Int32 InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Map_NumImplementation<TKey, TValue>(TMap<TKey, TValue> InMap);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_AddImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey,
            TValue InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Map_RemoveImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_FindKeyImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TValue InValue,
            out Object OutKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_FindImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey,
            out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Map_ContainsImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_GetImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey,
            out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Map_SetImplementation<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey,
            TValue InValue);
    }
}