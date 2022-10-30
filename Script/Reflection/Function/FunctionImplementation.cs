using System;
using System.Runtime.CompilerServices;

namespace Script.Reflection.Function
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void CallReflectionFunctionImplementation<T>(Object InMonoObject, string InFunctionName,
            out T ReturnValue, out IntPtrList OutValue, params Object[] InValue);
    }
}