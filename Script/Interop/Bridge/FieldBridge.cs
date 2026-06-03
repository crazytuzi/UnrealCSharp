using System;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Interop;

public static class FieldBridge
{
    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static unsafe void SetStaticValue(nint InHandle, byte* InName, long InValue)
    {
        var Field = GetField(InHandle, InName);

        if (Field != null)
        {
            Field.SetValue(null, LongToField(InValue, Field.FieldType));
        }
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static unsafe long GetStaticValue(nint InHandle, byte* InName)
    {
        var Field = GetField(InHandle, InName);

        if (Field != null)
        {
            return FieldToLong(Field.GetValue(null));
        }

        return 0;
    }

    private static unsafe FieldInfo? GetField(nint InHandle, byte* InName)
    {
        if (HandleData.GetObject(InHandle) is Type Type)
        {
            var Name = Marshal.PtrToStringUTF8((nint)InName) ?? string.Empty;

            if (Name.Length > 0)
            {
                return Type.GetField(Name, BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
            }
        }

        return null;
    }

    private static object? LongToField(long InValue, Type InField) => InField switch
    {
        { IsValueType: false } => InValue != 0 ? InValue : null,
        { IsEnum: true } => Enum.ToObject(InField, InValue),
        _ when InField == typeof(nint) => (nint)InValue,
        _ when InField == typeof(nuint) => (nuint)InValue,
        _ => Convert.ChangeType(InValue, InField)
    };

    private static long FieldToLong(object? InValue) => InValue switch
    {
        null => 0,
        nint v => v,
        nuint v => (long)v,
        _ => Convert.ToInt64(InValue)
    };
}