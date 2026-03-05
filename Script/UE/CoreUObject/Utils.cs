using System;
using System.Reflection;
using System.Diagnostics;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Script.Dynamic;

namespace Script.CoreUObject
{
    public static class Utils
    {
        public static string GetPathName(Type InType) => InType.GetCustomAttribute<PathNameAttribute>(true)?.PathName;

        private static Type MakeGenericTypeInstance(Type InGenericTypeDefinition, Type[] InTypeArguments) =>
            Activator.CreateInstance(InGenericTypeDefinition.MakeGenericType(InTypeArguments)).GetType();

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

        public static Type[] GetTypesWithAttribute(Type InAttributeType, Assembly InAssembly, out int OutLength)
        {
            var Types = new List<Type>();

            foreach (var Type in InAssembly.GetTypes())
            {
                if (Type.IsDefined(InAttributeType, false))
                {
                    Types.Add(Type);
                }
            }

            OutLength = Types.Count;

            return Types.ToArray();
        }

        public static void GetClassReflection(Type InType,
            out Type OutTypeDefinition, out string OutName, out string OutNameSpace, out string OutPathName,
            out Type OutParent, out Type OutUnderlyingType, out bool OutIsClass, out bool OutIsEnum,
            out int OutGenericArgumentLength, out Type[] OutGenericArguments,
            out int OutInterfaceLength, out Type[] OutInterfaces,
            out int OutClassAttributeLength, out Type[] OutClassAttributes,
            out int[] OutClassAttributeValueLength, out string[] OutClassAttributeValues,
            out int OutPropertyLength, out string[] OutPropertyNames,
            out PropertyInfo[] OutPropertyInfos, out Type[] OutPropertyTypes,
            out int[] OutPropertyAttributeCounts, out Type[] OutPropertyAttributes,
            out int[] OutPropertyAttributeValueCounts, out string[] OutPropertyAttributeValues,
            out int OutFieldLength, out string[] OutFieldNames, out FieldInfo[] OutFieldInfos,
            out int OutMethodLength, out string[] OutMethodNames, out MethodBase[] OutMethodInfos,
            out bool[] OutMethodIsStatics, out int[] OutMethodParamCounts, out Type[] OutMethodReturnTypes,
            out int[] OutMethodParamIndex, out string[] OutMethodParamNames,
            out Type[] OutMethodParamTypes, out bool[] OutMethodParamRefs,
            out int[] OutMethodAttributeCounts, out Type[] OutMethodAttributes,
            out int[] OutMethodAttributeValueCounts, out string[] OutMethodAttributeValues
        )
        {
            OutTypeDefinition = GetType(InType);

            OutName = InType.Name;

            OutNameSpace = InType.Namespace;

            OutPathName = null;

            foreach (var CustomAttribute in InType.GetCustomAttributes())
            {
                if (CustomAttribute is PathNameAttribute Attribute)
                {
                    OutPathName = Attribute.PathName;
                }
            }

            OutParent = InType.BaseType;

            OutUnderlyingType = InType.IsEnum ? InType.GetEnumUnderlyingType() : null;

            OutIsClass = InType.IsClass;

            OutIsEnum = InType.IsEnum;

            OutGenericArguments = InType.GenericTypeArguments;

            OutGenericArgumentLength = OutGenericArguments.Length;

            OutInterfaces = InType.GetInterfaces();

            OutInterfaceLength = (InType.IsValueType || InType.IsGenericType) ? 0 : OutInterfaces.Length;

            var ClassAttributes = new List<Type>();

            var ClassAttributeValueIndex = new List<int>();

            var ClassAttributeValues = new List<string>();

            var UClassAttributeNamespace = typeof(UClassAttribute).Namespace;

            var OverrideAttributeType = typeof(OverrideAttribute);

            foreach (var CustomAttribute in InType.CustomAttributes)
            {
                if (CustomAttribute.AttributeType.Namespace == UClassAttributeNamespace ||
                    CustomAttribute.AttributeType == OverrideAttributeType)
                {
                    ClassAttributes.Add(CustomAttribute.AttributeType);

                    var ClassAttributeValueCount = 0;

                    foreach (var ConstructorArgument in CustomAttribute.ConstructorArguments)
                    {
                        ClassAttributeValues.Add(ConstructorArgument.Value.ToString());

                        ClassAttributeValueCount++;
                    }

                    ClassAttributeValueIndex.Add(ClassAttributeValueCount);
                }
            }

            OutClassAttributeLength = ClassAttributes.Count;

            OutClassAttributes = ClassAttributes.ToArray();

            OutClassAttributeValueLength = ClassAttributeValueIndex.ToArray();

            OutClassAttributeValues = ClassAttributeValues.ToArray();

            OutPropertyInfos = InType.GetProperties(
                BindingFlags.Instance |
                BindingFlags.Static |
                BindingFlags.Public |
                BindingFlags.NonPublic
            );

            OutPropertyLength = OutPropertyInfos.Length;

            OutPropertyNames = new string[OutPropertyLength];

            OutPropertyTypes = new Type[OutPropertyLength];

            OutPropertyAttributeCounts = new int[OutPropertyLength];

            var PropertyAttributes = new List<Type>();

            var PropertyAttributeIndex = new List<int>();

            var PropertyAttributeValues = new List<string>();

            for (var i = 0; i < OutPropertyInfos.Length; i++)
            {
                OutPropertyNames[i] = OutPropertyInfos[i].Name;

                OutPropertyTypes[i] = OutPropertyInfos[i].PropertyType;

                var PropertyAttributeCount = 0;

                foreach (var CustomAttribute in OutPropertyInfos[i].CustomAttributes)
                {
                    if (CustomAttribute.AttributeType.Namespace == UClassAttributeNamespace)
                    {
                        var PropertyAttributeValueCount = 0;

                        PropertyAttributes.Add(CustomAttribute.AttributeType);

                        foreach (var ConstructorArgument in CustomAttribute.ConstructorArguments)
                        {
                            PropertyAttributeValues.Add(ConstructorArgument.Value.ToString());

                            PropertyAttributeValueCount++;
                        }

                        PropertyAttributeIndex.Add(PropertyAttributeValueCount);

                        PropertyAttributeCount++;
                    }
                }

                OutPropertyAttributeCounts[i] = PropertyAttributeCount;
            }

            OutPropertyAttributes = PropertyAttributes.ToArray();

            OutPropertyAttributeValueCounts = PropertyAttributeIndex.ToArray();

            OutPropertyAttributeValues = PropertyAttributeValues.ToArray();

            OutFieldInfos = InType.GetFields(
                BindingFlags.Instance |
                BindingFlags.Static |
                BindingFlags.Public |
                BindingFlags.NonPublic);

            OutFieldLength = OutFieldInfos.Length;

            OutFieldNames = new string[OutFieldLength];

            for (var i = 0; i < OutFieldInfos.Length; i++)
            {
                OutFieldNames[i] = OutFieldInfos[i].Name;
            }

            var Constructors = InType.GetConstructors(
                BindingFlags.Instance |
                BindingFlags.Static |
                BindingFlags.Public |
                BindingFlags.NonPublic);

            var Methods = InType.GetMethods(
                    BindingFlags.Instance |
                    BindingFlags.Static |
                    BindingFlags.Public |
                    BindingFlags.NonPublic)
                .Where(Method => !Method.IsSpecialName)
                .ToArray();

            var ConstructorLength = Constructors.Length;

            OutMethodLength = ConstructorLength + Methods.Length;

            OutMethodInfos = new MethodBase[OutMethodLength];

            for (var i = 0; i < ConstructorLength; i++)
            {
                OutMethodInfos[i] = Constructors[i];
            }

            for (var i = 0; i < Methods.Length; i++)
            {
                OutMethodInfos[ConstructorLength + i] = Methods[i];
            }

            OutMethodNames = new string[OutMethodLength];

            OutMethodParamCounts = new int[OutMethodLength];

            for (var i = 0; i < OutMethodInfos.Length; i++)
            {
                OutMethodNames[i] = OutMethodInfos[i].Name;

                OutMethodParamCounts[i] = OutMethodInfos[i].GetParameters().Length;
            }

            OutMethodIsStatics = new bool[OutMethodLength];

            OutMethodReturnTypes = new Type[OutMethodLength];

            OutMethodParamIndex = new int[OutMethodLength];

            var MethodParamNames = new List<string>();

            var MethodParamTypes = new List<Type>();

            var MethodParamRefs = new List<bool>();

            var UFunctionAttributeType = typeof(UFunctionAttribute);

            for (var i = 0; i < OutMethodInfos.Length; i++)
            {
                var IsUFunction = false;

                foreach (var CustomAttribute in OutMethodInfos[i].CustomAttributes)
                {
                    if (CustomAttribute.AttributeType == UFunctionAttributeType)
                    {
                        IsUFunction = true;

                        break;
                    }
                }

                OutMethodParamIndex[i] = MethodParamNames.Count;

                if (IsUFunction && OutMethodInfos[i] is MethodInfo MethodInfo)
                {
                    OutMethodIsStatics[i] = MethodInfo.IsStatic;

                    OutMethodReturnTypes[i] = MethodInfo.ReturnType;

                    foreach (var Parameter in MethodInfo.GetParameters())
                    {
                        MethodParamNames.Add(Parameter.Name);

                        var ParameterType = Parameter.ParameterType;

                        MethodParamTypes.Add(ParameterType.IsByRef ? ParameterType.GetElementType() : ParameterType);

                        MethodParamRefs.Add(ParameterType.IsByRef);
                    }
                }
                else
                {
                    OutMethodIsStatics[i] = false;

                    OutMethodReturnTypes[i] = null;
                }
            }

            OutMethodParamNames = MethodParamNames.ToArray();

            OutMethodParamTypes = MethodParamTypes.ToArray();

            OutMethodParamRefs = MethodParamRefs.ToArray();

            OutMethodAttributeCounts = new int[OutMethodLength];

            var MethodAttributes = new List<Type>();

            var MethodAttributeValueIndex = new List<int>();

            var MethodAttributeValues = new List<string>();

            for (var i = 0; i < OutMethodInfos.Length; i++)
            {
                var MethodAttribute = 0;

                foreach (var CustomAttribute in OutMethodInfos[i].CustomAttributes)
                {
                    if (CustomAttribute.AttributeType.Namespace == UClassAttributeNamespace ||
                        CustomAttribute.AttributeType == OverrideAttributeType
                       )
                    {
                        var MethodAttributeValue = 0;

                        MethodAttributes.Add(CustomAttribute.AttributeType);

                        foreach (var ConstructorArgument in CustomAttribute.ConstructorArguments)
                        {
                            MethodAttributeValues.Add(ConstructorArgument.Value.ToString());

                            MethodAttributeValue++;
                        }

                        MethodAttributeValueIndex.Add(MethodAttributeValue);

                        MethodAttribute++;
                    }
                }

                OutMethodAttributeCounts[i] = MethodAttribute;
            }

            OutMethodAttributes = MethodAttributes.ToArray();

            OutMethodAttributeValueCounts = MethodAttributeValueIndex.ToArray();

            OutMethodAttributeValues = MethodAttributeValues.ToArray();
        }
    }
}