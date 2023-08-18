using System;
using Script.Library;

namespace Script.Reflection.Property
{
    public static class PropertyUtils
    {
        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Byte OutValue) =>
            PropertyImplementation.Property_GetObjectBytePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Byte InValue) =>
            PropertyImplementation.Property_SetObjectBytePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, UInt16 InValue) =>
            PropertyImplementation.Property_SetObjectUInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt32PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, UInt32 InValue) =>
            PropertyImplementation.Property_SetObjectUInt32PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, UInt64 InValue) =>
            PropertyImplementation.Property_SetObjectUInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out SByte OutValue) =>
            PropertyImplementation.Property_GetObjectSBytePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, SByte InValue) =>
            PropertyImplementation.Property_SetObjectSBytePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Int16 OutValue) =>
            PropertyImplementation.Property_GetObjectInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Int16 InValue) =>
            PropertyImplementation.Property_SetObjectInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Int32 OutValue) =>
            PropertyImplementation.Property_GetObjectIntPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Int32 InValue) =>
            PropertyImplementation.Property_SetObjectIntPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Int64 OutValue) =>
            PropertyImplementation.Property_GetObjectInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Int64 InValue) =>
            PropertyImplementation.Property_SetObjectInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Boolean OutValue) =>
            PropertyImplementation.Property_GetObjectBoolPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Boolean InValue) =>
            PropertyImplementation.Property_SetObjectBoolPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Single OutValue) =>
            PropertyImplementation.Property_GetObjectFloatPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Single InValue) =>
            PropertyImplementation.Property_SetObjectFloatPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Object OutValue) =>
            PropertyImplementation.Property_GetObjectCompoundPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Object InValue) =>
            PropertyImplementation.Property_SetObjectCompoundPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, string InPropertyName, out Double OutValue) =>
            PropertyImplementation.Property_GetObjectDoublePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, string InPropertyName, Double InValue) =>
            PropertyImplementation.Property_SetObjectDoublePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Byte OutValue) =>
            PropertyImplementation.Property_GetStructBytePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Byte InValue) =>
            PropertyImplementation.Property_SetStructBytePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetStructUInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, UInt16 InValue) =>
            PropertyImplementation.Property_SetStructUInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetStructUInt32PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, UInt32 InValue) =>
            PropertyImplementation.Property_SetStructUInt32PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetStructUInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, UInt64 InValue) =>
            PropertyImplementation.Property_SetStructUInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out SByte OutValue) =>
            PropertyImplementation.Property_GetStructSBytePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, SByte InValue) =>
            PropertyImplementation.Property_SetStructSBytePropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Int16 OutValue) =>
            PropertyImplementation.Property_GetStructInt16PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Int16 InValue) =>
            PropertyImplementation.Property_SetStructInt16PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Int32 OutValue) =>
            PropertyImplementation.Property_GetStructIntPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Int32 InValue) =>
            PropertyImplementation.Property_SetStructIntPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Int64 OutValue) =>
            PropertyImplementation.Property_GetStructInt64PropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Int64 InValue) =>
            PropertyImplementation.Property_SetStructInt64PropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Boolean OutValue) =>
            PropertyImplementation.Property_GetStructBoolPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Boolean InValue) =>
            PropertyImplementation.Property_SetStructBoolPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Single OutValue) =>
            PropertyImplementation.Property_GetStructFloatPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Single InValue) =>
            PropertyImplementation.Property_SetStructFloatPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Object OutValue) =>
            PropertyImplementation.Property_GetStructCompoundPropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Object InValue) =>
            PropertyImplementation.Property_SetStructCompoundPropertyImplementation(InMonoObject, InPropertyName,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, string InPropertyName, out Double OutValue) =>
            PropertyImplementation.Property_GetStructDoublePropertyImplementation(InMonoObject, InPropertyName,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, string InPropertyName, Double InValue) =>
            PropertyImplementation.Property_SetStructDoublePropertyImplementation(InMonoObject, InPropertyName,
                InValue);
    }
}