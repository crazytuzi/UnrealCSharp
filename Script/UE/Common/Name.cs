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

        public static implicit operator FName(String InValue) => new(InValue);

        public static Boolean operator ==(FName A, FName B) =>
            NameImplementation.Name_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(FName A, FName B) =>
            !NameImplementation.Name_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as FName;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public override String ToString()
        {
            return NameImplementation.Name_ToStringImplementation(GetHandle());
        }

        public unsafe void SetHandle(void* InGCHandle)
        {
            GCHandle = new IntPtr(InGCHandle);
        }

        public IntPtr GetHandle()
        {
            return GCHandle;
        }

        public static FName NAME_None => NameImplementation.Name_NAME_NoneImplementation();

        private IntPtr GCHandle;
    }
}