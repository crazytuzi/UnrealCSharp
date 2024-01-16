using System;
using Script.Common;
using Script.Library;

namespace Script.Reflection.Container
{
    public static class SetUtils
    {
        public static void Set_Register<T>(TSet<T> InSet) =>
            SetImplementation.Set_RegisterImplementation(InSet);

        public static void Set_UnRegister(IntPtr InSet) =>
            SetImplementation.Set_UnRegisterImplementation(InSet);

        public static void Set_Empty(IntPtr InSet, Int32 InExpectedNumElements) =>
            SetImplementation.Set_EmptyImplementation(InSet, InExpectedNumElements);

        public static Int32 Set_Num(IntPtr InSet) =>
            SetImplementation.Set_NumImplementation(InSet);

        public static Int32 Set_GetMaxIndex(IntPtr InSet) =>
            SetImplementation.Set_GetMaxIndexImplementation(InSet);

        public static void Set_Add<T>(IntPtr InSet, T InValue) =>
            SetImplementation.Set_AddImplementation(InSet, InValue);

        public static Int32 Set_Remove<T>(IntPtr InSet, T InValue) =>
            SetImplementation.Set_RemoveImplementation(InSet, InValue);

        public static Boolean Set_Contains<T>(IntPtr InSet, T InValue) =>
            SetImplementation.Set_ContainsImplementation(InSet, InValue);

        public static Boolean Set_IsValidIndex(IntPtr InSet, Int32 InIndex) =>
            SetImplementation.Set_IsValidIndexImplementation(InSet, InIndex);

        public static T Set_GetEnumerator<T>(IntPtr InSet, Int32 Index)
        {
            SetImplementation.Set_GetEnumeratorImplementation<T>(InSet, Index, out var OutValue);

            return (T)OutValue;
        }
    }
}