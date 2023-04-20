using System;
using Script.Common;
using Script.Library;

namespace Script.Reflection.Container
{
    public static class SetUtils
    {
        public static void Set_Register<T>(TSet<T> InSet) =>
            SetImplementation.Set_RegisterImplementation(InSet);

        public static void Set_UnRegister<T>(TSet<T> InSet) =>
            SetImplementation.Set_UnRegisterImplementation(InSet);

        public static void Set_Empty<T>(TSet<T> InSet, Int32 InExpectedNumElements) =>
            SetImplementation.Set_EmptyImplementation(InSet, InExpectedNumElements);

        public static Int32 Set_Num<T>(TSet<T> InSet) =>
            SetImplementation.Set_NumImplementation(InSet);

        public static void Set_Add<T>(TSet<T> InSet, T InValue) =>
            SetImplementation.Set_AddImplementation(InSet, InValue);

        public static Int32 Set_Remove<T>(TSet<T> InSet, T InValue) =>
            SetImplementation.Set_RemoveImplementation(InSet, InValue);

        public static Boolean Set_Contains<T>(TSet<T> InSet, T InValue) =>
            SetImplementation.Set_ContainsImplementation(InSet, InValue);

        public static Boolean Set_IsValidIndex<T>(TSet<T> InSet, Int32 InIndex) =>
            SetImplementation.Set_IsValidIndexImplementation(InSet, InIndex);

        public static T Set_GetEnumerator<T>(TSet<T> InSet, Int32 Index)
        {
            SetImplementation.Set_GetEnumeratorImplementation(InSet, Index, out var OutValue);

            return (T) OutValue;
        }
        
        public static void Set_SetEnumerator<T>(TSet<T> InSet, Int32 InIndex,T value) =>
            SetImplementation.Set_SetEnumeratorImplementation(InSet, InIndex,value);
        
        public static Int32 Set_GetMaxIndex<T>(TSet<T> InSet) =>
            SetImplementation.Set_GetMaxIndexImplementation(InSet);
    }
}