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
            WeakObjectPtrImplementation.WeakObjectPtr_RegisterImplementation(this, InObject.GetHandle());

        public static implicit operator TWeakObjectPtr<T>(T InObject) => new(InObject);

        public static Boolean operator ==(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B) =>
            WeakObjectPtrImplementation.WeakObjectPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TWeakObjectPtr<T> A, TWeakObjectPtr<T> B) =>
            !WeakObjectPtrImplementation.WeakObjectPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TWeakObjectPtr<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public T Get()
        {
            return WeakObjectPtrImplementation.WeakObjectPtr_GetImplementation(GetHandle()) as T;
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