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
            ObjectImplementation.Object_GetClassImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString GetName()
        {
            ObjectImplementation.Object_GetNameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public UWorld GetWorld()
        {
            ObjectImplementation.Object_GetWorldImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public override string ToString()
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