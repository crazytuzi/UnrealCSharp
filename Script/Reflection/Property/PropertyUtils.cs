using System;
using Script.Common;
using Script.CoreUObject;

namespace Script.Reflection.Property
{
    public static class PropertyUtils
    {
        public static void GetProperty(Object InMonoObject, string InPropertyName, out Byte OutValue) =>
            PropertyImplementation.Property_GetBytePropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Byte InValue) =>
            PropertyImplementation.Property_SetBytePropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetUInt16PropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, UInt16 InValue) =>
            PropertyImplementation.Property_SetUInt16PropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetUInt32PropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, UInt32 InValue) =>
            PropertyImplementation.Property_SetUInt32PropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetUInt64PropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, UInt64 InValue) =>
            PropertyImplementation.Property_SetUInt64PropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out Int16 OutValue) =>
            PropertyImplementation.Property_GetInt16PropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Int16 InValue) =>
            PropertyImplementation.Property_SetInt16PropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out Int32 OutValue) =>
            PropertyImplementation.Property_GetIntPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Int32 InValue) =>
            PropertyImplementation.Property_SetIntPropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out Int64 OutValue) =>
            PropertyImplementation.Property_GetInt64PropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Int64 InValue) =>
            PropertyImplementation.Property_SetInt64PropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out Boolean OutValue) =>
            PropertyImplementation.Property_GetBoolPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Boolean InValue) =>
            PropertyImplementation.Property_SetBoolPropertyImplementation(InMonoObject, InPropertyName, InValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out Single OutValue) =>
            PropertyImplementation.Property_GetFloatPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Single OutValue) =>
            PropertyImplementation.Property_SetFloatPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out T OutValue) =>
            PropertyImplementation.Property_GetObjectPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, T OutValue) =>
            PropertyImplementation.Property_SetObjectPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TSubclassOf<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetClassPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TSubclassOf<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetClassPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TScriptInterface<T> OutValue)
            where T : IInterface =>
            PropertyImplementation.Property_GetInterfacePropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TScriptInterface<T> OutValue)
            where T : IInterface =>
            PropertyImplementation.Property_SetInterfacePropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TArray<T> OutValue) =>
            PropertyImplementation.Property_GetArrayPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TArray<T> OutValue) =>
            PropertyImplementation.Property_SetArrayPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TWeakObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetWeakObjectPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TWeakObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetWeakObjectPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TLazyObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetLazyObjectPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TLazyObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetLazyObjectPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TSoftObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetSoftObjectPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TSoftObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetSoftObjectPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty(Object InMonoObject, string InPropertyName, out Double OutValue) =>
            PropertyImplementation.Property_GetDoublePropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty(Object InMonoObject, string InPropertyName, Double OutValue) =>
            PropertyImplementation.Property_SetDoublePropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<TKey, TValue>(Object InMonoObject, string InPropertyName,
            out TMap<TKey, TValue> OutValue) =>
            PropertyImplementation.Property_GetMapPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<TKey, TValue>(Object InMonoObject, string InPropertyName,
            TMap<TKey, TValue> OutValue) =>
            PropertyImplementation.Property_SetMapPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TSet<T> OutValue) =>
            PropertyImplementation.Property_GetSetPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TSet<T> OutValue) =>
            PropertyImplementation.Property_SetSetPropertyImplementation(InMonoObject, InPropertyName, OutValue);

        public static void GetProperty<T>(Object InMonoObject, string InPropertyName, out TFieldPath<T> OutValue)
            where T : FField =>
            PropertyImplementation.Property_GetFieldPathPropertyImplementation(InMonoObject, InPropertyName, out OutValue);

        public static void SetProperty<T>(Object InMonoObject, string InPropertyName, TFieldPath<T> OutValue)
            where T : FField =>
            PropertyImplementation.Property_SetFieldPathPropertyImplementation(InMonoObject, InPropertyName, OutValue);
    }
}