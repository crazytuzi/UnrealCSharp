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

        public UClass Get()
        {
            SoftClassPtrImplementation.SoftClassPtr_GetImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public unsafe void SetHandle(void* InGCHandle)
        {
            GCHandle = new System.IntPtr(InGCHandle);
        }

        public System.IntPtr GetHandle()
        {
            return GCHandle;
        }

        private System.IntPtr GCHandle;
    }
}