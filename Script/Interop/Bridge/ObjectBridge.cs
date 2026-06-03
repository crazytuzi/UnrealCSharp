using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Interop;

public static class ObjectBridge
{
    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static nint NewObject(nint InHandle)
    {
        if (HandleData.GetObject(InHandle) is Type Type)
        {
            var Object = RuntimeHelpers.GetUninitializedObject(Type);

            return HandleData.AllocImplementation(Object, true);
        }

        return 0;
    }
}