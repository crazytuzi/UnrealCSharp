using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class StructImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_StaticStructImplementation(string InStructName, out UScriptStruct OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_RegisterImplementation(Object InMonoObject, string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_UnRegisterImplementation(IntPtr InMonoObject);
    }
}