using System;
using Script.Library;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void Function_Reflection(IntPtr InMonoObject, string InFunctionName, out Object ReturnValue,
            out Object[] OutValue, params Object[] InValue) =>
            FunctionImplementation.Function_ReflectionImplementation(InMonoObject, InFunctionName,
                out ReturnValue, out OutValue, InValue);
    }
}