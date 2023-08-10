using System;
using Script.Common;
using Script.Library;
using IntPtr = System.IntPtr;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void Function_Reflection<T>(IntPtr InMonoObject, string InFunctionName, out T ReturnValue,
            out ObjectList OutValue, params Object[] InValue) =>
            FunctionImplementation.Function_ReflectionImplementation(InMonoObject, InFunctionName,
                out ReturnValue, out OutValue, InValue);
    }
}