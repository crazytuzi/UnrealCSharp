using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TLazyObjectPtr<T> : IGCHandle where T : UObject
    {
        public TLazyObjectPtr()
        {
        }

        ~TLazyObjectPtr() => LazyObjectPtrImplementation.LazyObjectPtr_UnRegisterImplementation(GetHandle());

        public TLazyObjectPtr(T InObject) =>
            LazyObjectPtrImplementation.LazyObjectPtr_RegisterImplementation(this, InObject);

        public static implicit operator TLazyObjectPtr<T>(T InObject) => new TLazyObjectPtr<T>(InObject);

        public static Boolean operator ==(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            LazyObjectPtrImplementation.LazyObjectPtr_IdenticalImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            !LazyObjectPtrImplementation.LazyObjectPtr_IdenticalImplementation(A.GetHandle(), B.GetHandle());

        public T Get()
        {
            LazyObjectPtrImplementation.LazyObjectPtr_GetImplementation<T>(GetHandle(), out var OutValue);

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