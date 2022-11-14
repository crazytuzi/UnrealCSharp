using Script.Engine;

namespace Script.Reflection.Struct
{
    public static class StructUtils
    {
        public static void Struct_Register(UStruct InStruct, string InStructName) =>
            StructImplementation.Struct_RegisterImplementation(InStruct, InStructName);

        public static void Struct_UnRegister(UStruct InStruct) =>
            StructImplementation.Struct_UnRegisterImplementation(InStruct);
    }
}