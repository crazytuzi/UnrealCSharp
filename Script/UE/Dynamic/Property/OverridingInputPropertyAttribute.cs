using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class OverridingInputPropertyAttribute : Attribute
    {
        public OverridingInputPropertyAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}