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
            LazyObjectPtrImplementation.LazyObjectPtr_RegisterImplementation(this, InObject.GetHandle());

        public static implicit operator TLazyObjectPtr<T>(T InObject) => new(InObject);

        public static Boolean operator ==(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            LazyObjectPtrImplementation.LazyObjectPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TLazyObjectPtr<T> A, TLazyObjectPtr<T> B) =>
            !LazyObjectPtrImplementation.LazyObjectPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TLazyObjectPtr<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public T Get()
        {
            return LazyObjectPtrImplementation.LazyObjectPtr_GetImplementation(GetHandle()) as T;
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