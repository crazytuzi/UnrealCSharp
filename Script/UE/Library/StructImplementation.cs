using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class StructImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UScriptStruct Struct_StaticStructImplementation(string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_RegisterImplementation(object InMonoObject, string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Struct_IdenticalImplementation(nint InScriptStruct, nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Struct_UnRegisterImplementation(nint InMonoObject);
    }
}