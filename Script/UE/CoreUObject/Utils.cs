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
            InMethodInfo.IsDefined(typeof(OverrideAttribute), false);

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

        private static bool EqualsTo<T>(T A, T B, Func<bool> IdenticalImplementation)
        {
            if (A is null && B is null)
            {
                return true;
            }

            if (A is null || B is null)
            {
                return false;
            }

            return ReferenceEquals(A, B) || IdenticalImplementation();
        }

        public static bool EqualsTo<T>(T A, T B, Func<nint, nint, bool> IdenticalImplementation)
            where T : IGarbageCollectionHandle
        {
            return EqualsTo(A, B, () => A.GarbageCollectionHandle == B.GarbageCollectionHandle ||
                                        IdenticalImplementation(A.GarbageCollectionHandle,
                                            B.GarbageCollectionHandle));
        }

        public static bool EqualsTo<T>(T A, T B, Func<nint, nint, nint, bool> IdenticalImplementation)
            where T : IStaticStruct, IGarbageCollectionHandle
        {
            return EqualsTo(A, B, () => A.GarbageCollectionHandle == B.GarbageCollectionHandle ||
                                        IdenticalImplementation(T.StaticStruct().GarbageCollectionHandle,
                                            A.GarbageCollectionHandle,
                                            B.GarbageCollectionHandle));
        }

        public static bool IsClass(Type InType)
        {
            return InType.IsClass;
        }

        public static bool IsEnum(Type InType)
        {
            return InType.IsEnum;
        }
    }
}