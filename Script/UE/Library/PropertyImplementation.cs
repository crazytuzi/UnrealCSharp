using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out SByte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectIntPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectIntPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectBoolPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBoolPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectFloatPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectFloatPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out UInt64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out SByte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructIntPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Int32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructIntPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructBoolPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Boolean OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBoolPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructFloatPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Single OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructFloatPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_GetStructDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            out Double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash,
            Double InValue);
    }
}