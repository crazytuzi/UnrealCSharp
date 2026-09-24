using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExactClassAttribute : Attribute
    {
        public ExactClassAttribute(string InValue = "true")
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}