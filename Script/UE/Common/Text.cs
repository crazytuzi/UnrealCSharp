using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.Common
{
    public class FText : IGCHandle
    {
        public FText()
        {
        }

        ~FText() => TextImplementation.Text_UnRegisterImplementation(GetHandle());

        public FText(String InValue) => TextImplementation.Text_RegisterImplementation(this, InValue);

        public static implicit operator FText(String InValue) => new FText(InValue);

        public static Boolean operator ==(FText A, FText B) =>
            TextImplementation.Text_IdenticalImplementation(A.GetHandle(), B.GCHandle);

        public static Boolean operator !=(FText A, FText B) =>
            !TextImplementation.Text_IdenticalImplementation(A.GetHandle(), B.GCHandle);

        public override String ToString()
        {
            TextImplementation.Text_ToStringImplementation(GetHandle(), out var OutValue);

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