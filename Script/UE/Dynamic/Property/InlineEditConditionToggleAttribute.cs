using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class InlineEditConditionToggleAttribute : Attribute
    {
        public InlineEditConditionToggleAttribute()
        {
            Value = "true";
        }

        public InlineEditConditionToggleAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}