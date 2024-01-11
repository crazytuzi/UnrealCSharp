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

        public TSubclassOf(UClass InClass) =>
            SubclassOfImplementation.SubclassOf_RegisterImplementation(this, InClass.GetHandle());

        public static implicit operator TSubclassOf<T>(UClass InClass) => new(InClass);

        public static Boolean operator ==(TSubclassOf<T> A, TSubclassOf<T> B) =>
            SubclassOfImplementation.SubclassOf_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(TSubclassOf<T> A, TSubclassOf<T> B) =>
            !SubclassOfImplementation.SubclassOf_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as TSubclassOf<T>;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public UClass Get()
        {
            return SubclassOfImplementation.SubclassOf_GetImplementation(GetHandle());
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