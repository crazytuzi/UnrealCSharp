using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Interop;

public static class ObjectBridge
{
    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static nint NewObject(nint InHandle, int bIsWeak)
    {
        if (HandleData.GetObject(InHandle) is Type Type)
        {
            var Object = RuntimeHelpers.GetUninitializedObject(Type);

            return HandleData.Alloc(Object, false, bIsWeak != 0);
        }

        return 0;
    }
}