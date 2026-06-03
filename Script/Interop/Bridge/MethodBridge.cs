using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;

namespace Interop
{
    public static unsafe class MethodBridge
    {
        private static readonly Dictionary<string, nint> StringToMethod = new(StringComparer.Ordinal);

        private static readonly Dictionary<Type, PropertyInfo?> TypeToPropertyInfo = new();

        [UnmanagedCallersOnly]
        public static void RegisterBinding(byte** InNames, nint* InMethods, int InLength)
        {
            if (InNames != null && InMethods != null)
            {
                for (var Index = 0; Index < InLength; Index++)
                {
                    if (InNames[Index] != null && InMethods[Index] != 0)
                    {
                        var Name = Marshal.PtrToStringUTF8((nint)InNames[Index]) ?? string.Empty;

                        if (!string.IsNullOrEmpty(Name))
                        {
                            StringToMethod[Name] = InMethods[Index];
                        }
                    }
                }
            }
        }

        [UnmanagedCallersOnly]
        public static nint Invoke(nint InHandle, nint InMethod, int InParamCount, nint* InParams)
        {
            try
            {
                if (HandleData.GetObject(InMethod) is MethodBase Method)
                {
                    var Object = HandleData.GetObject(InHandle);

                    var MethodParameters = Method.GetParameters();

                    var MethodParameterLength = MethodParameters.Length;

                    var Parameters = new object?[MethodParameterLength];

                    for (var Index = 0; Index < MethodParameterLength; Index++)
                    {
                        var ParameterType = MethodParameters[Index].ParameterType;

                        if (InParams == null || Index >= InParamCount)
                        {
                            Parameters[Index] = ParameterType.IsValueType
                                ? Activator.CreateInstance(ParameterType)
                                : null;
                        }
                        else if (InParams[Index] == 0)
                        {
                            Parameters[Index] = null;
                        }
                        else
                        {
                            var ElementType = ParameterType.IsByRef ? ParameterType.GetElementType()! : ParameterType;

                            Parameters[Index] = ElementType.IsValueType
                                ? GetValue(InParams[Index], ElementType)
                                : HandleData.GetObject(*(nint*)InParams[Index]);
                        }
                    }

                    var Result = Method.Invoke(Object, Parameters);

                    if (InParams != null)
                    {
                        for (var Index = 0; Index < MethodParameterLength && Index < InParamCount; Index++)
                        {
                            var ParameterType = MethodParameters[Index].ParameterType;

                            if (ParameterType.IsByRef && InParams[Index] != 0)
                            {
                                var Param = (nint*)InParams[Index];

                                var ElementType = ParameterType.GetElementType()!;

                                var Parameter = Parameters[Index];

                                if (ElementType.IsValueType)
                                {
                                    SetValue(InParams[Index], Parameter, ElementType);
                                }
                                else if (Parameter != null)
                                {
                                    if (!TypeToPropertyInfo.TryGetValue(ElementType, out var ParameterProperty))
                                    {
                                        ParameterProperty = GetGarbageCollectionHandlePropertyInfo(ElementType);

                                        TypeToPropertyInfo[ElementType] = ParameterProperty;
                                    }

                                    if (ParameterProperty != null)
                                    {
                                        var Value = ParameterProperty.GetValue(Parameter);

                                        *Param = Value != null ? (nint)Value : 0;
                                    }
                                    else
                                    {
                                        *Param = HandleData.AllocImplementation(Parameter);
                                    }
                                }
                                else
                                {
                                    *Param = 0;
                                }
                            }
                        }
                    }

                    if (Result is null)
                    {
                        return 0;
                    }

                    var ResultType = Result.GetType();

                    if (ResultType.IsValueType)
                    {
                        if (ResultType.IsEnum)
                        {
                            var UnderlyingType = Enum.GetUnderlyingType(ResultType);

                            Result = Convert.ChangeType(Result, UnderlyingType);
                        }

                        return HandleData.AllocImplementation(Result);
                    }

                    if (!TypeToPropertyInfo.TryGetValue(ResultType, out var Property))
                    {
                        Property = GetGarbageCollectionHandlePropertyInfo(ResultType);

                        TypeToPropertyInfo[ResultType] = Property;
                    }

                    if (Property != null)
                    {
                        var Value = Property.GetValue(Result);

                        return Value != null ? (nint)Value : 0;
                    }

                    return HandleData.AllocImplementation(Result);
                }

                return 0;
            }
            catch (Exception Exception)
            {
                var InnerException = Exception is TargetInvocationException
                {
                    InnerException: not null
                } TargetInvocationException
                    ? TargetInvocationException.InnerException
                    : Exception;

                Console.Error.WriteLine($"\nUnhandled Exception:\n{InnerException}");

                return 0;
            }
        }

        public static nint GetMethod(string InName)
        {
            return StringToMethod.TryGetValue(InName, out var Method) ? Method : nint.Zero;
        }

        private static PropertyInfo? GetGarbageCollectionHandlePropertyInfo(Type InType)
        {
            for (var Type = InType; Type != null; Type = Type.BaseType)
            {
                var Property = Type.GetProperty("GarbageCollectionHandle",
                    BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.DeclaredOnly);

                if (Property != null && Property.PropertyType == typeof(nint))
                {
                    return Property;
                }
            }

            return null;
        }

        private static object GetValue(nint InHandle, Type InType)
        {
            var Type = Nullable.GetUnderlyingType(InType) ?? InType;

            return Type switch
            {
                _ when Type == typeof(bool) => *(bool*)InHandle,
                { IsEnum: true } => Enum.ToObject(Type,
                    Marshal.PtrToStructure(InHandle, Enum.GetUnderlyingType(Type))!),
                _ => Marshal.PtrToStructure(InHandle, Type)!,
            };
        }

        private static void SetValue(nint InHandle, object? InValue, Type InType)
        {
            if (InValue != null)
            {
                var Type = Nullable.GetUnderlyingType(InType) ?? InType;

                switch (Type)
                {
                    case var _ when Type == typeof(bool):
                        *(bool*)InHandle = (bool)InValue;
                        break;
                    case { IsEnum: true }:
                        Marshal.StructureToPtr(
                            Convert.ChangeType(InValue, Enum.GetUnderlyingType(Type)), InHandle, false);
                        break;
                    default:
                        Marshal.StructureToPtr(InValue, InHandle, false);
                        break;
                }
            }
        }

        internal static void Clear()
        {
            TypeToPropertyInfo.Clear();
        }
    }
}