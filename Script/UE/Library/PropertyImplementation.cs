using System;
using System.Runtime.CompilerServices;

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
        public static extern void Property_GetObjectCompoundPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectCompoundPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Double InValue);

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
        public static extern void Property_GetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out SByte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSBytePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt16PropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Int16 InValue);

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
        public static extern void Property_GetStructCompoundPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructCompoundPropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructDoublePropertyImplementation(IntPtr InMonoObject,
            string InPropertyName,
            Double InValue);
    }
}