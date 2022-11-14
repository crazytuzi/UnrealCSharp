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
            StructUtils.Struct_Register(this, GetType().GetCustomAttribute<PathNameAttribute>(true).PathName);

        ~UStruct() => StructUtils.Struct_UnRegister(this);
    }
}