using System;
using System.Collections.Generic;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void CallReflectionFunction<T>(Object InMonoObject, string InFunctionName, out T ReturnValue,
            out IntPtrList OutValue, params Object[] InValue)
        {
            FunctionImplementation.CallReflectionFunctionImplementation(InMonoObject, InFunctionName, out ReturnValue,
                out OutValue, InValue);
        }
    }
}