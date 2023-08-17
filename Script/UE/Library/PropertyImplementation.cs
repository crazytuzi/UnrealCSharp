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
        public static extern void Property_GetObjectBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt32PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt32PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out SByte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectIntPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectIntPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectBoolPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBoolPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectFloatPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectFloatPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSubclassOf<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSubclassOf<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInterfacePropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TScriptInterface<T> OutValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInterfacePropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TScriptInterface<T> InValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectArrayPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TArray<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectArrayPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TArray<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectWeakObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TWeakObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectWeakObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TWeakObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectLazyObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TLazyObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectLazyObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TLazyObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSoftClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSoftClassPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSoftClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSoftClassPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSoftObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSoftObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSoftObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSoftObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectMapPropertyImplementation<TKey, TValue>(IntPtr InMonoObject,
            string InPropertyName,
            out TMap<TKey, TValue> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectMapPropertyImplementation<TKey, TValue>(IntPtr InMonoObject,
            string InPropertyName,
            TMap<TKey, TValue> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSetPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSet<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSetPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSet<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectFieldPathPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TFieldPath<T> OutValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectFieldPathPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TFieldPath<T> InValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructIntPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructIntPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructBoolPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBoolPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructFloatPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructFloatPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSubclassOf<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSubclassOf<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInterfacePropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TScriptInterface<T> OutValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInterfacePropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TScriptInterface<T> InValue) where T : IInterface;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructArrayPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TArray<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructArrayPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TArray<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructWeakObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TWeakObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructWeakObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TWeakObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructLazyObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TLazyObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructLazyObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TLazyObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSoftClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSoftClassPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSoftClassPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSoftClassPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSoftObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSoftObjectPtr<T> OutValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSoftObjectPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSoftObjectPtr<T> InValue) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructMapPropertyImplementation<TKey, TValue>(IntPtr InMonoObject,
            string InPropertyName,
            out TMap<TKey, TValue> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructMapPropertyImplementation<TKey, TValue>(IntPtr InMonoObject,
            string InPropertyName,
            TMap<TKey, TValue> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSetPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TSet<T> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSetPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TSet<T> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructFieldPathPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            out TFieldPath<T> OutValue) where T : FField;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructFieldPathPropertyImplementation<T>(IntPtr InMonoObject,
            string InPropertyName,
            TFieldPath<T> InValue) where T : FField;
    }
}