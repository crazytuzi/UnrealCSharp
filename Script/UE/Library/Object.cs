using System;
using Script.Library;
using Script.Common;
using Script.Engine;

namespace Script.CoreUObject
{
    public partial class UObject : IGCHandle
    {
        public UClass GetClass()
        {
            return ObjectImplementation.Object_GetClassImplementation(GetHandle());
        }

        public FString GetName()
        {
            return ObjectImplementation.Object_GetNameImplementation(GetHandle());
        }

        public UWorld GetWorld()
        {
            return ObjectImplementation.Object_GetWorldImplementation(GetHandle());
        }

        public override String ToString()
        {
            return GetName().ToString();
        }

        public Boolean IsValid()
        {
            return ObjectImplementation.Object_IsValidImplementation(GetHandle());
        }

        public Boolean IsA<T>() where T : UObject, IStaticClass
        {
            return ObjectImplementation.Object_IsAImplementation(GetHandle(), T.StaticClass().GetHandle());
        }

        public unsafe void SetHandle(void* InHandle)
        {
            GCHandle = new IntPtr(InHandle);
        }

        public IntPtr GetHandle()
        {
            return GCHandle;
        }

        private IntPtr GCHandle;
    }
}