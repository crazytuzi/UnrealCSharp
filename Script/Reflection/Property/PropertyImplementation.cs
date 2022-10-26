using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Script.Engine;

namespace Script.Reflection.Property
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetBytePropertyImplementation(UObject InMonoObject, string InPropertyName,
            out byte OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBytePropertyImplementation(UObject InMonoObject, string InPropertyName,
            byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt16PropertyImplementation(UObject InMonoObject, string InPropertyName,
            out UInt16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt16PropertyImplementation(UObject InMonoObject, string InPropertyName,
            UInt16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetUInt32PropertyImplementation(UObject InMonoObject, string InPropertyName,
            UInt32 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetUInt32PropertyImplementation(UObject InMonoObject, string InPropertyName,
            out UInt32 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInt16PropertyImplementation(UObject InMonoObject, string InPropertyName,
            Int16 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInt16PropertyImplementation(UObject InMonoObject, string InPropertyName,
            out Int16 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetIntPropertyImplementation(UObject InMonoObject, string InPropertyName,
            out int OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            SetIntPropertyImplementation(UObject InMonoObject, string InPropertyName, int InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetInt64PropertyImplementation(UObject InMonoObject, string InPropertyName,
            out Int64 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetInt64PropertyImplementation(UObject InMonoObject, string InPropertyName,
            Int64 InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetBoolPropertyImplementation(UObject InMonoObject, string InPropertyName,
            out bool OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBoolPropertyImplementation(UObject InMonoObject, string InPropertyName,
            bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetFloatPropertyImplementation(UObject InMonoObject, string InPropertyName,
            out float OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetFloatPropertyImplementation(UObject InMonoObject, string InPropertyName,
            float InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetObjectPropertyImplementation<T>(UObject InMonoObject, string InPropertyName,
            out T OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetObjectPropertyImplementation<T>(UObject InMonoObject, string InPropertyName,
            T InValue);

        // @TODO

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetArrayPropertyImplementation(UObject InMonoObject, string InPropertyName,
            out List<Object> OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetArrayPropertyImplementation(UObject InMonoObject, string InPropertyName,
            List<Object> InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void GetDoublePropertyImplementation(UObject InMonoObject, string InPropertyName,
            out double OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetDoublePropertyImplementation(UObject InMonoObject, string InPropertyName,
            double InValue);

        // @TODO
    }
}