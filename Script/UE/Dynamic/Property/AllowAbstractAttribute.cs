using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowAbstractAttribute : Attribute
    {
        public AllowAbstractAttribute()
        {
            Value = "true";
        }

        public AllowAbstractAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}