using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using Script.Reflection.Property;

namespace Script.Library
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectBytePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBytePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt32PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt32PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSBytePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSBytePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out SByte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectIntPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectIntPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectBoolPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBoolPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectFloatPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectFloatPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSubclassOf<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSubclassOf<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInterfacePropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TScriptInterface<T> OutValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInterfacePropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TScriptInterface<T> InValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectArrayPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TArray<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectArrayPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TArray<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectWeakObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TWeakObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectWeakObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TWeakObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectLazyObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TLazyObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectLazyObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TLazyObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSoftClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSoftClassPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSoftClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSoftClassPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSoftObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSoftObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSoftObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSoftObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectDoublePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectDoublePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectMapPropertyImplementation<TKey, TValue>(Object InMonoObject,
            string InPropertyName,
            out TMap<TKey, TValue> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectMapPropertyImplementation<TKey, TValue>(Object InMonoObject,
            string InPropertyName,
            TMap<TKey, TValue> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSetPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSet<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSetPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSet<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectFieldPathPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TFieldPath<T> OutValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectFieldPathPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TFieldPath<T> InValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructBytePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBytePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt32PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt32PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt16PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructIntPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructIntPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt64PropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructBoolPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBoolPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructFloatPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructFloatPropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSubclassOf<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSubclassOf<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInterfacePropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TScriptInterface<T> OutValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInterfacePropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TScriptInterface<T> InValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructArrayPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TArray<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructArrayPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TArray<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructWeakObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TWeakObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructWeakObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TWeakObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructLazyObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TLazyObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructLazyObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TLazyObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSoftClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSoftClassPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSoftClassPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSoftClassPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSoftObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSoftObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSoftObjectPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSoftObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructDoublePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructDoublePropertyImplementation(Object InMonoObject,
            string InPropertyName,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructMapPropertyImplementation<TKey, TValue>(Object InMonoObject,
            string InPropertyName,
            out TMap<TKey, TValue> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructMapPropertyImplementation<TKey, TValue>(Object InMonoObject,
            string InPropertyName,
            TMap<TKey, TValue> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSetPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TSet<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSetPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TSet<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructFieldPathPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            out TFieldPath<T> OutValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructFieldPathPropertyImplementation<T>(Object InMonoObject,
            string InPropertyName,
            TFieldPath<T> InValue) where T : FField;
    }
}