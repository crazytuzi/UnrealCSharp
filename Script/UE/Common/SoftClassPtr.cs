using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSoftClassPtr<T> : IGCHandle where T : UObject
    {
        public TSoftClassPtr()
        {
        }

        ~TSoftClassPtr() => SoftClassPtrImplementation.SoftClassPtr_UnRegisterImplementation(GetHandle());

        public TSoftClassPtr(UClass InClass) =>
            SoftClassPtrImplementation.SoftClassPtr_RegisterImplementation(this, InClass.GetHandle());

        public static implicit operator TSoftClassPtr<T>(UClass InClass) => new(InClass);

        public static Boolean operator ==(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            SoftClassPtrImplementation.SoftClassPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            !SoftClassPtrImplementation.SoftClassPtr_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TSoftClassPtr<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public UClass Get()
        {
            return SoftClassPtrImplementation.SoftClassPtr_GetImplementation(GetHandle());
        }

        public UClass LoadSynchronous()
        {
            return SoftClassPtrImplementation.SoftClassPtr_LoadSynchronousImplementation(GetHandle());
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