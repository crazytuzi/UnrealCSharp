using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class FunctionImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection0Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Function_Reflection1Implementation(nint InMonoObject, uint InFunctionHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection2Implementation(nint InMonoObject, uint InFunctionHash,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Function_Reflection3Implementation(nint InMonoObject, uint InFunctionHash,
            params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection4Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Function_Reflection5Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Function_Reflection6Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, params object[] InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Function_Reflection7Implementation(nint InMonoObject, uint InFunctionHash,
            out object[] OutValue, params object[] InValue);
    }
}