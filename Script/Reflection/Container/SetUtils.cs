using System;
using Script.Common;

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
    }
}