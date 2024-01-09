using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FName : IGCHandle
    {
        public FName()
        {
        }

        ~FName() => NameImplementation.Name_UnRegisterImplementation(GetHandle());

        public FName(String InValue) => NameImplementation.Name_RegisterImplementation(this, InValue);

        public static implicit operator FName(String InValue) => new FName(InValue);

        public static Boolean operator ==(FName A, FName B) =>
            NameImplementation.Name_IdenticalImplementation(A.GetHandle(), B.GCHandle);

        public static Boolean operator !=(FName A, FName B) =>
            !NameImplementation.Name_IdenticalImplementation(A.GetHandle(), B.GCHandle);

        public override String ToString()
        {
            NameImplementation.Name_ToStringImplementation(GetHandle(), out var OutValue);

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