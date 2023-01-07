using System;
using Script.Common;
using Script.CoreUObject;

namespace Script.Reflection.Property
{
    public static class PropertyUtils
    {
        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Byte OutValue) =>
            PropertyImplementation.Property_GetObjectBytePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Byte InValue) =>
            PropertyImplementation.Property_SetObjectBytePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, UInt16 InValue) =>
            PropertyImplementation.Property_SetObjectUInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt32PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, UInt32 InValue) =>
            PropertyImplementation.Property_SetObjectUInt32PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, UInt64 InValue) =>
            PropertyImplementation.Property_SetObjectUInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Int16 OutValue) =>
            PropertyImplementation.Property_GetObjectInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Int16 InValue) =>
            PropertyImplementation.Property_SetObjectInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Int32 OutValue) =>
            PropertyImplementation.Property_GetObjectIntPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Int32 InValue) =>
            PropertyImplementation.Property_SetObjectIntPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Int64 OutValue) =>
            PropertyImplementation.Property_GetObjectInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Int64 InValue) =>
            PropertyImplementation.Property_SetObjectInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Boolean OutValue) =>
            PropertyImplementation.Property_GetObjectBoolPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Boolean InValue) =>
            PropertyImplementation.Property_SetObjectBoolPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Single OutValue) =>
            PropertyImplementation.Property_GetObjectFloatPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Single OutValue) =>
            PropertyImplementation.Property_SetObjectFloatPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName, out T OutValue) =>
            PropertyImplementation.Property_GetObjectObjectPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, T OutValue) =>
            PropertyImplementation.Property_SetObjectObjectPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName, out TSubclassOf<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetObjectClassPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TSubclassOf<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetObjectClassPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName,
            out TScriptInterface<T> OutValue)
            where T : IInterface =>
            PropertyImplementation.Property_GetObjectInterfacePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName,
            TScriptInterface<T> OutValue)
            where T : IInterface =>
            PropertyImplementation.Property_SetObjectInterfacePropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName, out TArray<T> OutValue) =>
            PropertyImplementation.Property_GetObjectArrayPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TArray<T> OutValue) =>
            PropertyImplementation.Property_SetObjectArrayPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName,
            out TWeakObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetObjectWeakObjectPropertyImplementation(InMonoObject,
                InPropertyName, out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TWeakObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetObjectWeakObjectPropertyImplementation(InMonoObject,
                InPropertyName, OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName,
            out TLazyObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetObjectLazyObjectPropertyImplementation(InMonoObject,
                InPropertyName, out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TLazyObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetObjectLazyObjectPropertyImplementation(InMonoObject,
                InPropertyName, OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName,
            out TSoftObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetObjectSoftObjectPropertyImplementation(InMonoObject,
                InPropertyName, out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TSoftObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetObjectSoftObjectPropertyImplementation(InMonoObject,
                InPropertyName, OutValue);

        public static void GetObjectProperty(Object InMonoObject, string InPropertyName, out Double OutValue) =>
            PropertyImplementation.Property_GetObjectDoublePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(Object InMonoObject, string InPropertyName, Double OutValue) =>
            PropertyImplementation.Property_SetObjectDoublePropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<TKey, TValue>(Object InMonoObject, string InPropertyName,
            out TMap<TKey, TValue> OutValue) =>
            PropertyImplementation.Property_GetObjectMapPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<TKey, TValue>(Object InMonoObject, string InPropertyName,
            TMap<TKey, TValue> OutValue) =>
            PropertyImplementation.Property_SetObjectMapPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName, out TSet<T> OutValue) =>
            PropertyImplementation.Property_GetObjectSetPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TSet<T> OutValue) =>
            PropertyImplementation.Property_SetObjectSetPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetObjectProperty<T>(Object InMonoObject, string InPropertyName, out TFieldPath<T> OutValue)
            where T : FField =>
            PropertyImplementation.Property_GetObjectFieldPathPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty<T>(Object InMonoObject, string InPropertyName, TFieldPath<T> OutValue)
            where T : FField =>
            PropertyImplementation.Property_SetObjectFieldPathPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Byte OutValue) =>
            PropertyImplementation.Property_GetStructBytePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Byte InValue) =>
            PropertyImplementation.Property_SetStructBytePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetStructUInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, UInt16 InValue) =>
            PropertyImplementation.Property_SetStructUInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetStructUInt32PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, UInt32 InValue) =>
            PropertyImplementation.Property_SetStructUInt32PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetStructUInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, UInt64 InValue) =>
            PropertyImplementation.Property_SetStructUInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Int16 OutValue) =>
            PropertyImplementation.Property_GetStructInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Int16 InValue) =>
            PropertyImplementation.Property_SetStructInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Int32 OutValue) =>
            PropertyImplementation.Property_GetStructIntPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Int32 InValue) =>
            PropertyImplementation.Property_SetStructIntPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Int64 OutValue) =>
            PropertyImplementation.Property_GetStructInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Int64 InValue) =>
            PropertyImplementation.Property_SetStructInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Boolean OutValue) =>
            PropertyImplementation.Property_GetStructBoolPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Boolean InValue) =>
            PropertyImplementation.Property_SetStructBoolPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Single OutValue) =>
            PropertyImplementation.Property_GetStructFloatPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Single OutValue) =>
            PropertyImplementation.Property_SetStructFloatPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName, out T OutValue) =>
            PropertyImplementation.Property_GetStructObjectPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, T OutValue) =>
            PropertyImplementation.Property_SetStructObjectPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName, out TSubclassOf<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetStructClassPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TSubclassOf<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetStructClassPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName,
            out TScriptInterface<T> OutValue)
            where T : IInterface =>
            PropertyImplementation.Property_GetStructInterfacePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName,
            TScriptInterface<T> OutValue)
            where T : IInterface =>
            PropertyImplementation.Property_SetStructInterfacePropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName, out TArray<T> OutValue) =>
            PropertyImplementation.Property_GetStructArrayPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TArray<T> OutValue) =>
            PropertyImplementation.Property_SetStructArrayPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName,
            out TWeakObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetStructWeakObjectPropertyImplementation(InMonoObject,
                InPropertyName, out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TWeakObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetStructWeakObjectPropertyImplementation(InMonoObject,
                InPropertyName, OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName,
            out TLazyObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetStructLazyObjectPropertyImplementation(InMonoObject,
                InPropertyName, out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TLazyObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetStructLazyObjectPropertyImplementation(InMonoObject,
                InPropertyName, OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName,
            out TSoftObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_GetStructSoftObjectPropertyImplementation(InMonoObject,
                InPropertyName, out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TSoftObjectPtr<T> OutValue)
            where T : UObject =>
            PropertyImplementation.Property_SetStructSoftObjectPropertyImplementation(InMonoObject,
                InPropertyName, OutValue);

        public static void GetStructProperty(Object InMonoObject, string InPropertyName, out Double OutValue) =>
            PropertyImplementation.Property_GetStructDoublePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(Object InMonoObject, string InPropertyName, Double OutValue) =>
            PropertyImplementation.Property_SetStructDoublePropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<TKey, TValue>(Object InMonoObject, string InPropertyName,
            out TMap<TKey, TValue> OutValue) =>
            PropertyImplementation.Property_GetStructMapPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<TKey, TValue>(Object InMonoObject, string InPropertyName,
            TMap<TKey, TValue> OutValue) =>
            PropertyImplementation.Property_SetStructMapPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName, out TSet<T> OutValue) =>
            PropertyImplementation.Property_GetStructSetPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TSet<T> OutValue) =>
            PropertyImplementation.Property_SetStructSetPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);

        public static void GetStructProperty<T>(Object InMonoObject, string InPropertyName, out TFieldPath<T> OutValue)
            where T : FField =>
            PropertyImplementation.Property_GetStructFieldPathPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty<T>(Object InMonoObject, string InPropertyName, TFieldPath<T> OutValue)
            where T : FField =>
            PropertyImplementation.Property_SetStructFieldPathPropertyImplementation(InMonoObject, InPropertyName,
                OutValue);
    }
}