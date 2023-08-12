using System;

namespace Script.CoreUObject
{
    public interface IGCHandle
    {
        public unsafe void SetHandle(void* InGCHandle);

        public IntPtr GetHandle();
    }
}