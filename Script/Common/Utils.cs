using System;
using System.Reflection;

namespace Script.Common
{
    public class Utils
    {
        static Boolean IsOverrideType(Type InType)
        {
            return InType.IsDefined(typeof(IsOverrideAttribute), true);
        }
        
        static Boolean IsOverrideMethod(MethodInfo InMethodInfo)
        {
            return InMethodInfo.IsDefined(typeof(IsOverrideAttribute), true);
        }
        
        static string GetPathName(Type InType) =>
            InType.GetCustomAttribute<PathNameAttribute>(true).PathName;

        public static Object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InParam) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InParam));
    }
}