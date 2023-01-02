using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Reflection.Property
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetBytePropertyImplementation(Object InMonoObject, string InPropertyName,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBytePropertyImplementation(Object InMonoObject, string InPropertyName,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt32PropertyImplementation(Object InMonoObject, string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt32PropertyImplementation(Object InMonoObject, string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInt16PropertyImplementation(Object InMonoObject, string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetIntPropertyImplementation(Object InMonoObject, string InPropertyName,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetIntPropertyImplementation(Object InMonoObject, string InPropertyName,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInt64PropertyImplementation(Object InMonoObject, string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetBoolPropertyImplementation(Object InMonoObject, string InPropertyName,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBoolPropertyImplementation(Object InMonoObject, string InPropertyName,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetFloatPropertyImplementation(Object InMonoObject, string InPropertyName,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetFloatPropertyImplementation(Object InMonoObject, string InPropertyName,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetClassPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TSubclassOf<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetClassPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TSubclassOf<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInterfacePropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TScriptInterface<T> OutValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInterfacePropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TScriptInterface<T> InValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetArrayPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TArray<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetArrayPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TArray<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetWeakObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TWeakObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetWeakObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TWeakObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetLazyObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TLazyObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetLazyObjectPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TLazyObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetDoublePropertyImplementation(Object InMonoObject, string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetDoublePropertyImplementation(Object InMonoObject, string InPropertyName,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetMapPropertyImplementation<TKey, TValue>(Object InMonoObject, string InPropertyName,
            out TMap<TKey, TValue> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetMapPropertyImplementation<TKey, TValue>(Object InMonoObject, string InPropertyName,
            TMap<TKey, TValue> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetSetPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            out TSet<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetSetPropertyImplementation<T>(Object InMonoObject, string InPropertyName,
            TSet<T> InValue);
    }
}