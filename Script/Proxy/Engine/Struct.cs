using Script.Reflection.Struct;
using IntPtr = Script.Reflection.Function.IntPtr;

namespace Script.Engine
{
    public abstract class UStruct
    {
        protected UStruct() => RegisterStruct();

        protected UStruct(IntPtr InValue)
        {
        }

        private void RegisterStruct() => StructUtils.RegisterStruct(this, GetPathName());

        ~UStruct() => StructUtils.UnRegisterStruct(this);

        protected abstract string GetPathName();
    }
}