using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowAbstractAttribute : Attribute
    {
        public string MetaValue { get; set; }

        public AllowAbstractAttribute(string MetaValue)
        {
            this.MetaValue = MetaValue;
        }

        public AllowAbstractAttribute()
        {
            this.MetaValue = "true";
        }
    }
}