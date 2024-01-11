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

        public static implicit operator FText(String InValue) => new(InValue);

        public static Boolean operator ==(FText A, FText B) =>
            TextImplementation.Text_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public static Boolean operator !=(FText A, FText B) =>
            !TextImplementation.Text_IdenticalImplementation(
                A?.GetHandle() ?? IntPtr.Zero, B?.GetHandle() ?? IntPtr.Zero);

        public override Boolean Equals(Object Other) => this == Other as FText;

        public override Int32 GetHashCode() => GetHandle().ToInt32();

        public override String ToString()
        {
            return TextImplementation.Text_ToStringImplementation(GetHandle());
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