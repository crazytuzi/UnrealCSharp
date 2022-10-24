using System;
using System.Runtime.CompilerServices;

namespace Script.Reflection.Function
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void CallReflectionFunctionImplementation(Object InMonoObject, string InFunctionName,
            params Object[] InValue);
    }
}