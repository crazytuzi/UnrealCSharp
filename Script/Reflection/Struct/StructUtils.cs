using System;
using Script.Engine;

namespace Script.Reflection.Struct
{
    public static class StructUtils
    {
        public static void RegisterStruct(UStruct InStruct, string InStructName)
        {
            StructImplementation.RegisterStructImplementation(InStruct, InStructName);
        }

        public static void UnRegisterStruct(UStruct InStruct)
        {
            StructImplementation.UnRegisterStructImplementation(InStruct);
        }
    }
}