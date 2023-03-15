using System;
using System.Reflection;

namespace Script.Common
{
    public static class Utils
    {
        static Boolean IsOverrideType(Type InType)
        {
            return InType.IsDefined(typeof(IsOverrideAttribute), true);
        }

        static Boolean IsOverrideMethod(MethodInfo InMethodInfo)
        {
            return InMethodInfo.IsDefined(typeof(IsOverrideAttribute), true);
        }
        
        public static string GetPathName(Type InType) =>
            InType.GetCustomAttribute<PathNameAttribute>(true).PathName;

        public static Object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InTypeArguments,
            Object[] InParams) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InTypeArguments), InParams);

        public static Object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InTypeArguments) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InTypeArguments));

        public static Type[] GetGenericArguments(Type InType)
        {
            return InType.GetGenericArguments();
        }
        
        public static Boolean IsSubclassOf(Type A, Type B)
        {
            return A.IsGenericType ? A.GetGenericTypeDefinition() == B : A.IsSubclassOf(B);
        }
    }
}