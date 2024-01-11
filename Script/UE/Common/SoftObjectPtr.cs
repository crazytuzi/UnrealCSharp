using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSoftObjectPtr<T> : IGCHandle where T : UObject
    {
        public TSoftObjectPtr()
        {
        }

        ~TSoftObjectPtr() => SoftObjectPtrImplementation.SoftObjectPtr_UnRegisterImplementation(GetHandle());

        public TSoftObjectPtr(T InObject) =>
            SoftObjectPtrImplementation.SoftObjectPtr_RegisterImplementation(this, InObject.GetHandle());

        public static implicit operator TSoftObjectPtr<T>(T InObject) => new(InObject);

        public static Boolean operator ==(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) =>
            SoftObjectPtrImplementation.SoftObjectPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TSoftObjectPtr<T> A, TSoftObjectPtr<T> B) =>
            !SoftObjectPtrImplementation.SoftObjectPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TSoftObjectPtr<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public T Get()
        {
            return SoftObjectPtrImplementation.SoftObjectPtr_GetImplementation(GetHandle()) as T;
        }

        public T LoadSynchronous()
        {
            return SoftObjectPtrImplementation.SoftObjectPtr_LoadSynchronousImplementation(GetHandle()) as T;
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