using System;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void CallReflectionMemberFunction<T>(Object InMonoObject, string InFunctionName,
            out T ReturnValue, out ObjectList OutValue, params Object[] InValue)
        {
            FunctionImplementation.CallReflectionMemberFunctionImplementation(InMonoObject, InFunctionName,
                out ReturnValue, out OutValue, InValue);
        }

        public static void CallReflectionStaticFunction<T>(string InClassName, string InFunctionName, out T ReturnValue,
            out ObjectList OutValue, params Object[] InValue)
        {
            FunctionImplementation.CallReflectionStaticFunctionImplementation(InClassName, InFunctionName,
                out ReturnValue, out OutValue, InValue);
        }
    }
}