using System;
using Script.Common;
using Script.Library;

namespace Script.Reflection.Container
{
    public static class MapUtils
    {
        public static void Map_Register<TKey, TValue>(TMap<TKey, TValue> InMap) =>
            MapImplementation.Map_RegisterImplementation(InMap);

        public static void Map_UnRegister<TKey, TValue>(TMap<TKey, TValue> InMap) =>
            MapImplementation.Map_UnRegisterImplementation(InMap);

        public static void Map_Empty<TKey, TValue>(TMap<TKey, TValue> InMap, Int32 InExpectedNumElements) =>
            MapImplementation.Map_EmptyImplementation(InMap, InExpectedNumElements);

        public static Int32 Map_Num<TKey, TValue>(TMap<TKey, TValue> InMap) =>
            MapImplementation.Map_NumImplementation(InMap);

        public static void Map_Add<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey, TValue InValue) =>
            MapImplementation.Map_AddImplementation(InMap, InKey, InValue);

        public static Int32 Map_Remove<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey) =>
            MapImplementation.Map_RemoveImplementation(InMap, InKey);

        public static TKey Map_FindKey<TKey, TValue>(TMap<TKey, TValue> InMap, TValue InValue)
        {
            MapImplementation.Map_FindKeyImplementation(InMap, InValue, out var OutKey);

            return (TKey) OutKey;
        }

        public static TValue Map_Find<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey)
        {
            MapImplementation.Map_FindImplementation(InMap, InKey, out var OutValue);

            return (TValue) OutValue;
        }

        public static Boolean Map_Contains<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey) =>
            MapImplementation.Map_ContainsImplementation(InMap, InKey);

        public static TValue Map_Get<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey)
        {
            MapImplementation.Map_GetImplementation(InMap, InKey, out var OutValue);

            return (TValue) OutValue;
        }

        public static void Map_Set<TKey, TValue>(TMap<TKey, TValue> InMap, TKey InKey, TValue InValue) =>
            MapImplementation.Map_SetImplementation(InMap, InKey, InValue);
    }
}