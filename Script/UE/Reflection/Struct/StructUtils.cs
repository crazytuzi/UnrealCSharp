using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Reflection.Struct
{
    public static class StructUtils
    {
        public static void Struct_StaticStruct(String InStructName, out UScriptStruct OutValue) =>
            StructImplementation.Struct_StaticStructImplementation(InStructName, out OutValue);

        public static void Struct_Register(Object InMonoObject, String InStructName) =>
            StructImplementation.Struct_RegisterImplementation(InMonoObject, InStructName);

        public static Boolean Struct_Identical(IntPtr InScriptStruct, IntPtr InA, IntPtr InB) =>
            StructImplementation.Struct_IdenticalImplementation(InScriptStruct, InA, InB);

        public static void Struct_UnRegister(IntPtr InMonoObject) =>
            StructImplementation.Struct_UnRegisterImplementation(InMonoObject);
    }
}