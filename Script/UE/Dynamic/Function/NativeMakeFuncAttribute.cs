using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NativeMakeFuncAttribute : Attribute
    {
        public string MetaValue { get; set; }

        public NativeMakeFuncAttribute(string MetaValue)
        {
            this.MetaValue = MetaValue;
        }

        public NativeMakeFuncAttribute()
        {
            this.MetaValue = "true";
        }
    }
}