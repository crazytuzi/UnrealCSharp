using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayAfterAttribute : Attribute
    {
        public DisplayAfterAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}