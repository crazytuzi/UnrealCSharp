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

        public UClass Get()
        {
            SubclassOfImplementation.SubclassOf_GetImplementation(GetHandle(), out var OutValue);

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