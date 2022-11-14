using System;
using System.Runtime.CompilerServices;
using Script.Engine;

namespace Script.Reflection.Container
{
    public static class SetImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_RegisterImplementation<T>(TSet<T> InSet, Type InType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_UnRegisterImplementation<T>(TSet<T> InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_EmptyImplementation<T>(TSet<T> InSet, Int32 InExpectedNumElements);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_NumImplementation<T>(TSet<T> InSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_AddImplementation<T>(TSet<T> InSet, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_RemoveImplementation<T>(TSet<T> InSet, T InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Set_ContainsImplementation<T>(TSet<T> InSet, T InValue);
    }
}