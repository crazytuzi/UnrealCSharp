using System;
using Script.Common;
using Script.Library;

namespace Script.Reflection.Container
{
    public static class MapUtils
    {
        public static void Map_Register<TKey, TValue>(TMap<TKey, TValue> InMap) =>
            MapImplementation.Map_RegisterImplementation(InMap);

        public static void Map_UnRegister(IntPtr InMap) =>
            MapImplementation.Map_UnRegisterImplementation(InMap);

        public static void Map_Empty(IntPtr InMap, Int32 InExpectedNumElements) =>
            MapImplementation.Map_EmptyImplementation(InMap, InExpectedNumElements);

        public static Int32 Map_Num(IntPtr InMap) =>
            MapImplementation.Map_NumImplementation(InMap);

        public static void Map_Add<TKey, TValue>(IntPtr InMap, TKey InKey, TValue InValue) =>
            MapImplementation.Map_AddImplementation(InMap, InKey, InValue);

        public static Int32 Map_Remove<TKey, TValue>(IntPtr InMap, TKey InKey) =>
            MapImplementation.Map_RemoveImplementation(InMap, InKey);

        public static TKey Map_FindKey<TKey, TValue>(IntPtr InMap, TValue InValue)
        {
            MapImplementation.Map_FindKeyImplementation(InMap, InValue, out var OutKey);

            return (TKey)OutKey;
        }

        public static TValue Map_Find<TKey, TValue>(IntPtr InMap, TKey InKey)
        {
            MapImplementation.Map_FindImplementation(InMap, InKey, out var OutValue);

            return (TValue)OutValue;
        }

        public static Boolean Map_Contains<TKey, TValue>(IntPtr InMap, TKey InKey) =>
            MapImplementation.Map_ContainsImplementation(InMap, InKey);

        public static TValue Map_Get<TKey, TValue>(IntPtr InMap, TKey InKey)
        {
            MapImplementation.Map_GetImplementation(InMap, InKey, out var OutValue);

            return (TValue)OutValue;
        }

        public static void Map_Set<TKey, TValue>(IntPtr InMap, TKey InKey, TValue InValue) =>
            MapImplementation.Map_SetImplementation(InMap, InKey, InValue);

        public static Int32 Map_GetMaxIndex(IntPtr InMap) =>
            MapImplementation.Map_GetMaxIndexImplementation(InMap);

        public static Boolean Map_IsValidIndex(IntPtr InMap, Int32 InIndex) =>
            MapImplementation.Map_IsValidIndexImplementation(InMap, InIndex);

        public static TKey Map_GetEnumeratorKey<TKey, TValue>(IntPtr InMap, Int32 InIndex)
        {
            MapImplementation.Map_GetEnumeratorKeyImplementation(InMap, InIndex, out var OutKey);

            return (TKey)OutKey;
        }

        public static TValue Map_GetEnumeratorValue<TKey, TValue>(IntPtr InMap, Int32 InIndex)
        {
            MapImplementation.Map_GetEnumeratorValueImplementation(InMap, InIndex, out var OutValue);

            return (TValue)OutValue;
        }
    }
}