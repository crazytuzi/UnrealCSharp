using System;
using System.Runtime.CompilerServices;
using Script.Common;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_ReflectionImplementation<T>(IntPtr InMonoObject, string InFunctionName,
            out T ReturnValue, out ObjectList OutValue, params Object[] InValue);
    }
}