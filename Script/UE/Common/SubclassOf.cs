using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class TSubclassOf<T> : IGCHandle where T : UObject
    {
        public TSubclassOf()
        {
        }

        ~TSubclassOf() => SubclassOfImplementation.SubclassOf_UnRegisterImplementation(GetHandle());

        public TSubclassOf(UClass InClass) => SubclassOfImplementation.SubclassOf_RegisterImplementation(this, InClass);

        public static implicit operator TSubclassOf<T>(UClass InClass) => new TSubclassOf<T>(InClass);

        public static Boolean operator ==(TSubclassOf<T> A, TSubclassOf<T> B) =>
            SubclassOfImplementation.SubclassOf_IdenticalImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(TSubclassOf<T> A, TSubclassOf<T> B) =>
            !SubclassOfImplementation.SubclassOf_IdenticalImplementation(A.GetHandle(), B.GetHandle());

        public UClass Get()
        {
            SubclassOfImplementation.SubclassOf_GetImplementation(GetHandle(), out var OutValue);

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