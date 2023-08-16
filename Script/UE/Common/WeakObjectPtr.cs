using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TWeakObjectPtr<T> : IGCHandle where T : UObject
    {
        public TWeakObjectPtr()
        {
        }

        ~TWeakObjectPtr() => WeakObjectPtrImplementation.WeakObjectPtr_UnRegisterImplementation(GetHandle());

        public TWeakObjectPtr(T InObject) =>
            WeakObjectPtrImplementation.WeakObjectPtr_RegisterImplementation(this, InObject);

        public static implicit operator TWeakObjectPtr<T>(T InObject) => new TWeakObjectPtr<T>(InObject);

        public T Get()
        {
            WeakObjectPtrImplementation.WeakObjectPtr_GetImplementation<T>(GetHandle(), out var OutValue);

            return OutValue;
        }

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