using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExactClassAttribute : Attribute
    {
        public ExactClassAttribute()
        {
            Value = "true";
        }

        public ExactClassAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}