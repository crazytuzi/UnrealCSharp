﻿using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class SetImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_RegisterImplementation<T>(TSet<T> InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_UnRegisterImplementation(IntPtr InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_EmptyImplementation(IntPtr InSet, Int32 InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_NumImplementation(IntPtr InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_GetMaxIndexImplementation(IntPtr InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_AddImplementation(IntPtr InSet, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_RemoveImplementation(IntPtr InSet, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Set_ContainsImplementation(IntPtr InSet, Object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Set_IsValidIndexImplementation(IntPtr InSet, Int32 InIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Set_GetEnumeratorImplementation<T>(IntPtr InSet, Int32 Index, out Object OutValue);
    }
}