using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;

namespace Interop
{
    public static unsafe class MethodBridge
    {
        private static readonly Dictionary<string, nint> StringToMethod = new(StringComparer.Ordinal);

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
                                    *Param = HandleData.Alloc(Parameter);
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
                    }

                    return HandleData.Alloc(Result);
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

        public static nint GetMethod(ref nint InSlot, string InName)
        {
            if (InSlot == nint.Zero)
            {
                InSlot = StringToMethod.TryGetValue(InName, out var Method) ? Method : nint.Zero;
            }

            return InSlot;
        }

        private static object GetValue(nint InHandle, Type InType)
        {
            return InType.IsEnum
                ? Enum.ToObject(InType, ReadPrimitiveValue(InHandle, Enum.GetUnderlyingType(InType)))
                : ReadPrimitiveValue(InHandle, InType);
        }

        private static object ReadPrimitiveValue(nint InHandle, Type InType)
        {
            return InType switch
            {
                _ when InType == typeof(bool) => *(bool*)InHandle,
                _ when InType == typeof(sbyte) => *(sbyte*)InHandle,
                _ when InType == typeof(short) => *(short*)InHandle,
                _ when InType == typeof(int) => *(int*)InHandle,
                _ when InType == typeof(long) => *(long*)InHandle,
                _ when InType == typeof(nint) => *(nint*)InHandle,
                _ when InType == typeof(byte) => *(byte*)InHandle,
                _ when InType == typeof(ushort) => *(ushort*)InHandle,
                _ when InType == typeof(uint) => *(uint*)InHandle,
                _ when InType == typeof(ulong) => *(ulong*)InHandle,
                _ when InType == typeof(nuint) => *(nuint*)InHandle,
                _ when InType == typeof(float) => *(float*)InHandle,
                _ when InType == typeof(double) => *(double*)InHandle
            };
        }

        private static void SetValue(nint InHandle, object? InValue, Type InType)
        {
            if (InValue != null)
            {
                if (InType.IsEnum)
                {
                    var UnderlyingType = Enum.GetUnderlyingType(InType);

                    WritePrimitiveValue(InHandle, Convert.ChangeType(InValue, UnderlyingType), UnderlyingType);
                }
                else
                {
                    WritePrimitiveValue(InHandle, InValue, InType);
                }
            }
        }

        private static void WritePrimitiveValue(nint InHandle, object InValue, Type InType)
        {
            switch (InType)
            {
                case var _ when InType == typeof(bool): *(bool*)InHandle = (bool)InValue; break;
                case var _ when InType == typeof(sbyte): *(sbyte*)InHandle = (sbyte)InValue; break;
                case var _ when InType == typeof(short): *(short*)InHandle = (short)InValue; break;
                case var _ when InType == typeof(int): *(int*)InHandle = (int)InValue; break;
                case var _ when InType == typeof(long): *(long*)InHandle = (long)InValue; break;
                case var _ when InType == typeof(nint): *(nint*)InHandle = (nint)InValue; break;
                case var _ when InType == typeof(byte): *(byte*)InHandle = (byte)InValue; break;
                case var _ when InType == typeof(ushort): *(ushort*)InHandle = (ushort)InValue; break;
                case var _ when InType == typeof(uint): *(uint*)InHandle = (uint)InValue; break;
                case var _ when InType == typeof(ulong): *(ulong*)InHandle = (ulong)InValue; break;
                case var _ when InType == typeof(nuint): *(nuint*)InHandle = (nuint)InValue; break;
                case var _ when InType == typeof(float): *(float*)InHandle = (float)InValue; break;
                case var _ when InType == typeof(double): *(double*)InHandle = (double)InValue; break;
            }
        }
    }
}