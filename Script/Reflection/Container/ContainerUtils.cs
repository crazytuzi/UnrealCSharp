using System;
using System.Reflection;
using Script.Engine;

namespace Script.Reflection.Container
{
    public class ContainerUtils
    {
        static string GetPathName(Type InType)
        {
            return InType.GetCustomAttribute<PathNameAttribute>(true).PathName;
        }
    }
}