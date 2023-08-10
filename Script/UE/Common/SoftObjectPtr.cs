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
            SoftObjectPtrImplementation.SoftObjectPtr_RegisterImplementation(this, InObject);

        public static implicit operator TSoftObjectPtr<T>(T InObject) => new TSoftObjectPtr<T>(InObject);

        public T Get()
        {
            SoftObjectPtrImplementation.SoftObjectPtr_GetImplementation<T>(GetHandle(), out var OutValue);

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