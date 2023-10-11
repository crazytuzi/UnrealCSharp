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
            SoftClassPtrImplementation.SoftClassPtr_RegisterImplementation(this, InClass);

        public static implicit operator TSoftClassPtr<T>(UClass InClass) => new TSoftClassPtr<T>(InClass);

        public static Boolean operator ==(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            SoftClassPtrImplementation.SoftClassPtr_IdenticalImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(TSoftClassPtr<T> A, TSoftClassPtr<T> B) =>
            !SoftClassPtrImplementation.SoftClassPtr_IdenticalImplementation(A.GetHandle(), B.GetHandle());

        public UClass Get()
        {
            SoftClassPtrImplementation.SoftClassPtr_GetImplementation(GetHandle(), out var OutValue);

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