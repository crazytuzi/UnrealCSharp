using System.Runtime.CompilerServices;
using Script.Engine;

namespace Script.Reflection.Struct
{
    public static class StructImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RegisterStructImplementation(UStruct InStruct, string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UnRegisterStructImplementation(UStruct InStruct);
    }
}