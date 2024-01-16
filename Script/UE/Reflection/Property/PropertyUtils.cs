using System;
using Script.Library;

namespace Script.Reflection.Property
{
    public static class PropertyUtils
    {
        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Byte OutValue) =>
            PropertyImplementation.Property_GetObjectBytePropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Byte InValue) =>
            PropertyImplementation.Property_SetObjectBytePropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt16PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, UInt16 InValue) =>
            PropertyImplementation.Property_SetObjectUInt16PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt32PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, UInt32 InValue) =>
            PropertyImplementation.Property_SetObjectUInt32PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetObjectUInt64PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, UInt64 InValue) =>
            PropertyImplementation.Property_SetObjectUInt64PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out SByte OutValue) =>
            PropertyImplementation.Property_GetObjectSBytePropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, SByte InValue) =>
            PropertyImplementation.Property_SetObjectSBytePropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Int16 OutValue) =>
            PropertyImplementation.Property_GetObjectInt16PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Int16 InValue) =>
            PropertyImplementation.Property_SetObjectInt16PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Int32 OutValue) =>
            PropertyImplementation.Property_GetObjectIntPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Int32 InValue) =>
            PropertyImplementation.Property_SetObjectIntPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Int64 OutValue) =>
            PropertyImplementation.Property_GetObjectInt64PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Int64 InValue) =>
            PropertyImplementation.Property_SetObjectInt64PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Boolean OutValue) =>
            PropertyImplementation.Property_GetObjectBoolPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Boolean InValue) =>
            PropertyImplementation.Property_SetObjectBoolPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Single OutValue) =>
            PropertyImplementation.Property_GetObjectFloatPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Single InValue) =>
            PropertyImplementation.Property_SetObjectFloatPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Object OutValue) =>
            PropertyImplementation.Property_GetObjectCompoundPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Object InValue) =>
            PropertyImplementation.Property_SetObjectCompoundPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Double OutValue) =>
            PropertyImplementation.Property_GetObjectDoublePropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetObjectProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Double InValue) =>
            PropertyImplementation.Property_SetObjectDoublePropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Byte OutValue) =>
            PropertyImplementation.Property_GetStructBytePropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Byte InValue) =>
            PropertyImplementation.Property_SetStructBytePropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out UInt16 OutValue) =>
            PropertyImplementation.Property_GetStructUInt16PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, UInt16 InValue) =>
            PropertyImplementation.Property_SetStructUInt16PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out UInt32 OutValue) =>
            PropertyImplementation.Property_GetStructUInt32PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, UInt32 InValue) =>
            PropertyImplementation.Property_SetStructUInt32PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out UInt64 OutValue) =>
            PropertyImplementation.Property_GetStructUInt64PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, UInt64 InValue) =>
            PropertyImplementation.Property_SetStructUInt64PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out SByte OutValue) =>
            PropertyImplementation.Property_GetStructSBytePropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, SByte InValue) =>
            PropertyImplementation.Property_SetStructSBytePropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Int16 OutValue) =>
            PropertyImplementation.Property_GetStructInt16PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Int16 InValue) =>
            PropertyImplementation.Property_SetStructInt16PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Int32 OutValue) =>
            PropertyImplementation.Property_GetStructIntPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Int32 InValue) =>
            PropertyImplementation.Property_SetStructIntPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Int64 OutValue) =>
            PropertyImplementation.Property_GetStructInt64PropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Int64 InValue) =>
            PropertyImplementation.Property_SetStructInt64PropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Boolean OutValue) =>
            PropertyImplementation.Property_GetStructBoolPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Boolean InValue) =>
            PropertyImplementation.Property_SetStructBoolPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Single OutValue) =>
            PropertyImplementation.Property_GetStructFloatPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Single InValue) =>
            PropertyImplementation.Property_SetStructFloatPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Object OutValue) =>
            PropertyImplementation.Property_GetStructCompoundPropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Object InValue) =>
            PropertyImplementation.Property_SetStructCompoundPropertyImplementation(InMonoObject, InPropertyHash,
                InValue);

        public static void GetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, out Double OutValue) =>
            PropertyImplementation.Property_GetStructDoublePropertyImplementation(InMonoObject, InPropertyHash,
                out OutValue);

        public static void SetStructProperty(IntPtr InMonoObject, UInt32 InPropertyHash, Double InValue) =>
            PropertyImplementation.Property_SetStructDoublePropertyImplementation(InMonoObject, InPropertyHash,
                InValue);
    }
}