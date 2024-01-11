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

        public static implicit operator FString(String InValue) => new(InValue);

        public static Boolean operator ==(FString A, FString B) =>
            StringImplementation.String_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(FString A, FString B) =>
            !StringImplementation.String_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as FString;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public override String ToString()
        {
            return StringImplementation.String_ToStringImplementation(GetHandle());
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