using System;
using System.Reflection;
using System.Diagnostics;
using System.Text;
using System.Collections.Generic;

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

        private static string GetTraceback()
        {
            var Traceback = new StringBuilder();

            var Trace = new StackTrace();

            var Frames = Trace.GetFrames();

            foreach (var Frame in Frames)
            {
                Traceback.Append(String.Format("at {0}.{1} in {2}:{3}\r\n",
                    Frame.GetMethod().DeclaringType.FullName,
                    Frame.GetMethod().Name,
                    Frame.GetFileName(),
                    Frame.GetFileLineNumber()));
            }

            return Traceback.ToString();
        }

        public static Type[] GetTypesWithAttribute(Type InAttributeType, Assembly InAssembly)
        {
            var Types = new List<Type>();

            foreach (var Type in InAssembly.GetTypes())
            {
                if (Type.IsDefined(InAttributeType, false))
                {
                    Types.Add(Type);
                }
            }

            return Types.ToArray();
        }
    }
}