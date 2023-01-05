using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Reflection.Property
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetBytePropertyImplementation(Object InMonoObject, string InPropertyName,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetBytePropertyImplementation(Object InMonoObject, string InPropertyName,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetUInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetUInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetUInt32PropertyImplementation(Object InMonoObject, string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetUInt32PropertyImplementation(Object InMonoObject, string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetUInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetUInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetIntPropertyImplementation(Object InMonoObject, string InPropertyName,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetIntPropertyImplementation(Object InMonoObject, string InPropertyName,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetBoolPropertyImplementation(Object InMonoObject, string InPropertyName,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetBoolPropertyImplementation(Object InMonoObject, string InPropertyName,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetFloatPropertyImplementation(Object InMonoObject, string InPropertyName,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetFloatPropertyImplementation(Object InMonoObject, string InPropertyName,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetClassPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TSubclassOf<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetClassPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TSubclassOf<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetInterfacePropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TScriptInterface<T> OutValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetInterfacePropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TScriptInterface<T> InValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetArrayPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TArray<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetArrayPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TArray<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetWeakObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TWeakObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetWeakObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TWeakObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetLazyObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TLazyObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetLazyObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TLazyObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetSoftObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TSoftObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetSoftObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TSoftObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetDoublePropertyImplementation(Object InMonoObject, string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetDoublePropertyImplementation(Object InMonoObject, string InPropertyName,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetMapPropertyImplementation<TKey, TValue>(Object InMonoObject, string InPropertyName,
            out TMap<TKey, TValue> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetMapPropertyImplementation<TKey, TValue>(Object InMonoObject, string InPropertyName,
            TMap<TKey, TValue> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetSetPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TSet<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetSetPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TSet<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetFieldPathPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TFieldPath<T> OutValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetFieldPathPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TFieldPath<T> InValue) where T : FField;
    }
}