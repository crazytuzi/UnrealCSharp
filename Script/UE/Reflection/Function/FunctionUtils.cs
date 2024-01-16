using System;
using Script.Library;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void Function_Reflection(IntPtr InMonoObject, UInt32 InFunctionHash, out Object ReturnValue,
            out Object[] OutValue, params Object[] InValue) =>
            FunctionImplementation.Function_ReflectionImplementation(InMonoObject, InFunctionHash,
                out ReturnValue, out OutValue, InValue);
    }
}