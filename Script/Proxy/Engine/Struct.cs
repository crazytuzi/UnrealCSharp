using System;
using System.Reflection;
using Script.Reflection.Struct;

namespace Script.Engine
{
    public abstract class UStruct
    {
        protected UStruct() => RegisterStruct();

        protected UStruct(Type InValue)
        {
        }

        private void RegisterStruct() =>
            StructUtils.RegisterStruct(this, GetType().GetCustomAttribute<PathNameAttribute>(true).PathName);

        ~UStruct() => StructUtils.UnRegisterStruct(this);
    }
}