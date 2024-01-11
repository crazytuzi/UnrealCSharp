using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Byte Property_GetObjectBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt16 Property_GetObjectUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Property_GetObjectUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt64 Property_GetObjectUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern SByte Property_GetObjectSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int16 Property_GetObjectInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Property_GetObjectInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 Property_GetObjectInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Property_GetObjectBooleanPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBooleanPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Property_GetObjectSinglePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSinglePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Property_GetObjectCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Property_GetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Byte Property_GetStructBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt16 Property_GetStructUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Property_GetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt64 Property_GetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, UInt64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern SByte Property_GetStructSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSBytePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, SByte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int16 Property_GetStructInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt16PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Property_GetStructInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt32PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Int32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 Property_GetStructInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt64PropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Property_GetStructBooleanPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBooleanPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Boolean InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Property_GetStructSinglePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSinglePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Single InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Property_GetStructCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructCompoundPropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Property_GetStructDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructDoublePropertyImplementation(IntPtr InMonoObject,
            UInt32 InPropertyHash, Double InValue);
    }
}