using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintBaseOnlyAttribute : Attribute
    {
        public string MetaValue { get; set; }

        public BlueprintBaseOnlyAttribute(string MetaValue)
        {
            this.MetaValue = MetaValue;
        }

        public BlueprintBaseOnlyAttribute()
        {
            this.MetaValue = "true";
        }
    }
}