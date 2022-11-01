using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace Script.Reflection.Property
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetBytePropertyImplementation(object InMonoObject, string InPropertyName,
            out byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBytePropertyImplementation(object InMonoObject, string InPropertyName,
            byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt16PropertyImplementation(object InMonoObject, string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt16PropertyImplementation(object InMonoObject, string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt32PropertyImplementation(object InMonoObject, string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt32PropertyImplementation(object InMonoObject, string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInt16PropertyImplementation(object InMonoObject, string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInt16PropertyImplementation(object InMonoObject, string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetIntPropertyImplementation(object InMonoObject, string InPropertyName,
            out int OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            SetIntPropertyImplementation(object InMonoObject, string InPropertyName, int InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInt64PropertyImplementation(object InMonoObject, string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInt64PropertyImplementation(object InMonoObject, string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetBoolPropertyImplementation(object InMonoObject, string InPropertyName,
            out bool OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBoolPropertyImplementation(object InMonoObject, string InPropertyName,
            bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetFloatPropertyImplementation(object InMonoObject, string InPropertyName,
            out float OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetFloatPropertyImplementation(object InMonoObject, string InPropertyName,
            float InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetObjectPropertyImplementation<T>(object InMonoObject, string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetObjectPropertyImplementation<T>(object InMonoObject, string InPropertyName,
            T InValue);

        // @TODO

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetArrayPropertyImplementation(object InMonoObject, string InPropertyName,
            out List<Object> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetArrayPropertyImplementation(object InMonoObject, string InPropertyName,
            List<Object> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetDoublePropertyImplementation(object InMonoObject, string InPropertyName,
            out double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetDoublePropertyImplementation(object InMonoObject, string InPropertyName,
            double InValue);

        // @TODO
    }
}