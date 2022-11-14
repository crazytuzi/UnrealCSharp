using System;
using System.Runtime.CompilerServices;

namespace Script.Reflection.Function
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_ReflectionMemberImplementation<T>(Object InMonoObject, string InFunctionName,
            out T ReturnValue, out ObjectList OutValue, params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_ReflectionStaticImplementation<T>(string InClassName, string InFunctionName,
            out T ReturnValue, out ObjectList OutValue, params Object[] InValue);
    }
}