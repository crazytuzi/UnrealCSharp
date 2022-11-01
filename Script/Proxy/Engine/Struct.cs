using Script.Reflection.Struct;

namespace Script.Engine
{
    public abstract class UStruct
    {
        protected UStruct() => RegisterStruct();

        private void RegisterStruct() => StructUtils.RegisterStruct(this, GetPathName());

        ~UStruct() => StructUtils.UnRegisterStruct(this);

        protected abstract string GetPathName();
    }
}