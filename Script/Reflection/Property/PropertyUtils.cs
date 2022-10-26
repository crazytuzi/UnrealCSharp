using System;
using System.Collections.Generic;
using Script.Engine;

namespace Script.Reflection.Property
{
    public static class PropertyUtils
    {
        public static void GetProperty(UObject InMonoObject, string InPropertyName, out byte OutValue)
        {
            PropertyImplementation.GetBytePropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, byte InValue)
        {
            PropertyImplementation.SetBytePropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out UInt16 OutValue)
        {
            PropertyImplementation.GetUInt16PropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, UInt16 InValue)
        {
            PropertyImplementation.SetUInt16PropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out UInt32 OutValue)
        {
            PropertyImplementation.GetUInt32PropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, UInt32 InValue)
        {
            PropertyImplementation.SetUInt32PropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        // @TODO

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out Int16 OutValue)
        {
            PropertyImplementation.GetInt16PropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, Int16 InValue)
        {
            PropertyImplementation.SetInt16PropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out Int32 OutValue)
        {
            PropertyImplementation.GetIntPropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, Int32 InValue)
        {
            PropertyImplementation.SetIntPropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out Int64 OutValue)
        {
            PropertyImplementation.GetInt64PropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, Int64 InValue)
        {
            PropertyImplementation.SetInt64PropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out bool OutValue)
        {
            PropertyImplementation.GetBoolPropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, bool InValue)
        {
            PropertyImplementation.SetBoolPropertyImplementation(InMonoObject, InPropertyName, InValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out float OutValue)
        {
            PropertyImplementation.GetFloatPropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, float OutValue)
        {
            PropertyImplementation.SetFloatPropertyImplementation(InMonoObject, InPropertyName, OutValue);
        }

        public static void GetProperty<T>(UObject InMonoObject, string InPropertyName, out T OutValue)
        {
            PropertyImplementation.GetObjectPropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty<T>(UObject InMonoObject, string InPropertyName, T OutValue)
        {
            PropertyImplementation.SetObjectPropertyImplementation(InMonoObject, InPropertyName, OutValue);
        }

        // @TODO

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out List<Object> OutValue)
        {
            PropertyImplementation.GetArrayPropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, List<Object> OutValue)
        {
            PropertyImplementation.SetArrayPropertyImplementation(InMonoObject, InPropertyName, OutValue);
        }

        public static void GetProperty(UObject InMonoObject, string InPropertyName, out double OutValue)
        {
            PropertyImplementation.GetDoublePropertyImplementation(InMonoObject, InPropertyName, out OutValue);
        }

        public static void SetProperty(UObject InMonoObject, string InPropertyName, double OutValue)
        {
            PropertyImplementation.SetDoublePropertyImplementation(InMonoObject, InPropertyName, OutValue);
        }
    }
}