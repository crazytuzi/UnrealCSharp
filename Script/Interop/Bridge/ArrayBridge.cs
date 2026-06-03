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
                var Handle = GCHandle.Alloc(Array.CreateInstance(Type, InLength), GCHandleType.Pinned);

                return HandleData.AddEntity(Handle);
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static nint ArrayGet(nint InHandle, int InIndex)
    {
        var Handle = HandleData.GetHandle(InHandle);

        if (Handle is { IsAllocated: true, Target: Array Array })
        {
            if (InIndex < Array.Length)
            {
                var Type = Array.GetType().GetElementType()!;

                var Size = Type.IsValueType ? Marshal.SizeOf(Type) : sizeof(nint);

                return Handle.AddrOfPinnedObject() + InIndex * Size;
            }
        }

        return 0;
    }

    [UnmanagedCallersOnly]
    public static nint ArrayGetRef(nint InHandle, int InIndex)
    {
        if (HandleData.GetHandle(InHandle) is { IsAllocated: true, Target: Array Array })
        {
            if (InIndex < Array.Length)
            {
                var Value = Array.GetValue(InIndex);

                if (Value != null)
                {
                    return HandleData.AllocImplementation(Value);
                }
            }
        }

        return 0;
    }
}