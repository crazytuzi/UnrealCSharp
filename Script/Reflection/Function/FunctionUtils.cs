using System;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void CallReflectionFunction(Object InMonoObject, string InFunctionName, params Object[] InValue)
        {
            FunctionImplementation.CallReflectionFunctionImplementation(InMonoObject, InFunctionName, InValue);
        }
    }
}