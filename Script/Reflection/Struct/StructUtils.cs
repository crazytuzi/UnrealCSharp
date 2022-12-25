using System;

namespace Script.Reflection.Struct
{
    public static class StructUtils
    {
        public static void Struct_Register(Object InMonoObject, string InStructName) =>
            StructImplementation.Struct_RegisterImplementation(InMonoObject, InStructName);

        public static void Struct_UnRegister(Object InMonoObject) =>
            StructImplementation.Struct_UnRegisterImplementation(InMonoObject);
    }
}