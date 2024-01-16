﻿using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_ReflectionImplementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            out Object ReturnValue, out Object[] OutValue, params Object[] InValue);
    }
}