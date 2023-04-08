using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class SetImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Set_RegisterImplementation<T>(TSet<T> InSet);

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
        
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_FindImplementation<T>(TSet<T>InSet,T Value);
        
        //     [MethodImpl(MethodImplOptions.InternalCall)]   
        // static TArray<FProperty*> Set_ToArrayImplementation(const MonoObject* InMonoObject);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_GetMaxIndexImplementation<T>(TSet<T>InSet);
        
        //[MethodImpl(MethodImplOptions.InternalCall)]
        // static TSet<void*> Set_UnionImplementation(const MonoObject* InMonoObject,TSet<void*> OtherSet);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Set_GetImplementation<T>(TSet<T>InSet, Int32 Index,out Object OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Set_SetImplementation<T>(TSet<T>InSet,Int32 Index,T Value);
        
    }
}