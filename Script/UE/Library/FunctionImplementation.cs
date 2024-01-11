using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection0Implementation(IntPtr InMonoObject, UInt32 InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Function_Reflection1Implementation(IntPtr InMonoObject, UInt32 InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection2Implementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Function_Reflection3Implementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection4Implementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            out Object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Function_Reflection5Implementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            out Object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection6Implementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            out Object[] OutValue, params Object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object Function_Reflection7Implementation(IntPtr InMonoObject, UInt32 InFunctionHash,
            out Object[] OutValue, params Object[] InValue);
    }
}