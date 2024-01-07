using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FString : IGCHandle
    {
        public FString()
        {
        }

        ~FString() => StringImplementation.String_UnRegisterImplementation(GetHandle());

        public FString(String InValue) => StringImplementation.String_RegisterImplementation(this, InValue);

        public static implicit operator FString(String InValue) => new FString(InValue);

        public static Boolean operator ==(FString A, FString B) =>
            StringImplementation.String_IdenticalImplementation(A.GetHandle(), B.GCHandle);

        public static Boolean operator !=(FString A, FString B) =>
            !StringImplementation.String_IdenticalImplementation(A.GetHandle(), B.GCHandle);

        public override String ToString()
        {
            StringImplementation.String_ToStringImplementation(GetHandle(), out var OutValue);

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