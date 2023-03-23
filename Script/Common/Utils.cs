using System;
using System.Reflection;

namespace Script.Common
{
    public static class Utils
    {
        private static Boolean IsOverrideType(Type InType)
        {
            return InType.IsDefined(typeof(IsOverrideAttribute), true);
        }

        private static Boolean IsOverrideMethod(MethodInfo InMethodInfo)
        {
            return InMethodInfo.IsDefined(typeof(IsOverrideAttribute), true);
        }

        public static string GetPathName(Type InType) =>
            InType.GetCustomAttribute<PathNameAttribute>(true).PathName;

        private static Object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InTypeArguments,
            Object[] InParams) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InTypeArguments), InParams);

        private static Object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InTypeArguments) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InTypeArguments));

        private static Type[] GetGenericArguments(Type InType)
        {
            return InType.GetGenericArguments();
        }

        private static Type GetType(Type InType)
        {
            return InType.IsGenericType ? InType.GetGenericTypeDefinition() : InType;
        }

        private static Object MulticastDelegate_GetTarget(System.Delegate InDelegate) => InDelegate.Target;

        private static Boolean MulticastDelegate_Equals(System.Delegate A, System.Delegate B) => A == B;

        private static void SetOut()
        {
            Console.SetOut(Log.Log.Create());
        }
    }
}