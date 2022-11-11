using System;
using Script.Engine;

namespace Script.Reflection.Container
{
    public class SetUtils
    {
        public static void RegisterSet<T>(TSet<T> InSet, Type InType) =>
            SetImplementation.RegisterSetImplementation(InSet, InType);

        public static void UnRegisterSet<T>(TSet<T> InSet) =>
            SetImplementation.UnRegisterSetImplementation(InSet);

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