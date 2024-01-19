using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class FixedIncrementAttribute : Attribute
    {
        public FixedIncrementAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}