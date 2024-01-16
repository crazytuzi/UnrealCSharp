using System;
using Script.CoreUObject;

namespace Script.Common
{
    public class FDelegateBase : IGCHandle
    {
        public unsafe void SetHandle(void* InGCHandle)
        {
            GCHandle = new IntPtr(InGCHandle);
        }

        public IntPtr GetHandle()
        {
            return GCHandle;
        }

        private IntPtr GCHandle;
    }
}