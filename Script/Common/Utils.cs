using System;
using System.Reflection;

namespace Script.Common
{
    public class Utils
    {
        static Boolean IsOverrideType(Type InType)
        {
            var IsOverride = InType.GetCustomAttribute<IsOverrideAttribute>(true);

            return IsOverride != null && IsOverride.IsOverride;
        }
        
        static Boolean IsOverrideMethod(MethodInfo InMethodInfo)
        {
            var IsOverride = InMethodInfo.GetCustomAttribute<IsOverrideAttribute>(true);

            return IsOverride != null && IsOverride.IsOverride;
        }
    }
}