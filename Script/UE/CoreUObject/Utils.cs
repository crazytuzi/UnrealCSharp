using System;
using System.Reflection;
using System.Diagnostics;
using System.Text;
using System.Collections.Generic;

namespace Script.CoreUObject
{
    public static class Utils
    {
        private static bool IsOverrideType(Type InType) => InType.IsDefined(typeof(OverrideAttribute), true);

        private static bool IsOverrideMethod(MethodInfo InMethodInfo) =>
            InMethodInfo.IsDefined(typeof(OverrideAttribute), true);

        public static string GetPathName(Type InType) => InType.GetCustomAttribute<PathNameAttribute>(true)?.PathName;

        private static object MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InTypeArguments) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InTypeArguments));

        private static Type[] GetGenericArguments(Type InType) => InType.GetGenericArguments();

        private static Type GetType(Type InType) =>
            InType.IsByRef
                ? InType.GetElementType()!.IsGenericType
                    ? InType.GetElementType()?.GetGenericTypeDefinition()
                    : InType.GetElementType()
                : InType.IsGenericType
                    ? InType.GetGenericTypeDefinition()
                    : InType;

        private static object MulticastDelegate_GetTarget(Delegate InDelegate) => InDelegate.Target;

        private static bool MulticastDelegate_Equals(Delegate A, Delegate B) => A == B;

        private static void SetOut() => Console.SetOut(Log.Log.Create());

        private static string GetTraceback()
        {
            var Traceback = new StringBuilder();

            var Trace = new StackTrace();

            var Frames = Trace.GetFrames();

            foreach (var Frame in Frames)
            {
                Traceback.Append(string.Format("at {0}.{1} in {2}:{3}\r\n",
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