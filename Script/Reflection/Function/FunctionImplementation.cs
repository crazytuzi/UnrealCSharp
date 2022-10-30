using System;
using System.Runtime.CompilerServices;

namespace Script.Reflection.Function
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void CallReflectionMemberFunctionImplementation<T>(Object InMonoObject,
            string InFunctionName, out T ReturnValue, out IntPtrList OutValue, params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void CallReflectionStaticFunctionImplementation<T>(string InClassName,
            string InFunctionName, out T ReturnValue, out IntPtrList OutValue, params Object[] InValue);
    }
}