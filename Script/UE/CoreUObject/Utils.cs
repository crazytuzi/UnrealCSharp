using System;
using System.Reflection;
using System.Diagnostics;
using System.Text;
using System.Collections.Generic;
using System.Linq;

namespace Script.CoreUObject
{
    public static class Utils
    {
        private static bool IsOverrideType(Type InType) => InType.IsDefined(typeof(OverrideAttribute), true);

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

        public static bool IsClass(Type InType)
        {
            return InType.IsClass;
        }

        public static bool IsEnum(Type InType)
        {
            return InType.IsEnum;
        }
        
        public static void GetPropertyInfo(Type InType, out bool IsOverride,
            out int OutPropertyLength, out string[] OutPropertyNames, out PropertyInfo[] OutPropertyInfos, 
            out int OutFieldLength, out string[] OutFieldNames, out FieldInfo[] OutFieldInfos, 
            out int OutMethodLength, out string[] OutMethodNames, out MethodInfo[] OutMethodInfos, 
            out bool[] OutIsMethodOverrides
            , out int[] OutMethodParamsLength
            // ,out int OutAttrDescLength, out int[] OutAttrDescs,
            // out Attribute[] OutAttrs
            )
        {
            // OutAttrDescs [Class有多少个Attr, 每个Property展开分别有多少个Attr, 每个Field展开分别有多少个Attr]
            // 示例 [1,3,0,2] Class有1个Attr,假定有2个Property，1个Field，那就是，第一个Property有3个Attr，第二个Property有0个Attr，第一个Field有2个Attr
            // OutAttrs [ClassAttr1, Property1-1, Property1-2, Property1-3, nullptr/或者不用占位，Field1-1, Field1-2]

            IsOverride = false;

            // OutAttrDescLength = 0;
            
            // var Type = GetType(InType);

            OutPropertyInfos = InType.GetProperties(
                BindingFlags.Instance |
                BindingFlags.Static |
                BindingFlags.Public |
                BindingFlags.NonPublic
            );
            
            OutPropertyLength = OutPropertyInfos.Length;
            
            OutPropertyNames = new string[OutPropertyLength];
            
            OutFieldInfos = InType.GetFields(
                BindingFlags.Instance |
                BindingFlags.Static |
                BindingFlags.Public |
                BindingFlags.NonPublic);
            
            OutFieldLength = OutFieldInfos.Length;
            
            OutFieldNames = new string[OutFieldLength];
            
            OutMethodInfos = InType.GetMethods(
                BindingFlags.Instance |
                BindingFlags.Static |
                BindingFlags.Public |
                BindingFlags.NonPublic);
            
            OutMethodLength = OutMethodInfos.Length;
            
            OutMethodNames = new string[OutMethodLength];
            
            OutIsMethodOverrides = new bool[OutMethodLength];
            
            OutMethodParamsLength = new int[OutMethodLength];
            
            var AttrDesc = new List<int>();
            
            var Attrs = new List<Attribute>();

            var Count = 0;
            
            foreach (var Attr in InType.GetCustomAttributes())
            {
                if (Attr is OverrideAttribute)
                {
                    IsOverride = true;
                }

                Count++;
                
                Attrs.Add(Attr);
            }
            
            // [0] 类有多少个Attr
            AttrDesc.Add(Count);

            for (var i = 0; i < OutPropertyInfos.Length; i++)
            {
                OutPropertyNames[i] = OutPropertyInfos[i].Name;
            }

            for (var i = 0; i < OutFieldInfos.Length; i++)
            {
                OutFieldNames[i] =  OutFieldInfos[i].Name;
            }

            for (var i = 0; i < OutMethodInfos.Length; i++)
            {
                OutMethodNames[i] = OutMethodInfos[i].Name;
                
                OutMethodParamsLength[i] = OutMethodInfos[i].GetParameters().Length;
                
                var IsMethodOverride = false;
                
                foreach (var Attr in OutMethodInfos[i].GetCustomAttributes())
                {
                    if (Attr is OverrideAttribute)
                    {
                        IsMethodOverride = true;
                    }
                }
                
                OutIsMethodOverrides[i] = IsMethodOverride;
            }
        }
    }
}