using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace Interop;

public static class TypeBridge
{
    private static readonly Dictionary<string, Type> StringToType = new(StringComparer.Ordinal);

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static unsafe nint GetClass(byte* InFullName)
    {
        if (InFullName != null)
        {
            var FullName = Marshal.PtrToStringUTF8((nint)InFullName)!;

            if (!string.IsNullOrEmpty(FullName))
            {
                var Type = GetTypeImplementation(FullName);

                if (Type != null)
                {
                    return HandleData.Alloc(Type);
                }
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static nint GetType(nint InHandle)
    {
        var Object = HandleData.GetObject(InHandle);

        if (Object != null)
        {
            return HandleData.Alloc(Object.GetType());
        }

        return 0;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static unsafe nint GetMethod(nint InHandle, byte* InName, int InParamCount)
    {
        if (InName != null)
        {
            if (HandleData.GetObject(InHandle) is Type Type)
            {
                var Name = Marshal.PtrToStringUTF8((nint)InName)!;

                if (!string.IsNullOrEmpty(Name))
                {
                    const BindingFlags BindingFlag =
                        BindingFlags.Public | BindingFlags.NonPublic |
                        BindingFlags.Static | BindingFlags.Instance;

                    foreach (var Method in Type.GetMethods(BindingFlag))
                    {
                        if (Method.Name == Name && Method.GetParameters().Length == InParamCount)
                        {
                            return HandleData.Alloc(Method);
                        }
                    }
                }
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint GetFunctionPointer(char* InAssemblyName, char* InTypeName, char* InMethodName)
    {
        if (AssemblyLoader.CurrentContext != null)
        {
            var Type = GetTypeImplementation(AssemblyLoader.CurrentContext.Assemblies,
                new string(InAssemblyName), new string(InTypeName));

            if (Type != null)
            {
                var Method = Type.GetMethod(new string(InMethodName),
                    BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);

                if (Method != null)
                {
                    return Method.MethodHandle.GetFunctionPointer();
                }
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int GetNamespace(nint InHandle, byte* OutString, int InStringSize)
    {
        if (OutString != null && InStringSize > 0)
        {
            if (HandleData.GetObject(InHandle) is Type Type)
            {
                var Namespace = Type.Namespace ?? string.Empty;

                var String = new Span<byte>(OutString, InStringSize);

                var Length = Encoding.UTF8.GetBytes(
                    Namespace.AsSpan(0, Math.Min(Namespace.Length, InStringSize - 1)), String);

                String[Length] = 0;

                return Length;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int GetName(nint InHandle, byte* OutString, int InStringSize)
    {
        if (OutString != null && InStringSize > 0)
        {
            if (HandleData.GetObject(InHandle) is Type Type)
            {
                var Name = Type.Name;

                var String = new Span<byte>(OutString, InStringSize);

                var Length = Encoding.UTF8.GetBytes(
                    Name.AsSpan(0, Math.Min(Name.Length, InStringSize - 1)), String);

                String[Length] = 0;

                return Length;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static unsafe int GetFullName(nint InHandle, byte* OutString, int InStringSize)
    {
        if (OutString != null && InStringSize > 0)
        {
            if (HandleData.GetObject(InHandle) is Type Type)
            {
                var FullName = $"{Type.FullName}, {Type.Assembly.GetName().Name}";

                var String = new Span<byte>(OutString, InStringSize);

                var Length = Encoding.UTF8.GetBytes(
                    FullName.AsSpan(0, Math.Min(FullName.Length, InStringSize - 1)), String);

                String[Length] = 0;

                return Length;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static nint MakeGenericType(nint InGeneric, nint InType)
    {
        if (HandleData.GetObject(InGeneric) is Type Generic)
        {
            if (HandleData.GetObject(InType) is Type Type)
            {
                return HandleData.Alloc(Generic.MakeGenericType(Type));
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static nint MakeGenericType2(nint InGeneric, nint InKeyType, nint InValueType)
    {
        if (HandleData.GetObject(InGeneric) is Type Generic)
        {
            if (HandleData.GetObject(InKeyType) is Type Key)
            {
                if (HandleData.GetObject(InKeyType) is Type Value)
                {
                    return HandleData.Alloc(Generic.MakeGenericType(Key, Value));
                }
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxBool(int* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue != 0) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxSByte(sbyte* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxInt16(short* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxInt32(int* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxInt64(long* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxByte(byte* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxUInt16(ushort* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxUInt32(uint* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxUInt64(ulong* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxFloat(float* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe nint BoxDouble(double* InValue)
    {
        return InValue != null ? HandleData.Alloc(*InValue) : 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxBool(nint InHandle, int* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is bool Value)
            {
                *OutValue = Value ? 1 : 0;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxSByte(nint InHandle, sbyte* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is sbyte Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxInt16(nint InHandle, short* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is short Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxInt32(nint InHandle, int* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is int Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxInt64(nint InHandle, long* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is long Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxByte(nint InHandle, byte* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is byte Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxUInt16(nint InHandle, ushort* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is ushort Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxUInt32(nint InHandle, uint* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is uint Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxUInt64(nint InHandle, ulong* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is ulong Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxFloat(nint InHandle, float* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is float Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static unsafe int UnboxDouble(nint InHandle, double* OutValue)
    {
        if (OutValue != null)
        {
            if (HandleData.GetObject(InHandle) is double Value)
            {
                *OutValue = Value;

                return 1;
            }
        }

        return 0;
    }

    internal static Type? GetTypeImplementation(string InFullName)
    {
        if (StringToType.TryGetValue(InFullName, out var OutType))
        {
            return OutType;
        }

        var Index = InFullName.IndexOf(',');

        var TypeName = Index >= 0 ? InFullName[..Index].Trim() : InFullName;

        var AssemblyName = Index >= 0 ? InFullName[(Index + 1)..].Trim() : null;

        var Type = System.Type.GetType(InFullName, throwOnError: false, ignoreCase: false);

        if (Type == null)
        {
            var Context = AssemblyLoader.CurrentContext;

            if (Context != null)
            {
                Type = GetTypeImplementation(Context.Assemblies, AssemblyName, TypeName);
            }
        }

        if (Type != null)
        {
            StringToType.TryAdd(InFullName, Type);
        }

        return Type;
    }

    private static Type? GetTypeImplementation(IEnumerable<Assembly> InAssemblies, string? InAssemblyName,
        string InTypeName)
    {
        foreach (var Assembly in InAssemblies)
        {
            if (InAssemblyName != null)
            {
                if (!string.Equals(Assembly.GetName().Name, InAssemblyName, StringComparison.OrdinalIgnoreCase))
                {
                    continue;
                }
            }

            var Type = Assembly.GetType(InTypeName, throwOnError: false, ignoreCase: false);

            if (Type != null)
            {
                return Type;
            }
        }

        return null;
    }

    internal static void Clear()
    {
        StringToType.Clear();
    }
}