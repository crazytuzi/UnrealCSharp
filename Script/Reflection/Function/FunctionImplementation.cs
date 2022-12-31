using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Reflection.Function
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_ReflectionImplementation<T>(Object InMonoObject, string InFunctionName,
            out T ReturnValue, out ObjectList OutValue, params Object[] InValue);
    }
}