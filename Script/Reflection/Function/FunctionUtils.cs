using System;
using Script.Common;

namespace Script.Reflection.Function
{
    public static class FunctionUtils
    {
        public static void Function_ReflectionMember<T>(Object InMonoObject, string InFunctionName, out T ReturnValue,
            out ObjectList OutValue, params Object[] InValue) =>
            FunctionImplementation.Function_ReflectionMemberImplementation(InMonoObject, InFunctionName,
                out ReturnValue, out OutValue, InValue);

        public static void Function_ReflectionStatic<T>(string InClassName, string InFunctionName, out T ReturnValue,
            out ObjectList OutValue, params Object[] InValue) =>
            FunctionImplementation.Function_ReflectionStaticImplementation(InClassName, InFunctionName, out ReturnValue,
                out OutValue, InValue);
    }
}