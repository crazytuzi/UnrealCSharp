using System;
using System.Runtime.InteropServices;

namespace Interop;

public static unsafe class ArrayBridge
{
    [UnmanagedCallersOnly]
    public static nint NewArray(byte* InFullName, int InLength)
    {
        if (InFullName != null && InLength > 0)
        {
            var FullName = Marshal.PtrToStringUTF8((nint)InFullName)!;

            var Type = TypeBridge.GetTypeImplementation(FullName);

            if (Type != null)
            {
                return HandleData.Alloc(Array.CreateInstance(Type, InLength), true);
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static nint ArrayGet(nint InHandle, int InIndex)
    {
        if (HandleData.GetObject(InHandle) is Array Array)
        {
            if (InIndex < Array.Length)
            {
                var Value = Array.GetValue(InIndex);

                if (Value != null)
                {
                    return HandleData.Alloc(Value);
                }
            }
        }

        return 0;
    }
}