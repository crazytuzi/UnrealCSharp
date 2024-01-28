using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AlwaysAsPinAttribute : Attribute
    {
        public AlwaysAsPinAttribute()
        {
            Value = "true";
        }

        public AlwaysAsPinAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}