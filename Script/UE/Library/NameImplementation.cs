using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class NameImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Name_RegisterImplementation(FName InName, String InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Name_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Name_UnRegisterImplementation(IntPtr InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern String Name_ToStringImplementation(IntPtr InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FName Name_NAME_NoneImplementation();
    }
}