using System;
using System.Reflection;
using Script.Common;

namespace Script.Reflection.Container
{
    public class ContainerUtils
    {
        static string GetPathName(Type InType) =>
            InType.GetCustomAttribute<PathNameAttribute>(true).PathName;

        public static Object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InParam) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InParam));
    }
}