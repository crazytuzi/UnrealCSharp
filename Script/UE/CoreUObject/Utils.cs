using System;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Script.Dynamic;
using Interop;

namespace Script.CoreUObject
{
    public static class Utils
    {
        public static string GetPathName(Type InType) => InType.GetCustomAttribute<PathNameAttribute>(true)?.PathName;

        private static Type GetType(Type InType) =>
            InType.IsByRef
                ? InType.GetElementType()!.IsGenericType
                    ? InType.GetElementType()?.GetGenericTypeDefinition()
                    : InType.GetElementType()
                : InType.IsGenericType
                    ? InType.GetGenericTypeDefinition()
                    : InType;

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
            var Result = new List<Type>();

            Type[] Types;

            try
            {
                Types = InAssembly.GetTypes();
            }
            catch (ReflectionTypeLoadException ReflectionTypeLoadException)
            {
                Types = ReflectionTypeLoadException.Types;
            }

            foreach (var Type in Types)
            {
                if (Type != null && Type.IsDefined(InAttributeType, false))
                {
                    Result.Add(Type);
                }
            }

            OutLength = Result.Count;

            return Result.ToArray();
        }

        private static void GetClassDescriptorImplementation(Type InType,
            out Type OutTypeDefinition, out string OutNameSpace, out string OutPathName,
            out Type OutParent, out Type OutUnderlyingType, out bool OutIsClass, out bool OutIsEnum,
            out int OutGenericArgumentLength, out Type[] OutGenericArguments,
            out int OutInterfaceLength, out Type[] OutInterfaces,
            out int OutClassAttributeLength, out Type[] OutClassAttributes,
            out int[] OutClassAttributeValueLength, out string[] OutClassAttributeValues
        )
        {
            OutTypeDefinition = GetType(InType);

            OutNameSpace = InType.Namespace;

            OutPathName = null;

            var PathNameAttributeFullName = typeof(PathNameAttribute).FullName;

            foreach (var CustomAttribute in InType.CustomAttributes)
            {
                if (CustomAttribute.AttributeType.FullName == PathNameAttributeFullName)
                {
                    OutPathName = CustomAttribute.ConstructorArguments[0].Value as string;
                }
            }

            OutParent = InType.BaseType;

            OutUnderlyingType = InType.IsEnum ? InType.GetEnumUnderlyingType() : null;

            OutIsClass = InType.IsClass;

            OutIsEnum = InType.IsEnum;

            if (OutIsClass || OutIsEnum)
            {
                OutGenericArguments = InType.GenericTypeArguments;

                OutGenericArgumentLength = OutGenericArguments.Length;

                OutInterfaces = InType.GetInterfaces();

                OutInterfaceLength = (InType.IsValueType || InType.IsGenericType) ? 0 : OutInterfaces.Length;

                var ClassAttributes = new List<Type>();

                var ClassAttributeValueIndex = new List<int>();

                var ClassAttributeValues = new List<string>();

                var UClassAttributeNamespace = typeof(UClassAttribute).Namespace;

                var OverrideAttributeTypeFullName = typeof(OverrideAttribute).FullName;

                foreach (var CustomAttribute in InType.CustomAttributes)
                {
                    if (CustomAttribute.AttributeType.Namespace == UClassAttributeNamespace ||
                        CustomAttribute.AttributeType.FullName == OverrideAttributeTypeFullName)
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
            }
            else
            {
                OutGenericArgumentLength = 0;

                OutGenericArguments = null;

                OutInterfaceLength = 0;

                OutInterfaces = null;

                OutClassAttributeLength = 0;

                OutClassAttributes = null;

                OutClassAttributeValueLength = null;

                OutClassAttributeValues = null;
            }
        }

        private static void GetClassPropertiesImplementation(Type InType,
            out int OutPropertyLength, out string[] OutPropertyNames,
            out PropertyInfo[] OutPropertyInfos, out Type[] OutPropertyTypes,
            out int[] OutPropertyAttributeCounts, out Type[] OutPropertyAttributes,
            out int[] OutPropertyAttributeValueCounts, out string[] OutPropertyAttributeValues
        )
        {
            if (InType.IsClass)
            {
                var UClassAttributeNamespace = typeof(UClassAttribute).Namespace;

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
            }
            else
            {
                OutPropertyLength = 0;

                OutPropertyNames = null;

                OutPropertyInfos = null;

                OutPropertyTypes = null;

                OutPropertyAttributeCounts = null;

                OutPropertyAttributes = null;

                OutPropertyAttributeValueCounts = null;

                OutPropertyAttributeValues = null;
            }
        }

        private static void GetClassFieldsImplementation(Type InType,
            out int OutFieldLength, out string[] OutFieldNames, out FieldInfo[] OutFieldInfos
        )
        {
            if (InType.IsClass || InType.IsEnum)
            {
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
            }
            else
            {
                OutFieldLength = 0;

                OutFieldNames = null;

                OutFieldInfos = null;
            }
        }

        private static void GetClassMethodsImplementation(Type InType,
            out int OutMethodLength, out string[] OutMethodNames, out MethodBase[] OutMethodInfos,
            out bool[] OutMethodIsStatics, out int[] OutMethodParamCounts, out Type[] OutMethodReturnTypes,
            out int[] OutMethodParamIndex, out string[] OutMethodParamNames,
            out Type[] OutMethodParamTypes, out bool[] OutMethodParamRefs,
            out int[] OutMethodAttributeCounts, out Type[] OutMethodAttributes,
            out int[] OutMethodAttributeValueCounts, out string[] OutMethodAttributeValues
        )
        {
            if (InType.IsClass)
            {
                var UClassAttributeNamespace = typeof(UClassAttribute).Namespace;

                var OverrideAttributeTypeFullName = typeof(OverrideAttribute).FullName;

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

                var UFunctionAttributeTypeFullName = typeof(UFunctionAttribute).FullName;

                for (var i = 0; i < OutMethodInfos.Length; i++)
                {
                    var IsUFunction = false;

                    foreach (var CustomAttribute in OutMethodInfos[i].CustomAttributes)
                    {
                        if (CustomAttribute.AttributeType.FullName == UFunctionAttributeTypeFullName)
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

                            MethodParamTypes.Add(ParameterType.IsByRef
                                ? ParameterType.GetElementType()
                                : ParameterType);

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
                            CustomAttribute.AttributeType.FullName == OverrideAttributeTypeFullName
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
            else
            {
                OutMethodLength = 0;

                OutMethodNames = null;

                OutMethodInfos = null;

                OutMethodIsStatics = null;

                OutMethodParamCounts = null;

                OutMethodReturnTypes = null;

                OutMethodParamIndex = null;

                OutMethodParamNames = null;

                OutMethodParamTypes = null;

                OutMethodParamRefs = null;

                OutMethodAttributeCounts = null;

                OutMethodAttributes = null;

                OutMethodAttributeValueCounts = null;

                OutMethodAttributeValues = null;
            }
        }

        [UnmanagedCallersOnly]
        public static int IsOverride(nint InTypeHandle)
        {
            if (HandleData.GetObject(InTypeHandle) is Type Type)
            {
                return Type.IsDefined(typeof(UClassAttribute), false) ||
                       Type.IsDefined(typeof(OverrideAttribute), false)
                    ? 1
                    : 0;
            }

            return 0;
        }

        [UnmanagedCallersOnly]
        public static unsafe void GetClassDescriptor(nint InTypeHandle, nint* OutBuffer)
        {
            if (HandleData.GetObject(InTypeHandle) is Type Type)
            {
                GetClassDescriptorImplementation(Type,
                    out var OutTypeDefinition, out var OutNameSpace, out var OutPathName,
                    out var OutParent, out var OutUnderlyingType, out var OutIsClass, out var OutIsEnum,
                    out var OutGenericArgumentLength, out var OutGenericArguments,
                    out var OutInterfaceLength, out var OutInterfaces,
                    out var OutClassAttributeLength, out var OutClassAttributes,
                    out var OutClassAttributeValueLength, out var OutClassAttributeValues
                );

                OutBuffer[0] = OutTypeDefinition != null ? HandleData.Alloc(OutTypeDefinition) : 0;

                OutBuffer[1] = OutNameSpace != null ? HandleData.Alloc(OutNameSpace) : 0;

                OutBuffer[2] = OutPathName != null ? HandleData.Alloc(OutPathName) : 0;

                OutBuffer[3] = OutParent != null ? HandleData.Alloc(OutParent) : 0;

                OutBuffer[4] = OutUnderlyingType != null ? HandleData.Alloc(OutUnderlyingType) : 0;

                OutBuffer[5] = OutIsClass ? 1 : 0;

                OutBuffer[6] = OutIsEnum ? 1 : 0;

                OutBuffer[7] = OutGenericArgumentLength;

                OutBuffer[8] = OutGenericArguments != null ? HandleData.Alloc(OutGenericArguments) : 0;

                OutBuffer[9] = OutInterfaceLength;

                OutBuffer[10] = OutInterfaces != null ? HandleData.Alloc(OutInterfaces) : 0;

                OutBuffer[11] = OutClassAttributeLength;

                OutBuffer[12] = OutClassAttributes != null ? HandleData.Alloc(OutClassAttributes) : 0;

                OutBuffer[13] = OutClassAttributeValueLength != null
                    ? HandleData.Alloc(OutClassAttributeValueLength)
                    : 0;

                OutBuffer[14] = OutClassAttributeValues != null ? HandleData.Alloc(OutClassAttributeValues) : 0;
            }
        }

        [UnmanagedCallersOnly]
        public static unsafe void GetClassProperties(nint InTypeHandle, nint* OutBuffer)
        {
            if (HandleData.GetObject(InTypeHandle) is Type Type)
            {
                GetClassPropertiesImplementation(Type,
                    out var OutPropertyLength, out var OutPropertyNames,
                    out var OutPropertyInfos, out var OutPropertyTypes,
                    out var OutPropertyAttributeCounts, out var OutPropertyAttributes,
                    out var OutPropertyAttributeValueCounts, out var OutPropertyAttributeValues
                );

                OutBuffer[0] = OutPropertyLength;

                OutBuffer[1] = OutPropertyNames != null ? HandleData.Alloc(OutPropertyNames) : 0;

                OutBuffer[2] = OutPropertyInfos != null ? HandleData.Alloc(OutPropertyInfos) : 0;

                OutBuffer[3] = OutPropertyTypes != null ? HandleData.Alloc(OutPropertyTypes) : 0;

                OutBuffer[4] = OutPropertyAttributeCounts != null ? HandleData.Alloc(OutPropertyAttributeCounts) : 0;

                OutBuffer[5] = OutPropertyAttributes != null ? HandleData.Alloc(OutPropertyAttributes) : 0;

                OutBuffer[6] = OutPropertyAttributeValueCounts != null
                    ? HandleData.Alloc(OutPropertyAttributeValueCounts)
                    : 0;

                OutBuffer[7] = OutPropertyAttributeValues != null ? HandleData.Alloc(OutPropertyAttributeValues) : 0;
            }
        }

        [UnmanagedCallersOnly]
        public static unsafe void GetClassFields(nint InTypeHandle, nint* OutBuffer)
        {
            if (HandleData.GetObject(InTypeHandle) is Type Type)
            {
                GetClassFieldsImplementation(Type,
                    out var OutFieldLength, out var OutFieldNames, out var OutFieldInfos
                );

                OutBuffer[0] = OutFieldLength;

                OutBuffer[1] = OutFieldNames != null ? HandleData.Alloc(OutFieldNames) : 0;

                OutBuffer[2] = OutFieldInfos != null ? HandleData.Alloc(OutFieldInfos) : 0;
            }
        }

        [UnmanagedCallersOnly]
        public static unsafe void GetClassMethods(nint InTypeHandle, nint* OutBuffer)
        {
            if (HandleData.GetObject(InTypeHandle) is Type Type)
            {
                GetClassMethodsImplementation(Type,
                    out var OutMethodLength, out var OutMethodNames, out var OutMethodInfos,
                    out var OutMethodIsStatics, out var OutMethodParamCounts, out var OutMethodReturnTypes,
                    out var OutMethodParamIndex, out var OutMethodParamNames,
                    out var OutMethodParamTypes, out var OutMethodParamRefs,
                    out var OutMethodAttributeCounts, out var OutMethodAttributes,
                    out var OutMethodAttributeValueCounts, out var OutMethodAttributeValues
                );

                OutBuffer[0] = OutMethodLength;

                OutBuffer[1] = OutMethodNames != null ? HandleData.Alloc(OutMethodNames) : 0;

                OutBuffer[2] = OutMethodInfos != null ? HandleData.Alloc(OutMethodInfos) : 0;

                OutBuffer[3] = OutMethodIsStatics != null ? HandleData.Alloc(OutMethodIsStatics) : 0;

                OutBuffer[4] = OutMethodParamCounts != null ? HandleData.Alloc(OutMethodParamCounts) : 0;

                OutBuffer[5] = OutMethodReturnTypes != null ? HandleData.Alloc(OutMethodReturnTypes) : 0;

                OutBuffer[6] = OutMethodParamIndex != null ? HandleData.Alloc(OutMethodParamIndex) : 0;

                OutBuffer[7] = OutMethodParamNames != null ? HandleData.Alloc(OutMethodParamNames) : 0;

                OutBuffer[8] = OutMethodParamTypes != null ? HandleData.Alloc(OutMethodParamTypes) : 0;

                OutBuffer[9] = OutMethodParamRefs != null ? HandleData.Alloc(OutMethodParamRefs) : 0;

                OutBuffer[10] = OutMethodAttributeCounts != null ? HandleData.Alloc(OutMethodAttributeCounts) : 0;

                OutBuffer[11] = OutMethodAttributes != null ? HandleData.Alloc(OutMethodAttributes) : 0;

                OutBuffer[12] = OutMethodAttributeValueCounts != null
                    ? HandleData.Alloc(OutMethodAttributeValueCounts)
                    : 0;

                OutBuffer[13] = OutMethodAttributeValues != null ? HandleData.Alloc(OutMethodAttributeValues) : 0;
            }
        }
    }
}