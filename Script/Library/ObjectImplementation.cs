using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Binding
{
    public static class ObjectImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_StaticClassImplementation(string InClassName, out UClass OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_GetClassImplementation(UObject InObject, out UClass OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Object_GetNameImplementation(UObject InObject, out FString OutValue);
    }
}