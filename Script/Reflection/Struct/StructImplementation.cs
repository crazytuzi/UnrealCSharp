using System;
using System.Runtime.CompilerServices;

namespace Script.Reflection.Struct
{
    public static class StructImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_RegisterImplementation(Object InMonoObject, string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_UnRegisterImplementation(Object InMonoObject);
    }
}